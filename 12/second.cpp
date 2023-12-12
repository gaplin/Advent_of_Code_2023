#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>

struct record {
    std::string text;
    std::vector<int> groups;
};

void read_input(const std::string& file_name, std::vector<record>& output) {
    std::ifstream input(file_name);
    if(!input.is_open()) {
        perror("Unable to load input file");
        exit(1);
    }

    std::string line;
    while(std::getline(input, line)) {
        while(line[line.length() - 1] == '\r' || line[line.length() - 1] == '\n') {
            line.pop_back();
        }
        record record;
        int i = 0;
        std::string text;
        while(line[i] != ' ') {
            text += line[i];
            ++i;
        }
        record.text += text;
        for(int j = 0; j < 4; ++j) {
            record.text += '?' + text;
        }
        ++i;
        int group = 0;
        while(i < line.size()) {
            if(line[i] == ',') {
                record.groups.push_back(group);
                group = 0;
            } else {
                group = group * 10 + line[i] - '0';
            }
            ++i;
        }
        record.groups.push_back(group);
        int initial_group_size = record.groups.size();
        for(int j = 0; j < 4; ++j) {
            for(int k = 0; k < initial_group_size; ++k) {
                record.groups.push_back(record.groups[k]);
            }
        }
        output.push_back(record);
    }
    input.close();
}

void write_output(const std::string& file_name, const long long& result) {
    std::ofstream output(file_name);
    if(!output.is_open()) {
        perror("Unable to open output file");
        exit(1);
    }
    output << result;
    output.close();
}

long long get_num_of_arrangements(const record& record) {
    long long result = 0;
    int n = record.text.size();
    std::vector<std::vector<std::vector<long long>>> partial_results;
    for(int i = 0; i < 2; ++i) {
        partial_results.push_back(std::vector<std::vector<long long>>(n, std::vector<long long>(2, 0)));
    }

    for(int i = 0; i < n; ++i) {
        if(record.text[i] != '#') {
            partial_results[0][i][0] = 1;
        } else {
            break;
        }
    }
    bool idx = true;
    for(int j = 0; j < record.groups.size(); ++j) {
        int g = record.groups[j];
        int occurrences = 0;
        for (int i = 0; i < n; ++i) {
            char symbol = record.text[i];
            if(symbol != '.') {
                ++occurrences;
            } else {
                occurrences = 0;
            }
            if((symbol == '.' || symbol == '?') && i > 0) {
                partial_results[idx][i][0] = partial_results[idx][i - 1][0] + partial_results[idx][i - 1][1];
            } else {
                partial_results[idx][i][0] = 0;
            }
            if((symbol == '#' || symbol == '?') && occurrences >= g) {
                if(i - g < 0) {
                    if(j == 0) {
                        partial_results[idx][i][1] = 1;
                    } else {
                        partial_results[idx][i][1] = 0;
                    }
                } else {
                    partial_results[idx][i][1] = partial_results[!idx][i - g][0];
                }
            } else {
                partial_results[idx][i][1] = 0;
            }
        }
        idx = !idx;
    }
    return partial_results[!idx][n - 1][0] + partial_results[!idx][n - 1][1];
}

int main() {
    std::vector<record> records;
    read_input("input/input.txt", records);

    long long answer = 0;
    for(auto record : records) {
        answer += get_num_of_arrangements(record);
    }

    write_output("output/out_second.txt", answer);
}
#include <iostream>
#include <vector>
#include <fstream>

struct record {
    std::string text;
    std::vector<int> groups;
    std::vector<int> missing_positions;
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
        while(line[i] != ' ') {
            record.text += line[i];
            if(line[i] == '?') {
                record.missing_positions.push_back(i);
            }
            ++i;
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
        output.push_back(record);
    }
    input.close();
}

void write_output(const std::string& file_name, const int& result) {
    std::ofstream output(file_name);
    if(!output.is_open()) {
        perror("Unable to open output file");
        exit(1);
    }
    output << result;
    output.close();
}

bool valid_record(const std::string& text, const std::vector<int>& valid_groups) {
    std::vector<int> groups;
    int group_size = 0;
    for(int i = 0; i < text.size(); ++i) {
        if(text[i] == '#') {
            group_size += 1;
        } else if(group_size != 0) {
            groups.push_back(group_size);
            group_size = 0;
        }
    }
    if(group_size != 0) {
        groups.push_back(group_size);
    }
    if(groups.size() != valid_groups.size()) {
        return false;
    }
    for(int i = 0; i < groups.size(); ++i) {
        if(groups[i] != valid_groups[i]) {
            return false;
        }
    }
    return true;
}

int get_num_of_arrangements(record record) {
    int result = 0;
    int missing_count = record.missing_positions.size();
    int limit = 1 << (missing_count);
    for(int i = 0; i < limit; ++i) {
        int mask = i;
        for(int j = 0; j < missing_count; ++j) {
            bool damaged = (mask & 1);
            mask >>= 1;
            if(damaged) {
                record.text[record.missing_positions[j]] = '#';
            } else {
                record.text[record.missing_positions[j]] = '.';
            }
        }
        if(valid_record(record.text, record.groups)) {
            result += 1;
        }
    }
    return result;
}

int main() {
    std::vector<record> records;
    read_input("input/input.txt", records);

    int answer = 0;
    for(auto record : records) {
        answer += get_num_of_arrangements(record);
    }

    write_output("output/out_first.txt", answer);
}
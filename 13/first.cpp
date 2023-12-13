#include <iostream>
#include <vector>
#include <fstream>

struct map {
    std::vector<std::string> patterns;
};

void read_input(const std::string& file_name, std::vector<map>& output) {
    std::ifstream input(file_name);
    if(!input.is_open()) {
        perror("Unable to load input file");
        exit(1);
    }

    std::string line;
    map current_map;
    while(std::getline(input, line)) {
        while(line[line.length() - 1] == '\r' || line[line.length() - 1] == '\n') {
            line.pop_back();
        }
        if(line.size() == 0) {
            output.push_back(current_map);
            current_map = map();
        } else {
            current_map.patterns.push_back(line);
        }
    }
    output.push_back(current_map);
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

long long get_result(const std::vector<std::string>& patterns) {
    int n = patterns.size();
    int m = patterns[0].size();

    for(int i = 0; i < n - 1; ++i) {
        bool perfect_match = true;
        int u = i, d = i + 1;
        while(u >= 0 && d < n) {
            if(patterns[u] != patterns[d]) {
                perfect_match = false;
                break;
            }
            --u;
            ++d;
        }
        if(perfect_match) {
            return 100 * (i + 1);
        }
    }
    
    for(int i = 0; i < m - 1; ++i) {
        bool perfect_match = true;
        int l = i, r = i + 1;
        while(l >= 0 && r < m) {
            bool match = true;
            for(int j = 0; j < n; ++j) {
                if(patterns[j][l] != patterns[j][r]) {
                    match = false;
                    break;
                }
            }
            if(!match) {
                perfect_match = false;
                break;
            }
            --l;
            ++r;
        }
        if(perfect_match) {
            return i + 1;
        }
    }

    return 0;
}

int main() {
    std::vector<map> maps;
    read_input("input/input.txt", maps);

    long long answer = 0;
    for(auto map : maps) {
        answer += get_result(map.patterns);
    }

    write_output("output/out_first.txt", answer);
}
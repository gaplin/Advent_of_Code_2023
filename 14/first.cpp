#include <iostream>
#include <vector>
#include <fstream>

void read_input(const std::string& file_name, std::vector<std::string>& output) {
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
        output.push_back(line);
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

int main() {
    std::vector<std::string> map;
    read_input("input/input.txt", map);

    long long answer = 0;
    int n = map.size();
    int m = map[0].size();
    for(int i = 0; i < m; ++i) {
        int free_position = 0;
        for(int j = 0; j < n; ++j) {
            if(map[j][i] == 'O') {
                answer += n - free_position;
                ++free_position;
            } else if(map[j][i] == '#') {
                free_position = j + 1;
            }
        }
    }

    write_output("output/out_first.txt", answer);
}
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

void simulate_cycle(std::vector<std::string>& map) {
    int n = map.size();
    int m = map[0].size();
    
    // North
    for(int i = 0; i < m; ++i) {
        int free_position = 0;
        for(int j = 0; j < n; ++j) {
            if(map[j][i] == 'O') {
                map[j][i] = '.';
                map[free_position][i] = 'O';
                ++free_position;
            } else if(map[j][i] == '#') {
                free_position = j + 1;
            }
        }
    }

    // West
    for(int i = 0; i < n; ++i) {
        int free_position = 0;
        for(int j = 0; j < m; ++j) {
            if(map[i][j] == 'O') {
                map[i][j] = '.';
                map[i][free_position] = 'O';
                ++free_position;
            } else if(map[i][j] == '#') {
                free_position = j + 1;
            }
        }
    }

    // South
    for(int i = 0; i < m; ++i) {
        int free_position = n - 1;
        for(int j = n - 1; j >= 0; --j) {
            if(map[j][i] == 'O') {
                map[j][i] = '.';
                map[free_position][i] = 'O';
                --free_position;
            } else if(map[j][i] == '#') {
                free_position = j - 1;
            }
        }
    }   

    // East
    for(int i = 0; i < n; ++i) {
        int free_position = m - 1;
        for(int j = m - 1; j >= 0; --j) {
            if(map[i][j] == 'O') {
                map[i][j] = '.';
                map[i][free_position] = 'O';
                --free_position;
            } else if(map[i][j] == '#') {
                free_position = j - 1;
            }
        }
    }
}

bool equal_maps(const std::vector<std::string>& A, const std::vector<std::string>& B) {
    int n = A.size();
    int m = A[0].size();
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(A[i][j] != B[i][j]) {
                return false;
            }
        }
    }
    return true;
}

long long get_north_load(const std::vector<std::string>& map) {
    int n = map.size();
    int m = map[0].size();
    long long result = 0;
    for(int i = 0; i < n; ++i) {
        int height = n - i;
        for(int j = 0; j < m; ++j) {
            if(map[i][j] == 'O') {
                result += height;
            }
        }
    }

    return result;
}

int main() {
    std::vector<std::string> map;
    read_input("input/input.txt", map);

    long long answer = 0;
    std::vector<std::vector<std::string>> maps;
    maps.push_back(map);

    while(answer == 0) {
        simulate_cycle(map);
        for(int i = 0; i < maps.size(); ++i) {
            if(equal_maps(maps[i], map)) {
                int steps = 1000000000 - i;
                int cycle_length = maps.size() - i;
                answer = get_north_load(maps[i + steps % cycle_length]);
                break;
            }
        }
        maps.push_back(map);
    }

    write_output("output/out_second.txt", answer);
}
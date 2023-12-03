#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

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

void write_output(const std::string& file_name, const int& result) {
    std::ofstream output(file_name);
    if(!output.is_open()) {
        perror("Unable to open output file");
        exit(1);
    }
    output << result;
}

void fill_numbers(const std::vector<std::string>& map, std::vector<std::vector<int>>& output) {
    int height = output.size();
    int width = output[0].size();
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            if(map[i][j] < '0' || map[i][j] > '9') {
                continue;
            }
            int start_idx = j;
            std::string number_string;
            while(j < width && map[i][j] >= '0' && map[i][j] <= '9') {
                number_string += map[i][j];
                ++j;
            }
            number_string += map[i][j];
            int value = stoi(number_string);
            for(int k = start_idx; k < j; ++k) {
                output[i][k] = value;
            }
        }
    }
}

int get_answer(const std::vector<std::string>& map, const std::vector<std::vector<int>>& numbers) {
    int width = numbers[0].size();
    int height = numbers.size();
    std::vector<std::string> map_copy;
    map_copy.push_back(std::string(width + 2, '.'));
    for(auto line : map) {
        map_copy.push_back('.' + line + '.');
    }
    map_copy.push_back(std::string(width + 2, '.'));
    int result = 0;

    std::vector<std::pair<int, int>> neighbour_coordinate = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    std::vector<std::vector<std::vector<std::pair<int, int>>>> adjacent_numbers(height + 2, std::vector<std::vector<std::pair<int, int>>>(width + 2, std::vector<std::pair<int, int>>()));
    int num_idx = 0;
    for(int i = 1; i <= height; ++i) {
        ++num_idx;
        for(int j = 1; j <= width; ++j) {
            if(numbers[i - 1][j - 1] == 0) {
                ++num_idx;
                continue;
            }
            for(auto coordinate : neighbour_coordinate) {
                int cordY = i + coordinate.first;
                int cordX = j + coordinate.second;
                char symbol = map_copy[cordY][cordX];
                if(symbol == '*') {
                    bool value_already_added = false;
                    for(auto filled_entries : adjacent_numbers[cordY][cordX]) {
                        if(filled_entries.first == num_idx) {
                            value_already_added = true;
                            break;
                        }
                    }
                    if(value_already_added) {
                        break;
                    }
                    adjacent_numbers[cordY][cordX].push_back({num_idx, numbers[i - 1][j - 1]});
                }
            }
        }
    }
    for(auto line : adjacent_numbers) {
        for(auto cell : line) {
            if(cell.size() > 0) {
                for(auto pair : cell) {
                }
            }
            if(cell.size() == 2) {
                result += cell[0].second * cell[1].second;
            }
        }
    }
    return result;
}

int main() {
    std::vector<std::string> lines;
    read_input("input/input.txt", lines);

    int map_width = lines[0].size();
    int map_height = lines.size();
    std::vector<std::vector<int>> numbers(map_height, std::vector<int>(map_width));
    fill_numbers(lines, numbers);
    int answer = get_answer(lines, numbers);
    
    write_output("output/out_second.txt", answer);
}
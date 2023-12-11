#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

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
    output.close();
}

void read_map(const std::string& file_name, std::vector<std::string>& output) {
    std::vector<std::string> lines;
    read_input(file_name, lines);

    std::vector<int> col_maps;

    int width = 0;
    for(int i = 0; i < lines[0].size(); ++i) {
        col_maps.push_back(width);
        ++width;
        bool all_empty = true;
        for(int j = 0; j < lines.size(); ++j) {
            if(lines[j][i] != '.') {
                all_empty = false;
                break;
            }
        }
        if(all_empty) {
            ++width;
        }
    }
    std::string empty_line = std::string(width, '.');
    for(int i = 0; i < lines.size(); ++i) {
        std::string row(empty_line);
        bool all_empty = true;
        for(int j = 0; j < lines[i].size(); ++j) {
            if(lines[i][j] == '#') {
                all_empty = false;
            }
            row[col_maps[j]] = lines[i][j];
        }
        output.push_back(row);
        if(all_empty) {
            output.push_back(empty_line);
        }
    }
}

int get_distance(const std::pair<int, int>& source, const std::pair<int, int>& target) {
    return abs(source.first - target.first) + abs(source.second - target.second);
}

int main() {
    std::vector<std::string> map;
    read_map("input/input.txt", map);


    int answer = 0;
    std::vector<std::pair<int, int>> galaxies;
    for(int i = 0; i < map.size(); ++i) {
        for(int j = 0; j < map[i].size(); ++j) {
            if(map[i][j] == '#') {
                galaxies.push_back({i, j});
            }
        }
    }
    for(int i = 0; i < galaxies.size() - 1; ++i) {
        for(int j = i + 1; j < galaxies.size(); ++j) {
            answer += get_distance(galaxies[i], galaxies[j]);
        }
    }

    write_output("output/out_first.txt", answer);
}
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

void write_output(const std::string& file_name, const long long& result) {
    std::ofstream output(file_name);
    if(!output.is_open()) {
        perror("Unable to open output file");
        exit(1);
    }
    output << result;
    output.close();
}

void fill_x_prefix_sum(const std::vector<std::string>& map, std::vector<long long>& output, long long empty_col_value) {
    int width = map[0].size();
    int height = map.size();
    long long distance = 0;
    for(int i = 0; i < width - 1; ++i) {
        output[i] = distance;
        bool all_empty = true;
        for(int j = 0; j < height; ++j) {
            if(map[j][i] != '.') {
                all_empty = false;
                break;
            }
        }
        distance = all_empty ? 1 + empty_col_value : 1;
    }
    output[width - 1] = distance;
    for(int i = 1; i < width; ++i) {
        output[i] += output[i - 1];
    }
}

void fill_y_prefix_sum(const std::vector<std::string>& map, std::vector<long long>& output, long long empty_col_value) {
    int width = map[0].size();
    int height = map.size();
    long long distance = 0;
    for(int i = 0; i < height - 1; ++i) {
        output[i] = distance;
        bool all_empty = true;
        for(int j = 0; j < width; ++j) {
            if(map[i][j] != '.') {
                all_empty = false;
                break;
            }
        }
        distance = all_empty ? 1 + empty_col_value : 1;
    }
    output[height - 1] = distance;
    for(int i = 1; i < height; ++i) {
        output[i] += output[i - 1];
    }
}

long long get_distance(const std::pair<int, int>& source, const std::pair<int, int>& target,
 const std::vector<long long>& x_prefix_sum, const std::vector<long long>& y_prefix_sum) {

    return abs(x_prefix_sum[source.second] - x_prefix_sum[target.second])
     + abs(y_prefix_sum[source.first] - y_prefix_sum[target.first]);
}

int main() {
    std::vector<std::string> map;
    read_input("input/input.txt", map);

    std::vector<long long> x_prefix_sum(map[0].size());
    std::vector<long long> y_prefix_sum(map.size());

    long long empty_col_value = 999999;
    fill_x_prefix_sum(map, x_prefix_sum, empty_col_value);
    fill_y_prefix_sum(map, y_prefix_sum, empty_col_value);

    long long answer = 0;
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
            auto distance = get_distance(galaxies[i], galaxies[j], x_prefix_sum, y_prefix_sum);
            answer += distance;
        }
    }

    write_output("output/out_second.txt", answer);
}
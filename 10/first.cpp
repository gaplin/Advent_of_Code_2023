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

char get_symbol_at_position(const std::vector<std::string>& map, const int& i, const int& j) {
    if(i < 0 || i >= map.size() || j < 0 || j >= map[i].size()) {
        return '.';
    }
    return map[i][j];
}

void fill_neighbours(const std::vector<std::string>& map, std::vector<std::vector<int>>& G, const char& pipe, const int& i, const int& j) {
    int height = map.size();
    int width = map[i].size();
    int nodeIdx = i * width + j;
    if(pipe == '-') {
        char left_neighbour = get_symbol_at_position(map, i, j - 1);
        if(left_neighbour == '-' || left_neighbour == 'F' || left_neighbour == 'L') {
            G[nodeIdx].push_back(nodeIdx - 1);
        }
        char right_neighbour = get_symbol_at_position(map, i, j + 1);
        if(right_neighbour == '-' || right_neighbour == 'J' || right_neighbour == '7') {
            G[nodeIdx].push_back(nodeIdx + 1);
        }
        return;
    }
    if(pipe == '|') {
        char top_neighbour = get_symbol_at_position(map, i - 1, j);
        if(top_neighbour == '|' || top_neighbour == '7' || top_neighbour == 'F') {
            G[nodeIdx].push_back(nodeIdx - width);
        }
        char bottom_neighbour = get_symbol_at_position(map, i + 1, j);
        if(bottom_neighbour == '|' || bottom_neighbour == 'J' || bottom_neighbour == 'L') {
            G[nodeIdx].push_back(nodeIdx + width);
        }
        return;
    }
    if(pipe == 'S') {
        char left_neighbour = get_symbol_at_position(map, i, j - 1);
        if(left_neighbour == '-' || left_neighbour == 'F' || left_neighbour == 'L') {
            G[nodeIdx].push_back(nodeIdx - 1);
        }
        char right_neighbour = get_symbol_at_position(map, i, j + 1);
        if(right_neighbour == '-' || right_neighbour == 'J' || right_neighbour == '7') {
            G[nodeIdx].push_back(nodeIdx + 1);
        }
        char top_neighbour = get_symbol_at_position(map, i - 1, j);
        if(top_neighbour == '|' || top_neighbour == '7' || top_neighbour == 'F') {
            G[nodeIdx].push_back(nodeIdx - width);
        }
        char bottom_neighbour = get_symbol_at_position(map, i + 1, j);
        if(bottom_neighbour == '|' || bottom_neighbour == 'J' || bottom_neighbour == 'L') {
            G[nodeIdx].push_back(nodeIdx + width);
        }
        return;
    }
    if(pipe == 'L') {
        char top_neighbour = get_symbol_at_position(map, i - 1, j);
        if(top_neighbour == '|' || top_neighbour == '7' || top_neighbour == 'F') {
            G[nodeIdx].push_back(nodeIdx - width);
        }
        char right_neighbour = get_symbol_at_position(map, i, j + 1);
        if(right_neighbour == '-' || right_neighbour == 'J' || right_neighbour == '7') {
            G[nodeIdx].push_back(nodeIdx + 1);
        }
        return;
    }
    if(pipe == 'J') {
        char top_neighbour = get_symbol_at_position(map, i - 1, j);
        if(top_neighbour == '|' || top_neighbour == '7' || top_neighbour == 'F') {
            G[nodeIdx].push_back(nodeIdx - width);
        }
        char left_neighbour = get_symbol_at_position(map, i, j - 1);
        if(left_neighbour == '-' || left_neighbour == 'F' || left_neighbour == 'L') {
            G[nodeIdx].push_back(nodeIdx - 1);
        }
        return;
    }
    if(pipe == 'F') {
        char right_neighbour = get_symbol_at_position(map, i, j + 1);
        if(right_neighbour == '-' || right_neighbour == 'J' || right_neighbour == '7') {
            G[nodeIdx].push_back(nodeIdx + 1);
        }
        char bottom_neighbour = get_symbol_at_position(map, i + 1, j);
        if(bottom_neighbour == '|' || bottom_neighbour == 'J' || bottom_neighbour == 'L') {
            G[nodeIdx].push_back(nodeIdx + width);
        }
        return;
    }
    if(pipe == '7') {
        char bottom_neighbour = get_symbol_at_position(map, i + 1, j);
        if(bottom_neighbour == '|' || bottom_neighbour == 'J' || bottom_neighbour == 'L') {
            G[nodeIdx].push_back(nodeIdx + width);
        }
        char left_neighbour = get_symbol_at_position(map, i, j - 1);
        if(left_neighbour == '-' || left_neighbour == 'F' || left_neighbour == 'L') {
            G[nodeIdx].push_back(nodeIdx - 1);
        }
        return;
    }
}

void prepare_graph(const std::vector<std::string>& map, std::vector<std::vector<int>>& G, std::pair<int, int>& starting_position) {
    int height = map.size();
    int width = map[0].size();
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            char symbol = map[i][j];
            if(symbol != '.') {
                if(symbol == 'S') {
                    starting_position.first = i;
                    starting_position.second = j;
                }
                fill_neighbours(map, G, symbol, i, j);
            }
        }
    }
}

int mark_loop(const std::vector<std::vector<int>>& G, const int& starting_position) {
    int num_of_nodes = G.size();
    std::vector<int> distances(num_of_nodes, -1);

    std::queue<int> Q;
    Q.push(starting_position);
    distances[starting_position] = 0;

    int max_distance = 0;
    while(!Q.empty()) {
        int node = Q.front();
        Q.pop();
        int current_distance = distances[node];
        for(int neighbour : G[node]) {
            if(distances[neighbour] == -1) {
                distances[neighbour] = current_distance + 1;
                max_distance = std::max(max_distance, distances[neighbour]);
                Q.push(neighbour);
            }
        }
    }
    return max_distance;
}

int main() {
    std::vector<std::string> map;
    read_input("input/input.txt", map);

    int height = map.size();
    int width = map[0].size();
    std::vector<std::vector<int>> G(height * width);
    std::pair<int, int> starting_position;
    prepare_graph(map, G, starting_position);

    int starting_node = starting_position.first * width + starting_position.second;
    int answer = mark_loop(G, starting_node);
    write_output("output/out_first.txt", answer);
}
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

void fill_neighbours(std::vector<std::string>& map, std::vector<std::vector<int>>& G, const char& pipe, const int& i, const int& j) {
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
        bool top = false;
        bool bottom = false;
        bool right = false;
        bool left = false;
        char left_neighbour = get_symbol_at_position(map, i, j - 1);
        if(left_neighbour == '-' || left_neighbour == 'F' || left_neighbour == 'L') {
            G[nodeIdx].push_back(nodeIdx - 1);
            left = true;
        }
        char right_neighbour = get_symbol_at_position(map, i, j + 1);
        if(right_neighbour == '-' || right_neighbour == 'J' || right_neighbour == '7') {
            G[nodeIdx].push_back(nodeIdx + 1);
            right = true;
        }
        char top_neighbour = get_symbol_at_position(map, i - 1, j);
        if(top_neighbour == '|' || top_neighbour == '7' || top_neighbour == 'F') {
            G[nodeIdx].push_back(nodeIdx - width);
            top = true;
        }
        char bottom_neighbour = get_symbol_at_position(map, i + 1, j);
        if(bottom_neighbour == '|' || bottom_neighbour == 'J' || bottom_neighbour == 'L') {
            G[nodeIdx].push_back(nodeIdx + width);
            bottom = true;
        }
        if(bottom && top) {
            map[i][j] = '|';
        } else if(left && right) {
            map[i][j] = '-';
        } else if(top && right) {
            map[i][j] = 'L';
        } else if(right && bottom) {
            map[i][j] = 'F';
        } else if(bottom && left) {
            map[i][j] = '7';
        } else {
            map[i][j] = 'J';
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

void prepare_graph(std::vector<std::string>& map, std::vector<std::vector<int>>& G, std::pair<int, int>& starting_position) {
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

void mark_loop(const std::vector<std::vector<int>>& G, const int& starting_position, std::vector<std::string>& map) {
    int num_of_nodes = G.size();
    std::vector<bool> visited(num_of_nodes);

    std::queue<int> Q;
    Q.push(starting_position);
    visited[starting_position] = true;
    

    int width = map[0].size();
    while(!Q.empty()) {
        int node = Q.front();
        int i_position = node / width;
        int j_position = node % width;
        map[i_position][j_position] = 'X';
        Q.pop();
        for(int neighbour : G[node]) {
            if(!visited[neighbour]) {
                visited[neighbour] = true;
                Q.push(neighbour);
            }
        }
    }
}

int get_number_of_enclosed_tiles(const std::vector<std::string>& map, std::vector<std::string>& marked_map) {
    int enclosed_tiles = 0;
    for(int i = 0; i < map.size(); ++i) {
        int loop_hits = 0;
        for(int j = 0; j < map[i].size(); ++j) {
            char symbol = map[i][j];
            if(marked_map[i][j] == 'X' && (symbol == '|' || symbol == 'J' || symbol == 'L')) {
                loop_hits++;
            } else if(marked_map[i][j] != 'X' && loop_hits % 2 == 1){
                marked_map[i][j] = 'I';
                enclosed_tiles++;
            }
        }
    }
    return enclosed_tiles;
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
    std::vector<std::string> marked_map(map);
    mark_loop(G, starting_node, marked_map);

    int answer = get_number_of_enclosed_tiles(map, marked_map);
    write_output("output/out_second.txt", answer);
}
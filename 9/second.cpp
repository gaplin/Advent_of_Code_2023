#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <stack>

void read_input(const std::string& file_name, std::vector<std::vector<long long>>& output) {
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
        std::vector<long long> sequence;
        long long num = 0;
        int sign = 1;
        for(int i = 0; i < line.size(); ++i) {
            if(line[i] == ' ') {
                sequence.push_back(num * sign);
                sign = 1;
                num = 0;
            } else if(line[i] == '-') {
                sign = -1;
            } else {
                num = num * 10 + line[i] - '0';
            }
        }
        sequence.push_back(num * sign);
        output.push_back(sequence);
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
}

bool all_zeros(const std::vector<long long>& nums, int length) {
    for(int i = 0; i < length; ++i) {
        if(nums[i] != 0) {
            return false;
        }
    }
    return true;
}

long long get_next_number(const std::vector<long long>& sequence) {
    const int N = sequence.size();
    std::stack<long long> last_nums;
    last_nums.push(sequence[0]);

    int length = N;
    std::vector<long long> differences(sequence);
    while(!all_zeros(differences, length)) {
        --length;
        for(int i = 0; i < length; ++i) {
            differences[i] = differences[i + 1] - differences[i];
        }
        last_nums.push(differences[0]);
    }
    
    long long current_num = 0;

    while(!last_nums.empty()) {
        long long num = last_nums.top();
        last_nums.pop();
        current_num = num - current_num;
    }
    return current_num;
}

int main() {
    std::vector<std::vector<long long>> sequences;
    read_input("input/input.txt", sequences);

    long long answer = 0;
    for(auto sequence : sequences) {
        long long next_num = get_next_number(sequence);
        answer += next_num;
    }
    
    write_output("output/out_second.txt", answer);
}
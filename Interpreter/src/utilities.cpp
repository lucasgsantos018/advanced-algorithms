#include "../include/utilities.h"
#include <iostream>
#include <sstream>

std::vector<int> read_ram_input() {
    std::vector<int> ram(1000, 0);
    std::string line;
    int address = 0;
    
    // pula as linhas brancas do inicio
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        break;
    }
    
    // lê casos de teste
    int cases;
    std::istringstream iss(line);
    iss >> cases;
    
    for (int c = 0; c < cases; ++c) {
        address = 0;
        while (address < 1000 && std::getline(std::cin, line)) {
            if (line.empty()) continue;
            ram[address++] = std::stoi(line);
        }
    }
    
    return ram;
}

void initialize_system(std::vector<int>& ram, std::vector<int>& registers) {
    registers.assign(10, 0);
    ram.resize(1000, 0);
}
#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>

std::vector<int> read_ram_input();
void initialize_system(std::vector<int>& ram, std::vector<int>& registers);
int execute_program(std::vector<int>& ram, std::vector<int>& registers);

#endif
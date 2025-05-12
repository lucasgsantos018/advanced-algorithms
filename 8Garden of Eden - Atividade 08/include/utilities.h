#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>

void process_input();
bool is_garden_of_eden(int automaton, int n, const std::string& state);
bool backtrack(const std::vector<int>& rules, std::string& prev_state, 
               const std::string& target, int pos);

#endif
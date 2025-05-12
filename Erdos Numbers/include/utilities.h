#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>
#include <unordered_map>

void process_input();
std::vector<std::string> parse_authors(const std::string& line);
void calculate_erdos_numbers();
void add_paper(const std::vector<std::string>& authors);

#endif
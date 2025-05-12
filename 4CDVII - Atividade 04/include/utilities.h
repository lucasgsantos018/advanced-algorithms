#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>
#include <algorithm>

struct TollRecord {
    std::string license;
    int time;
    bool is_enter;
    int location;
};

void process_input();
bool compare_records(const TollRecord& a, const TollRecord& b);
double calculate_charges(const std::vector<int>& fares, const std::vector<TollRecord>& records);

#endif
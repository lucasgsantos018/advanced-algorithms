#include "../include/utilities.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

string solve_fragmentation(const vector<string>& fragments) {
    unordered_map<string, int> candidate_counts;
    int total_length = 0;
    
    // Calcula o comprimento total esperado
    for (const auto& frag : fragments) {
        total_length += frag.length();
    }
    int target_length = total_length * 2 / fragments.size();
    
    // Gera candidatos possíveis
    for (size_t i = 0; i < fragments.size(); ++i) {
        for (size_t j = i + 1; j < fragments.size(); ++j) {
            string candidate1 = fragments[i] + fragments[j];
            string candidate2 = fragments[j] + fragments[i];
            
            if (candidate1.length() == target_length) {
                candidate_counts[candidate1]++;
            }
            if (candidate2.length() == target_length) {
                candidate_counts[candidate2]++;
            }
        }
    }
    
    // Encontra o candidato mais frequente
    string result;
    int max_count = 0;
    for (const auto& [candidate, count] : candidate_counts) {
        if (count > max_count || (count == max_count && candidate < result)) {
            max_count = count;
            result = candidate;
        }
    }
    
    return result;
}

void process_input() {
    int cases;
    cin >> cases;
    
    for (int case_num = 0; case_num < cases; ++case_num) {
        vector<string> fragments;
        string line;
        
        // Pular linhas em branco entre casos
        while (line.empty() && getline(cin, line));
        
        do {
            if (!line.empty()) {
                fragments.push_back(line);
            }
        } while (getline(cin, line) && !line.empty());
        
        string solution = solve_fragmentation(fragments);
        cout << solution << endl;
        
        if (case_num < cases - 1) {
            cout << endl;
        }
    }
}
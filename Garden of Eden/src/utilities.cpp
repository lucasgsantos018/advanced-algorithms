#include "../include/utilities.h"
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

// Converte o identificador do autômato em regras de evolução
vector<int> get_rules(int automaton) {
    vector<int> rules(8);
    for (int i = 0; i < 8; ++i) {
        rules[i] = (automaton >> i) & 1;
    }
    return rules;
}

// Verifica se um estado anterior pode gerar o estado alvo
bool is_valid(const vector<int>& rules, const string& prev, const string& target) {
    int n = target.size();
    for (int i = 0; i < n; ++i) {
        int left = prev[(i - 1 + n) % n] - '0';
        int center = prev[i] - '0';
        int right = prev[(i + 1) % n] - '0';
        int pattern = (left << 2) | (center << 1) | right;
        if (rules[pattern] != target[i] - '0') {
            return false;
        }
    }
    return true;
}

// Backtracking para encontrar um estado anterior válido
bool backtrack(const vector<int>& rules, string& prev_state, 
               const string& target, int pos) {
    if (pos == target.size()) {
        return is_valid(rules, prev_state, target);
    }
    
    // Tenta ambos os valores (0 e 1) para a célula atual
    for (int bit = 0; bit <= 1; ++bit) {
        prev_state[pos] = '0' + bit;
        if (backtrack(rules, prev_state, target, pos + 1)) {
            return true;
        }
    }
    return false;
}

bool is_garden_of_eden(int automaton, int n, const string& state) {
    vector<int> rules = get_rules(automaton);
    string prev_state(n, '0');
    
    // Verifica se existe algum estado anterior que gera o estado atual
    return !backtrack(rules, prev_state, state, 0);
}

void process_input() {
    int automaton, n;
    string state;
    
    while (cin >> automaton >> n >> state) {
        if (is_garden_of_eden(automaton, n, state)) {
            cout << "GARDEN OF EDEN" << endl;
        } else {
            cout << "REACHABLE" << endl;
        }
    }
}
#include "../include/utilities.h"
#include <iostream>
#include <vector>
#include <cmath> 
#include <algorithm>

using namespace std;

// armazenar os resultados pré computados
vector<string> dp;

// calcula até N=10000
void initialize() {
    dp.resize(10001);
    dp[0] = "0";
    dp[1] = "1";
    
    vector<int> k_values(10001, 1);
    
    for (int n = 2; n <= 10000; ++n) { // começa com o k do caso anterior
        int k = k_values[n-1];
        long double min_moves = 2.0 * stold(dp[k]) + pow(2.0, n - k) - 1;
        
        // verificar valores próximos ao k pra encontrar um melhor
        for (int dk = -2; dk <= 2; ++dk) {
            int test_k = k + dk;
            if (test_k < 1 || test_k >= n) continue; // pular valores invalidos
            
            long double moves = 2.0 * stold(dp[test_k]) + pow(2.0, n - test_k) - 1;
            if (moves < min_moves) {
                min_moves = moves;
                k = test_k; // se encontrar um k melhor atualiza
            }
        }
        
        k_values[n] = k;
        dp[n] = to_string((long long)(2 * stoll(dp[k]) + (1LL << (n - k)) - 1));
    }
}

string calculate_moves(int N) {
    return dp[N];
}

void process_input() {
    initialize();
    int N;
    
    while (cin >> N) {
        cout << calculate_moves(N) << endl;
    }
}
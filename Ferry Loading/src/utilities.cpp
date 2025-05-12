#include "../include/utilities.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve_ferry_problem(int ferry_length, const vector<int>& cars) {
    int max_cm = ferry_length * 100;
    int n = cars.size();
    
    // Tabela DP: dp[i][l] = maior r possível com i carros e l no porto
    vector<vector<int>> dp(n+1, vector<int>(max_cm+1, -1));
    dp[0][0] = 0;
    
    int max_cars = 0;
    int best_l = 0, best_r = 0;

    // tabela DP
    for (int i = 0; i < n; ++i) {
        int car_len = cars[i];
        for (int l = max_cm; l >= 0; --l) {
            if (dp[i][l] == -1) continue;
            
            // tenta colocar no porto
            if (l + car_len <= max_cm) {
                dp[i+1][l+car_len] = max(dp[i+1][l+car_len], dp[i][l]);
                if (i+1 > max_cars) {
                    max_cars = i+1;
                    best_l = l+car_len;
                    best_r = dp[i][l];
                }
            }
            
            // tenta colocar no estibordo
            if (dp[i][l] + car_len <= max_cm) {
                dp[i+1][l] = max(dp[i+1][l], dp[i][l] + car_len);
                if (i+1 > max_cars) {
                    max_cars = i+1;
                    best_l = l;
                    best_r = dp[i][l] + car_len;
                }
            }
        }
    }

    // reconstroi a solução
    vector<string> solution;
    int current_l = best_l, current_r = best_r;
    
    for (int i = max_cars; i > 0; --i) {
        int car_len = cars[i-1];
        
        if (current_l >= car_len && dp[i-1][current_l-car_len] == current_r) {
            solution.push_back("port");
            current_l -= car_len;
        } else {
            solution.push_back("starboard");
            current_r -= car_len;
        }
    }
    
    cout << max_cars << endl;
    for (auto it = solution.rbegin(); it != solution.rend(); ++it) {
        cout << *it << endl;
    }
}

void process_input() {
    int cases;
    cin >> cases;
    
    while (cases--) {
        cin.ignore(); // pular linha em branco
        int ferry_length;
        cin >> ferry_length;
        
        vector<int> cars;
        while (true) {
            int car_len;
            cin >> car_len;
            if (car_len == 0) break;
            cars.push_back(car_len);
        }
        
        solve_ferry_problem(ferry_length, cars);
        if (cases > 0) cout << endl;
    }
}
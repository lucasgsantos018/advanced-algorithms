#include "../include/utilities.h"
#include <iostream>
#include <vector>

using namespace std;

// Calcular fatorial
int factorial(int x) {
    int result = 1;
    for (int i = 2; i <= x; ++i) {
        result *= i;
    }
    return result;
}

int calculate_coefficient(int n, const vector<int>& exponents) {
    int numerator = factorial(n);
    int denominator = 1;
    
    for (int exp : exponents) {
        denominator *= factorial(exp);
    }
    
    return numerator / denominator;
}

void process_input() {
    int n, k;
    
    while (cin >> n >> k) {
        vector<int> exponents(k);
        for (int i = 0; i < k; ++i) {
            cin >> exponents[i];
        }
        
        cout << calculate_coefficient(n, exponents) << endl;
    }
}
#include "../include/utilities.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool is_prime(int n) { // verifica se um numero é primo
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int sum_digits(int n) { // soma dos digitos de um numero
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int sum_prime_factors_digits(int n) { // soma dos digitos dos fatores primos
    int sum = 0;
    int original = n;
    
    while (n % 2 == 0) { // 2 é o único primo par, precisa tratar separadamente
        sum += sum_digits(2);
        n /= 2;
    }
    
    // verifica divisores ímpares de 3 até raiz quadrada de n
    for (int i = 3; i <= sqrt(n); i += 2) {
        while (n % i == 0) {
            sum += sum_digits(i);
            n /= i;
        }
    }
    
    // se sobrou um fator primo maior que 2 e diferente do número original
    if (n > 1 && n != original) {
        sum += sum_digits(n);
    }
    
    return sum;
}

bool is_smith_number(int n) { // verificar se um número é um número de Smith
    if (is_prime(n)) return false;
    return sum_digits(n) == sum_prime_factors_digits(n);
}

int find_next_smith(int n) { // função pra encontrar o próximo número de Smith após n
    while (true) {
        n++;
        if (is_smith_number(n)) {
            return n;
        }
    }
}

void process_input() {
    int cases;
    cin >> cases;
    
    while (cases--) {
        int n;
        cin >> n;
        cout << find_next_smith(n) << endl;
    }
}
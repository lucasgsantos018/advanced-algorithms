#include "../include/utilities.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>

using namespace std;

// Função de comparação pra ordenação
bool compare_records(const TollRecord& a, const TollRecord& b) {
    if (a.license != b.license)
        return a.license < b.license; // Ordena por placa primeiro
    return a.time < b.time; // Depois por tempo
}

// Converte data pra minutos desde o início do mês
int time_to_minutes(int day, int hour, int minute) {
    return day * 24 * 60 + hour * 60 + minute;
}

vector<int> parse_fares(const string& line) {
    vector<int> fares(24);
    istringstream iss(line);
    for (int i = 0; i < 24; ++i) {
        iss >> fares[i];
    }
    return fares;
}

TollRecord parse_record(const string& line) {
    TollRecord record;
    char colon;
    int month, day, hour, minute;
    string action;
    
    istringstream iss(line);
    iss >> record.license >> month >> colon >> day >> colon >> hour >> colon >> minute;
    iss >> action;
    record.is_enter = (action == "enter");
    iss >> record.location;
    
    record.time = time_to_minutes(day, hour, minute);
    return record;
}

double calculate_charges(const vector<int>& fares, const vector<TollRecord>& records) {
    map<string, double> bills;
    
    // Processa pares ordenados de enter/exit
    for (size_t i = 0; i < records.size(); ) {
        if (i + 1 >= records.size()) break;
        
        const TollRecord& first = records[i];
        const TollRecord& second = records[i+1];
        
        if (first.license == second.license && 
            first.is_enter && !second.is_enter) {
            
            int hour = first.time % (24 * 60) / 60;
            int distance = abs(second.location - first.location);
            double cost = (distance * fares[hour]) / 100.0 + 1.0;
            
            bills[first.license] += cost;
            i += 2; // Avança dois registros
        } else {
            i++; // Avança um registro
        }
    }
    
    for (const auto& [license, amount] : bills) {
        cout << license << " $" << fixed << setprecision(2) << amount + 2.0 << endl;
    }
    
    return 0;
}

void process_input() {
    int cases;
    cin >> cases;
    
    for (int case_num = 0; case_num < cases; ++case_num) {
        cin.ignore();
        string fare_line;
        getline(cin, fare_line);
        vector<int> fares = parse_fares(fare_line);
        
        vector<TollRecord> records;
        string line;
        while (getline(cin, line) && !line.empty()) {
            records.push_back(parse_record(line));
        }
        
        // Ordenação
        sort(records.begin(), records.end(), compare_records);
        
        if (case_num > 0) cout << endl;
        calculate_charges(fares, records);
    }
}
#include "../include/utilities.h"
#include <iostream>
#include <algorithm>

using namespace std;

unordered_map<string, vector<string>> collaboration_graph;
unordered_map<string, int> erdos_numbers;

// Extrair os autores de uma linha do artigo
vector<string> parse_authors(const string& line) {
    vector<string> authors;
    size_t end = line.find(':'); // fim da lista
    if (end == string::npos) return authors;

    string authors_part = line.substr(0, end); // separa os autores do título do artigo
    size_t pos = 0;
    
    while (pos < authors_part.length()) {
        size_t comma = authors_part.find(',', pos); // vírgula após o sobrenome
        if (comma == string::npos) break;
        
        size_t next_comma = authors_part.find(',', comma + 1); // vírgula após a inicial do nome
        string author = authors_part.substr(pos, (next_comma == string::npos ? end : next_comma) - pos);
        
        author.erase(remove(author.begin(), author.end(), '.'), author.end());
        author.erase(0, author.find_first_not_of(" \t"));
        author.erase(author.find_last_not_of(" \t") + 1);
        
        if (!author.empty()) {
            authors.push_back(author);
        }
        
        pos = (next_comma == string::npos) ? end : next_comma + 1;
    }
    
    return authors;
}

void add_paper(const vector<string>& authors) {
    for (const auto& author : authors) {
        if (collaboration_graph.find(author) == collaboration_graph.end()) {
            collaboration_graph[author] = vector<string>();
        }
    }
    
    for (size_t i = 0; i < authors.size(); ++i) {
        for (size_t j = i + 1; j < authors.size(); ++j) {
            collaboration_graph[authors[i]].push_back(authors[j]);
            collaboration_graph[authors[j]].push_back(authors[i]);
        }
    }
}

void calculate_erdos_numbers() {
    vector<string> current_level = {"Erdos, P"};
    int level = 0;
    
    while (!current_level.empty()) {
        vector<string> next_level;
        
        for (const auto& author : current_level) {
            if (erdos_numbers.find(author) == erdos_numbers.end()) {
                erdos_numbers[author] = level;
                
                for (const auto& collaborator : collaboration_graph[author]) {
                    if (erdos_numbers.find(collaborator) == erdos_numbers.end()) {
                        next_level.push_back(collaborator);
                    }
                }
            }
        }
        
        current_level = next_level;
        level++;
    }
}

void process_input() {
    int scenarios;
    cin >> scenarios;
    
    for (int scenario = 1; scenario <= scenarios; ++scenario) {
        int P, N;
        cin >> P >> N;
        cin.ignore(); // Ignora o \n após P e N
        
        // Limpa estruturas para novo cenário
        collaboration_graph.clear();
        erdos_numbers.clear();
        
        // Processa cada paper
        for (int i = 0; i < P; ++i) {
            string line;
            getline(cin, line);
            vector<string> authors = parse_authors(line);
            add_paper(authors);
        }
        
        // Calcula números de Erdos
        calculate_erdos_numbers();
        
        // Processa consultas
        cout << "Scenario " << scenario << endl;
        for (int i = 0; i < N; ++i) {
            string name;
            getline(cin, name);
            
            // Normaliza o nome da consulta
            string normalized = name;
            normalized.erase(remove(normalized.begin(), normalized.end(), '.'), normalized.end());
            normalized.erase(0, normalized.find_first_not_of(" \t"));
            normalized.erase(normalized.find_last_not_of(" \t") + 1);
            
            // Busca o número
            auto it = erdos_numbers.find(normalized);
            if (it != erdos_numbers.end()) {
                cout << name << " " << it->second << endl;
            } else {
                cout << name << " infinity" << endl;
            }
        }
    }
}
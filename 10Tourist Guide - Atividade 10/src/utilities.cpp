#include "../include/utilities.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// aresta do grafo
struct Edge {
    int dest; 
    int capacity;
};

// encontra o caminho com a maior capacidade mínima entre start e end
int find_max_min_path(vector<vector<Edge>>& graph, int start, int end, int n) {
    vector<int> max_capacity(n+1, 0);
    vector<bool> visited(n+1, false);  // vetor para marcar cidades visitadas
    
    max_capacity[start] = INT_MAX;
    
    for (int i = 1; i <= n; ++i) {
        int u = -1;
        for (int j = 1; j <= n; ++j) {
            if (!visited[j] && (u == -1 || max_capacity[j] > max_capacity[u])) {
                u = j;
            }
        }
        
        if (u == -1 || u == end) break;
        visited[u] = true;
        
        for (const Edge& e : graph[u]) {
            int v = e.dest;
            int min_cap = min(max_capacity[u], e.capacity);
            if (min_cap > max_capacity[v]) {
                max_capacity[v] = min_cap;
            }
        }
    }
    
    return max_capacity[end];
}

void process_input() {
    int scenario = 1;
    int n, r;
    while (cin >> n >> r, n != 0 || r != 0) {
        vector<vector<Edge>> graph(n+1);
        
        for (int i = 0; i < r; ++i) {
            int c1, c2, p;
            cin >> c1 >> c2 >> p;
            graph[c1].push_back({c2, p});
            graph[c2].push_back({c1, p});
        }
        
        int s, d, t;
        cin >> s >> d >> t;
        
        int max_min_capacity = find_max_min_path(graph, s, d, n);
        int trips = (t + max_min_capacity - 1 - 1) / (max_min_capacity - 1);
        
        cout << "Scenario #" << scenario++ << endl;
        cout << "Minimum Number of Trips = " << trips << endl << endl;
    }
}

int calculate_min_trips(int max_passengers, int num_tourists) {
    return (num_tourists + max_passengers - 1 - 1) / (max_passengers - 1);
}
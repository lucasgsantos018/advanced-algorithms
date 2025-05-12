#include "../include/utilities.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const string face_names[6] = {"front", "back", "left", "right", "top", "bottom"};

void solve_tower_problem(const vector<vector<int>>& cubes) {
    int n = cubes.size();
    vector<vector<pair<int, string>>> dp(n, vector<pair<int, string>>(6, {1, ""}));
    int max_height = 1;
    pair<int, int> last_cube = {0, 0};

    // faces opostas
    const int opposite[6] = {1, 0, 3, 2, 5, 4};

    // tabela DP
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < 6; ++j) {
            dp[i][j] = {1, ""};  // inicializa com um único cubo
            for (int k = 0; k < i; ++k) {
                for (int l = 0; l < 6; ++l) {
                    if (cubes[i][j] == cubes[k][opposite[l]]) { // se achar uma sequencia mais longa, atualiza
                        if (dp[k][l].first + 1 > dp[i][j].first) {
                            dp[i][j].first = dp[k][l].first + 1;
                            dp[i][j].second = to_string(k+1) + " " + face_names[l];
                        }
                    }
                }
            }
            if (dp[i][j].first > max_height) { // atualiza a altura máxima
                max_height = dp[i][j].first;
                last_cube = {i, j};
            }
        }
    }

    // reconstroi a solução a partir do cubo final
    vector<string> solution;
    int current_cube = last_cube.first;
    int current_face = last_cube.second;

    while (dp[current_cube][current_face].first > 1) {
        solution.push_back(to_string(current_cube+1) + " " + face_names[current_face]);
        string prev = dp[current_cube][current_face].second;
        size_t space_pos = prev.find(' ');
        current_cube = stoi(prev.substr(0, space_pos)) - 1;
        current_face = distance(face_names, find(face_names, face_names+6, prev.substr(space_pos+1)));
    }
    solution.push_back(to_string(current_cube+1) + " " + face_names[current_face]);

    // output
    cout << max_height << endl;
    for (auto it = solution.rbegin(); it != solution.rend(); ++it) {
        cout << *it << endl;
    }
}

void process_input() {
    int case_num = 1;
    int n;
    while (cin >> n, n != 0) {
        vector<vector<int>> cubes(n, vector<int>(6));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 6; ++j) {
                cin >> cubes[i][j];
            }
        }

        cout << "Case #" << case_num++ << endl;
        solve_tower_problem(cubes);
        cout << endl;
    }
}
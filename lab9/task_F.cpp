#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
void dfs (int v, vector<int> &position, vector<vector<int>> &g) {
 
    for (int to : g[v]) {
        if (position[to] == 0)
            dfs (to, position, g);
    }
    if (g[v].empty()) {
        position[v] = -1;
        return;
    }
    position[v] = -1;
    for (int to : g[v]) {
        if (position[to] == -1) {
            position[v] = 1;
            return;
        }
    }
}
 
int main() {
    ifstream input_file("game.in");
    ofstream output_file("game.out");
 
    int ver, edges, start_point;
    input_file >> ver >> edges >> start_point;
    start_point--;
    vector<vector<int>> g (ver);
    vector<int> position (ver, 0);
 
    for (int i = 0; i < edges; i++) {
        int ver1, ver2;
        input_file >> ver1 >> ver2;
            ver1--;
            ver2--;
            g[ver1].push_back(ver2);
    }
 
    dfs (start_point, position, g);
    if (position[start_point] == 1)
        output_file << "First player wins";
    else
        output_file << "Second player wins";
 
    output_file.close();
    input_file.close();
 
    return 0;
}

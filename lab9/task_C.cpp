#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
inline char invert(int c) {
    return c == 1 ? 2 : 1;
}
 
void dfs(int v, char c,  vector<char>& colour, vector<vector<int>>& g, bool& b) {
    colour[v] = c;
 
    for (int u: g[v]) {
        if (colour[u] == 0) {
            (dfs(u, invert(c), colour, g, b));
        } else if (colour[u] == c) {
          b = true;
        }
    }
}
 
int main() {
 
    ifstream input_file ("bipartite.in");
    ofstream output_file ("bipartite.out");
 
    int ver, edges;
    input_file >> ver >> edges;
    vector<vector<int>> adj_lists (ver);
    vector<char> colour (ver);
    bool bipartite = false;
 
 
    for (int i = 0; i < edges; i++) {
        int ver1, ver2;
        input_file >> ver1 >> ver2;
        ver1--; ver2--;
        adj_lists[ver1].push_back(ver2);
        adj_lists[ver2].push_back(ver1);
    }
 
    for (int i = 0; i < ver; i++) {
        if (colour[i] == 0) {
            dfs(i, 1, colour, adj_lists, bipartite);
        }
    }
 
    if (bipartite)
        output_file << "NO";
    else
        output_file << "YES";
        
    input_file.close();
    output_file.close();
 
    return 0;
}

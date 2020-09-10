#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
 
 
void dfs1 (int v, vector<bool> &used, vector<int> &order, vector<vector<int>> &g) {
    used[v] = true;
    for (int el : g[v])
        if (!used[el])
            dfs1 (el, used, order, g);
    order.push_back (v);
}
 
void dfs2 (int v, int count, vector<bool> &used, vector<int> &component, vector<vector<int>> &gr) {
    used[v] = true;
    component[v] = count;
    for (int el : gr[v])
        if (!used[el] )
            dfs2 (el, count, used, component, gr);
}
 
int main() {
 
    ios_base::sync_with_stdio(false); std::cin.tie(NULL);
 
    ifstream input_file("cond.in");
    ofstream output_file("cond.out");
 
    int ver, edges;
    input_file >> ver >> edges;
    int count = 1;
    vector<vector<int>> g(ver), gr(ver);
    vector<bool> used(ver);
    vector<int> order, component (ver);
 
 
    for (int i = 0; i < ver; i++) {
        g.emplace_back(vector<int>());
        gr.emplace_back(vector<int>());
    }
    for (int i = 0; i < edges; i++) {
        int ver1, ver2;
        input_file >> ver1 >> ver2;
        ver1--; ver2--;
        g[ver1].push_back(ver2);
        gr[ver2].push_back(ver1);
    }
 
    used.assign (ver, false);
    for (int i=0; i<ver; i++)
        if (!used[i])
            dfs1 (i, used, order, g);
    used.assign (ver, false);
    for (int i=0; i<ver; i++) {
        int v = order[ver-1-i];
        if (!used[v]) {
            dfs2 (v, count, used, component, gr);
            count++;
        }
    }
 
    output_file << count-1 << "\n";
    for (int el : component) {
        output_file << el << " ";
    }
 
    output_file.close();
    input_file.close();
 
        return 0;
}

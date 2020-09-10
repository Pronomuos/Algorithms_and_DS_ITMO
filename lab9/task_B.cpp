#include <iostream>
#include <fstream>
#include <vector>
 
 
using namespace std;
 
void dfs (int v, vector<int> &used, vector<vector<int>> &g, bool &cycle, vector<int> &p,
        int &cycle_end, int &cycle_start) {
    used[v] = 1;
        for (int to : g[v]) {
            if (used[to] == 0) {
                p[to] = v;
                dfs(to, used, g, cycle, p, cycle_end, cycle_start);
            } else if (used[to] == 1) {
                cycle = true;
                cycle_end = v;
                cycle_start = to;
            }
        }
        used[v] = 2;
}
 
int main() {
 
    ifstream input_file ("cycle.in");
    ofstream output_file ("cycle.out");
 
    int ver, edges;
    input_file >> ver >> edges;
    vector<vector<int>> g (ver);
    vector<int> used (ver);
    vector<int> p (ver);
    vector<int> q;
    bool cycle = false;
    int cycle_end = 0;
    int cycle_start = 0;
 
 
    for (int i = 0; i < edges; i++) {
        int ver1, ver2;
        input_file >> ver1 >> ver2;
        ver1--; ver2--;
        g[ver1].push_back(ver2);
    }
 
    for (int i=0; i < ver; ++i) {
        if (!cycle && !used[i])
            dfs(i, used, g, cycle, p, cycle_end, cycle_start);
    }
 
        if (cycle) {
           q.push_back(cycle_start);
           int k = cycle_end;
           while (k!=cycle_start) {
               q.push_back(k);
               k = p[k];
           }
           output_file << "YES\n";
           for (int i = q.size()-1; i>=0; i--)
               output_file << q[i]+1 << " ";
        } else
            output_file << "NO";
            
        input_file.close(); 
        output_file.close();
 
        return 0;
}

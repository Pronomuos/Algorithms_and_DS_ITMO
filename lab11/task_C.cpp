#include <iostream>
#include <vector>
#include <fstream>
#include <set>
 
using namespace std;
 
void dijkstra (int st, vector<vector<pair<int, int>>> &g, vector<long long> &d) {
    d[st] = 0;
    set<pair<long long, int> > q;
    q.insert (make_pair (d[st], st));
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase (q.begin());
 
        for (auto edge : g[v]) {
            int to = edge.first,
                    len = edge.second;
            if (d[v] + len < d[to]) {
                q.erase (make_pair (d[to], to));
                d[to] = d[v] + len;
                q.insert (make_pair (d[to], to));
            }
        }
    }
}
 
int main() {
 
    ifstream input_file ("pathbgep.in");
    ofstream output_file("pathbgep.out");
 
 
    int ver, edges;
    input_file >> ver >> edges;
    vector<vector<pair<int, int>>> g (ver);
 
    for (int i = 0; i < edges; i++) {
        int ver1, ver2, cost;
        input_file >> ver1 >> ver2 >> cost;
        ver1--; ver2--;
        g[ver1].push_back(make_pair(ver2, cost));
        g[ver2].push_back(make_pair(ver1, cost));
    }
 
        vector<long long> d(ver, LLONG_MAX);
        dijkstra(0, g, d);
        for (int j = 0; j < ver; j++)
            output_file << d[j] << " ";
 
 
    output_file.close();
    input_file.close();
 
    return 0;
}

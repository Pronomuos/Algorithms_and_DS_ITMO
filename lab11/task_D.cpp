#include <iostream>
#include <vector>
#include <fstream>
 
 
using namespace std;
const long long INF = 8e18;
 
struct edge {
    int from, to;
    long long cost;
};
 
bool find (vector<int> &v, int num) {
    for (int el : v)
        if (el == num)
            return true;
 
 
        return false;
}
 
void dfs(int ver, vector<vector<int>> &g, vector<bool> &visited) {
    visited[ver] = true;
    for (auto to : g[ver])
        if (!visited[to])
            dfs(to, g, visited);
}
 
void solve (int st, vector<edge> &edges, vector<long long> &d, vector<vector<int>> &g, vector<int> &p) {
    d[st] = 0;
    vector<int> q;
    for (int i = 0; i < g.size(); i++) {
        q.clear();
        for (auto &e : edges)
            if (d[e.from] < INF)
                if (d[e.to] > d[e.from] + e.cost) {
                    d[e.to] = max (-INF, d[e.from] + e.cost);
                    p[e.to] = e.from;
                    if (!find(q, e.to))
                        q.push_back(e.to);
                }
        if (q.empty())
            break;
    }
 
    while (!q.empty()) {
        int x = q.back();
        q.pop_back();
        for (int i = 0; i < g.size(); i++)
            x = p[x];
 
        vector<bool> visited (g.size(), false);
        dfs (x, g, visited);
 
        for (int i = 0; i < g.size(); i++)
            if (visited[i])
                d[i] = -INF;
    }
}
 
int main() {
 
    ifstream input_file ("path.in");
    ofstream output_file("path.out");
 
    int ver, edges_num, st;
    input_file >> ver >> edges_num >> st;
    st--;
    vector<edge> edges;
    vector<int> p (ver, -1);
    vector<vector<int>> g (ver);
    for (int i = 0; i < edges_num; i++) {
        int from, to;
        long long cost;
        input_file >> from >> to >> cost;
        from--; to--;
        edges.push_back({from, to, cost});
        g[from].push_back(to);
    }
 
    vector<long long> d (ver, INF);
    solve(st, edges, d, g, p);
 
    for (int i = 0; i < ver; i++) {
        switch (d[i]) {
            case -INF:
                output_file << "-\n";
                break;
            case INF:
                output_file << "*\n";
                break;
            default:
                output_file << d[i] << "\n";
        }
    }
 
    output_file.close();
    input_file.close();
 
    return 0;
}

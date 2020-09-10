#include <iostream>
#include <vector>
#include <fstream>
#include <list>
 
 
using namespace std;
 
 
struct Edge {
    int to, from;
    long flow, capacity;
};
 
bool bfs (int s, int t, vector<vector<Edge>> &g, vector<int> &layered_g) {
 
    layered_g.assign (layered_g.size(), -1);
    layered_g [s] = 0;
 
    list<int> q;
    q.push_back(s);
 
    while (!q.empty()) {
        int from = q.front();
        q.pop_front();
        for (auto edge : g[from])
            if (layered_g[edge.to] < 0 && edge.flow < edge.capacity) {
                layered_g [edge.to] = layered_g [from] + 1;
                q.push_back(edge.to);
            }
    }
 
    return layered_g[t] >= 0;
 
}
 
long dfs (int from, long flow, int t, vector<vector<Edge>> &g, vector<int> &start, vector<int> &layered_g) {
 
    if (from == t)
         return flow;
 
    for (  ; start[from] < g[from].size(); start[from]++)
    {
        Edge &edge = g[from][start[from]];
        if (layered_g[edge.to] == layered_g[from] + 1 && edge.flow < edge.capacity) {
 
            long curr_flow = min (flow, edge.capacity - edge.flow);
            long temp_flow = dfs (edge.to, curr_flow, t, g, start, layered_g);
 
            if (temp_flow > 0) {
                edge.flow += temp_flow;
                g[edge.to][edge.from].flow -= temp_flow;
                return temp_flow;
            }
        }
    }
 
    return 0;
}
 
long dinicMaxFlow (int s, int t, vector<vector<Edge>> &g) {
 
    if (s == t)
        return -1;
 
    long maxFlow = 0;
    vector<int> layered_g (g.size(), -1);
 
    while (bfs(s, t, g, layered_g)) {
 
        vector<int> start (g.size() + 1);
        while (long flow = dfs(s, LONG_MAX, t, g, start, layered_g)) {
            maxFlow += flow;
        }
    }
 
    return maxFlow;
}
 
 
int main() {
 
    ifstream input_file ("maxflow.in");
    ofstream output_file("maxflow.out");
 
    int ver, edges;
    input_file >> ver >> edges;
 
    vector<vector<Edge>> g (ver);
    for (int i = 0; i < edges; i++) {
        int from, to;
        long cap;
        input_file >> from >> to >> cap;
        from--;
        to--;
        g[from].push_back({to, (int) g[to].size(),0, cap });
        g[to].push_back({from, (int) g[from].size(), 0, 0});
    }
 
    long maxFlow = dinicMaxFlow(0, ver - 1, g);
 
    output_file << maxFlow;
 
 
    output_file.close();
    input_file.close();
 
    return 0;
}

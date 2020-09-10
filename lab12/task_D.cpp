#include <iostream>
#include <vector>
#include <fstream>
#include <list>
 
using namespace std;
 
struct Edge {
    int to, flow, capacity, id;
};
 
class Dinic {
private:
    vector<vector<int>> g;
    vector<Edge> edges;
    vector<int> start;
    vector<int> layered_g;
    int m_ver = 0;
public:
    Dinic (int ver) : m_ver(ver) {
        g.resize(ver);
        start.resize(ver, 0);
        layered_g.resize(ver, 0);
    }
 
    bool bfs(int s, int t) {
 
        layered_g.assign(m_ver, 0);
        layered_g[s] = 1;
 
        list<int> q;
        q.push_back(s);
 
        while (!q.empty() && !layered_g[t]) {
            int from = q.front();
            q.pop_front();
            for (int index : g[from]) {
                if (edges[index].flow >= edges[index].capacity)
                    continue;
                if (!layered_g[edges[index].to]) {
                    layered_g[edges[index].to] = layered_g[from] + 1;
                    q.push_back(edges[index].to);
                }
            }
        }
        return layered_g[t];
    }
 
    int dfs(int from, int flow, int t) {
        if (!flow)
            return 0;
        if (from == t)
            return flow;
 
        for (; start[from] < g[from].size(); start[from]++) {
            int index = g[from][start[from]];
            if (layered_g[edges[index].to] == layered_g[from] + 1) {
 
                int curr_flow = min(flow, edges[index].capacity - edges[index].flow);
                int temp_flow = dfs(edges[index].to, curr_flow, t);
 
                if (temp_flow > 0) {
                    edges[index].flow += temp_flow;
                    edges[index^1].flow -= temp_flow;
                    return temp_flow;
                }
            }
        }
        return 0;
    }
 
    int dinicMaxFlow(int s, int t) {
        if (s == t)
            return -1;
 
        int maxFlow = 0;
        while (bfs(s, t)) {
            while (int flow = dfs(s, INT_MAX, t))
                maxFlow += flow;
            start.assign(m_ver, 0);
        }
        return maxFlow;
    }
 
    void add_edge(int to, int from, int cap, int id) {
        g[from].push_back(edges.size());
        edges.push_back({to, 0, cap, id});
        g[to].push_back(edges.size());
        edges.push_back({from, 0, 0, id});
    }
 
    bool circulation() {
        dinicMaxFlow(0, m_ver - 1);
        for (int index : g[0])
            if (edges[index].flow != edges[index].capacity)
                return false;
 
        return true;
    }
 
    void print_result (ofstream &out) {
        if (circulation()) {
            out << "YES\n";
            for (int index : g[0])
                out << edges[index].capacity + edges[edges[index].id].flow << "\n";
        }
        else
            out << "NO";
    }
};
 
int main() {
 
    ifstream input_file ("circulation.in");
    ofstream output_file("circulation.out");
 
    int ver, edges_num;
    input_file >> ver >> edges_num;
 
    Dinic d (ver + 2);
    for (int id = 0; id < edges_num; id++) {
        int from, to, minCap, maxCap;
        input_file >> from >> to >> minCap >> maxCap;
        d.add_edge(to, from, maxCap - minCap, id * 6);
        d.add_edge (to, 0, minCap, id * 6);
        d.add_edge(ver + 1, from, minCap, id * 6);
    }
 
    d.print_result(output_file);
 
    output_file.close();
    input_file.close();
 
    return 0;
}

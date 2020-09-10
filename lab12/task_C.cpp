#include <iostream>
#include <vector>
#include <fstream>
#include <list>
 
using namespace std;
 
struct Edge {
    int to, flow, capacity;
};
 
class Dinic {
private:
    vector<vector<int>> g;
    vector<Edge> edges;
    vector<int> start;
    vector<int> layered_g;
    vector<int> path;
    vector<vector<int>> v_decomposition;
    int m_ver = 0;
public:
    Dinic (int ver) : m_ver(ver) {
        g.resize(ver);
        start.resize(ver);
        layered_g.resize(ver);
    }
 
    bool bfs(int s, int t) {
 
        layered_g.assign(m_ver, -1);
        layered_g[s] = 0;
 
        list<int> q;
        q.push_back(s);
 
        while (!q.empty() && layered_g[t] < 0) {
            int from = q.front();
            q.pop_front();
            for (int index : g[from])
                if (layered_g[edges[index].to] < 0 && edges[index].flow < edges[index].capacity) {
                    layered_g[edges[index].to] = layered_g[from] + 1;
                    q.push_back(edges[index].to);
                }
        }
        return layered_g[t] >= 0;
    }
 
    int dfs(int from, int flow, int t) {
        if (from == t)
            return flow;
 
        for (; start[from] < g[from].size(); start[from]++) {
            int index = g[from][start[from]];
            if (layered_g[edges[index].to] == layered_g[from] + 1 &&
                edges[index].flow < edges[index].capacity) {
 
                int curr_flow = min(flow, edges[index].capacity - edges[index].flow);
                int temp_flow = dfs(edges[index].to, curr_flow, t);
 
                if (temp_flow > 0) {
                    edges[index].flow += temp_flow;
                    edges[index ^ 1].flow -= temp_flow;
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
        layered_g.assign(m_ver, -1);
 
        while (bfs(s, t)) {
 
            start.assign(m_ver, 0);
            while (int flow = dfs(s, INT_MAX, t))
                maxFlow += flow;
            start.assign(m_ver, 0);
        }
        return maxFlow;
    }
 
    void add_edge(int to, int from, int cap) {
        g[from].push_back(edges.size());
        edges.push_back({to, 0, cap});
        g[to].push_back(edges.size());
        edges.push_back({from, 0, 0});
    }
 
     int find_path (int s, int flow = INT_MAX) {
        if (s == m_ver - 1)
            return flow;
 
        for (int next : g[s]) {
            if (edges[next].flow > 0)
                if ((flow = find_path(edges[next].to, min(flow, edges[next].flow)))) {
                    path.push_back((next >> 1) + 1);
                    edges[next].flow -= flow;
                    return flow;
                }
            }
 
        return 0;
    }
 
    void decomposition () {
 
        dinicMaxFlow(0, m_ver - 1);
        while (int path_flow = find_path(0)) {
            path.push_back(path.size());
            path.push_back(path_flow);
            v_decomposition.push_back(path);
            path.clear();
        }
    }
 
    void print_result (ofstream &out) {
        out << v_decomposition.size() << "\n";
        for (auto &p : v_decomposition) {
            for (int i = p.size() - 1; i >= 0; i--)
                out << p[i] << " ";
            out << "\n";
 
        }
    }
 
};
 
int main() {
 
    ifstream input_file ("decomposition.in");
    ofstream output_file("decomposition.out");
 
    int ver, edges_num;
    input_file >> ver >> edges_num;
 
    Dinic d (ver);
    for (int i = 0; i < edges_num; i++) {
       int from, to, cap;
       input_file >> from >> to >> cap;
       from--;
       to--;
       d.add_edge(to, from, cap);
    }
 
    d.decomposition();
    d.print_result(output_file);
 
 
    output_file.close();
    input_file.close();
 
    return 0;
}

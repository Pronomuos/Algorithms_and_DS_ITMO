#include <iostream>
#include <vector>
#include <fstream>
 
 
using namespace std;
const long long INF = 1e12 + 7;
 
struct edge {
    int from, to;
    long long cost;
};
 
void solve (int ver, vector<edge> &edges, vector<int> &path) {
    vector<int> p (ver, -1);
    vector<long long> d (ver, INF);
    int iter_happened = -1;
    for (int i = 0; i < ver; i++) {
        iter_happened = -1;
        for (auto &e : edges)
                if (d[e.to] > d[e.from] + e.cost) {
                    d[e.to] = max (-INF, d[e.from] + e.cost);
                    p[e.to] = e.from;
                    iter_happened = e.to;
                }
        if (iter_happened == -1)
            break;
 
    }
 
    if (iter_happened != -1) {
        int x = iter_happened;
        for (int i = 0; i < ver; i++)
            x = p[x];
 
        int x2 = x;
        do
        {
            path.push_back(x2);
            x2 = p[x2];
        } while (x2 != x);
        path.push_back(x2);
 
    }
}
 
int main() {
 
    ifstream input_file ("negcycle.in");
    ofstream output_file("negcycle.out");
 
    int ver;
    input_file >> ver;
    vector<edge> edges;
    vector<int> path;
    vector<int> p (ver, -1);
    for (int from = 0; from < ver; from++)
        for (int to = 0; to < ver; to++) {
            long long cost;
            input_file >> cost;
            if (cost != 1e9)
                edges.push_back({from, to, cost});
    }
 
    vector<long long> d (ver, INF);
    solve(ver, edges, path);
 
    if (path.empty())
        output_file << "NO\n";
    else {
        output_file << "YES\n" << path.size() << "\n";
        for (int i = path.size() - 1; i >= 0; i--)
            output_file << path[i] + 1 << " ";
    }
 
 
    output_file.close();
    input_file.close();
 
    return 0;
}

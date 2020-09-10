#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
void dfs (int ver, vector<bool> &used, const vector<vector<pair<int, int>>>  &g) {
    used[ver] = true;
    for (auto to : g[ver]) {
        if (!used[to.first])
            dfs (to.first, used, g);
    }
}
 
void dfs (int ver, vector<bool> &used, const vector<vector<int>>  &g) {
    used[ver] = true;
    for (auto to : g[ver]) {
        if (!used[to])
            dfs (to, used, g);
    }
}
 
void dfs1 (int v, vector<bool> &used, vector<int> &order, vector<vector<int>> &g) {
    used[v] = true;
    for (auto to : g[v])
        if (!used[to])
            dfs1(to, used, order, g);
        order.push_back(v);
 
}
 
void dfs2 (int v, int count, vector<bool> &used, vector<int> &components, vector<vector<int>> &tr_g) {
    used[v] = true;
    components[v] = count;
    for (auto to : tr_g[v]) {
        if (!used[to])
            dfs2(to, count, used, components, tr_g);
    }
}
 
bool connected_g (int root, int ver, vector<vector<pair<int, int>>> &g) {
    vector<bool> used(ver, false);
    dfs(root, used, g);
    for (auto el : used)
        if (!el)
            return false;
 
        return true;
}
 
bool connected_g (int root, int ver, vector<vector<int>> &g) {
    vector<bool> used(ver, false);
    dfs(root, used, g);
    for (auto el : used)
        if (!el)
            return false;
 
    return true;
}
 
void cond (vector<vector<int>> &g, int ver, int &count, vector<int> &components) {
 
    vector<bool> used (ver);
    vector<int> order;
    vector<vector<int>> tr_g(ver);
    for (int i = 0; i < ver; i++)
        for (auto to : g[i])
                tr_g[to].push_back(i);
 
    used.assign(ver, false);
    for (int i = 0; i < ver; i++)
        if (!used[i]) {
            dfs1(i, used, order, g);
        }
 
    used.assign(ver, false);
    for (int i = 0; i < ver; i++) {
        int v = order[ver - 1 - i];
        if (!used[v]) {
            count++;
            dfs2(v, count, used, components, tr_g);
        }
    }
}
 
void findMST (vector<vector<pair<int, int>>> &g, int ver, int root, long long &res) {
 
    vector<int> min_edges(ver, 1000000000);
    min_edges[root] = 0;
    for (const auto &list : g)
        for (auto edge : list)
            min_edges[edge.first] = min(edge.second, min_edges[edge.first]);
 
    for (auto min_edge : min_edges)
        res += min_edge;
 
    vector<vector<int>> zero_g(ver);
    for (int i = 0; i < ver; i++)
        for (auto edge : g[i])
            if (edge.second == min_edges[edge.first])
                zero_g[i].push_back(edge.first);
 
    if (connected_g(root, ver, zero_g))
        return;
 
    int count = -1;
    vector<int> new_components(ver);
    cond(zero_g, ver, count, new_components);
    vector<vector<pair<int, int>>> new_g(count + 1);
 
    for (int i = 0; i < ver; i++)
        for (auto edge : g[i])
            if (new_components[i] != new_components[edge.first])
        new_g[new_components[i]].push_back(make_pair(new_components[edge.first], edge.second - min_edges[edge.first]));
 
    findMST(new_g, count + 1, new_components[root], res);
}
 
int main() {
 
    ifstream input_file("chinese.in");
    ofstream output_file("chinese.out");
 
    int ver, edges;
    input_file >> ver >> edges;
    vector<vector<pair<int, int>>> g (ver);
    vector<bool> used(ver, false);
 
    for (int i = 0; i < edges; i++) {
        int ver1, ver2, cost;
        input_file >> ver1 >> ver2 >> cost;
        ver1--;
        ver2--;
        if (ver2 != 0)
        g[ver1].push_back(make_pair(ver2, cost));
    }
 
    if (connected_g(0, ver, g)) {
        output_file << "YES\n";
        long long res = 0;
        findMST (g, ver, 0, res);
        output_file << res;
 
    }
    else {
        output_file << "NO\n";
    }
 
    output_file.close();
    input_file.close();
 
    return 0;
}

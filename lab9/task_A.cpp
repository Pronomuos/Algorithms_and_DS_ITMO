#include <iostream>
#include <fstream>
#include <vector>
 
void dfs (int ver, std::vector<bool>& used, std::vector<int>& ans,
          std::vector<std::vector<int>>& adj_lists, std::vector<int>& colour, bool& cycle) {
    used[ver] = true;
    colour[ver] = true;
    for (size_t i=0; i<adj_lists[ver].size(); ++i) {
        int to = adj_lists[ver][i];
        if (!used[to])
            dfs (to, used, ans, adj_lists, colour, cycle);
        else if (colour[to])
            cycle = true;
    }
    ans.push_back (ver);
    colour[ver] = false;
}
 
int main() {
 
    std::ifstream input_file ("topsort.in");
    std::ofstream output_file ("topsort.out");
 
    int ver, edges;
    input_file >> ver >> edges;
    std::vector<bool> used (ver);
    std::vector<std::vector<int>> adj_lists (ver);
    std::vector<int> ans;
    std::vector<int> colour (ver);
    bool cycle = false;
 
    for (int i = 0; i < edges; i++) {
        int ver1, ver2;
        input_file >> ver1 >> ver2;
        ver1--; ver2--;
        adj_lists[ver1].push_back(ver2);
    }
 
    for (int i=0; i<ver; ++i)
        used[i] = false;
    ans.clear();
    for (int i=0; i<ver; ++i)
        if (!used[i])
            dfs (i, used, ans, adj_lists, colour, cycle);
 
    if (!cycle)
    for (int i = ans.size()-1; i >= 0; i--) {
        output_file << ans[i]+1 << " ";
    }
    else
        output_file << -1;
 
 
    return 0;
}

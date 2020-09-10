#include <iostream>
#include <fstream>
#include <vector>
 
 
void dfs (int ver, std::vector<bool>& used, std::vector<int>& ans,
          std::vector<std::vector<int>>& g) {
    used[ver] = true;
    for (auto to : g[ver]) {
        if (!used[to])
            dfs (to, used, ans, g);
    }
    ans.push_back (ver);
}
 
 
 
int main() {
 
    std::ifstream input_file ("hamiltonian.in");
    std::ofstream output_file ("hamiltonian.out");
 
    int ver, edges;
    input_file >> ver >> edges;
    std::vector<bool> used (ver);
    std::vector<std::vector<int>> g (ver);
    std::vector<int> ans;
 
    for (int i = 0; i < edges; i++) {
        int ver1, ver2;
        input_file >> ver1 >> ver2;
        ver1--;
        ver2--;
        g[ver1].push_back(ver2);
    }
 
    used.assign(ver,false);
    ans.clear();
    for (int i=0; i<ver; ++i)
        if (!used[i])
            dfs(i, used, ans, g);
 
 
    int count = 0;
    size_t size = ans.size() - 1;
    for (size_t i = size; i > 0; i--)
        for (auto to : g[ans[i]])
            if (to == ans[i - 1]) {
                count++;
                break;
            }
 
        if (count == size)
            output_file << "YES";
        else
            output_file << "NO";
 
        input_file.close();
        output_file.close();
 
 
 
    return 0;
}

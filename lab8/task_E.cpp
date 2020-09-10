#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
 
 
int main() {
 
    std::ifstream input_file("pathbge1.in");
    std::ofstream output_file("pathbge1.out");
 
    int vertices, edges;
    input_file >> vertices >> edges;
    std::queue<int> q;
    q.push (0);
    std::vector<bool> used (vertices);
    used[0] = true;
    std::vector<int> path (vertices);
    path[0] = 0;
    std::vector<std::vector<int>> adj_lists (vertices);
 
    for (int i = 0; i < vertices; i++) {
        adj_lists.emplace_back(std::vector<int>());
    }
 
    for (int i = 0; i < edges; i++) {
        int ver1, ver2;
        input_file >> ver1 >> ver2;
        ver1--; ver2--;
        adj_lists[ver1].push_back(ver2);
        adj_lists[ver2].push_back(ver1);
    }
 
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (size_t i = 0; i < adj_lists[v ].size(); ++i) {
            int to = adj_lists[v][i];
            if (!used[to]) {
                q.push(to);
                used[to] = true;
                path[to] = path[v] + 1;
            }
        }
    }
 
    for (int i = 0; i < vertices; i++){
        output_file  << path[i] << " ";
    }
 
    input_file.close();
    output_file.close();
 
    return 0;
}

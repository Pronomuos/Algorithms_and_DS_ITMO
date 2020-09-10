#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
 
int main() {
 
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
 
    std::ifstream input_file("components.in");
    std::ofstream output_file("components.out");
 
    int vertices, edges;
    input_file >> vertices >> edges;
    std::queue<int> q;
    std::vector<bool> used(vertices);
    std::vector<int> c_p(vertices);
    std::vector<std::vector<int>> adj_lists (vertices);
    int count = 0;
 
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
 
    for (int n = 0; n < vertices; n++) {
        if (!used[n]) {
            count++;
            q.push(n);
            used[n] = true;
            c_p[n] = count;
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (size_t i = 0; i < adj_lists[v].size(); ++i) {
                int to = adj_lists[v][i];
                if (!used[to]) {
                    q.push(to);
                    used[to] = true;
                    c_p[to] = count;
                }
            }
        }
    }
 
    output_file << count << '\n';
    for (int i = 0; i < vertices; i++){
        output_file  << c_p[i] << " ";
    }
 
    input_file.close();
    output_file.close();
 
    return 0;
}

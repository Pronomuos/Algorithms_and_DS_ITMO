#include <iostream>
#include <vector>
#include <fstream>
 
 
using namespace std;
 
bool dfs (int x, vector<vector<int>> &x_to_y, vector<bool> &visited, vector<int> &py) {
 
    if (visited[x])
        return false;
 
    visited[x] = true;
    for (int y : x_to_y[x])
        if (py[y] == -1 || dfs(py[y], x_to_y, visited, py)) {
            py[y] = x;
            return true;
        }
 
    return false;
}
 
int kuhn (vector<vector<int>> &x_to_y,  vector<int> &py) {
 
    vector<bool> visited (x_to_y.size(), false);
    int count = 0;
 
        for (int x = 0; x < x_to_y.size(); x++) {
            visited.assign (x_to_y.size(), false);
                if (dfs(x, x_to_y, visited, py))
                    count++;
 
    }
 
    return count;
 
}
 
int main() {
 
    ifstream input_file ("matching.in");
    ofstream output_file("matching.out");
 
    int ver1, ver2, edges;
    input_file >> ver1 >> ver2 >> edges;
    bool xySwapped = false;
    if (ver1 > ver2) {
        swap(ver1, ver2);
        xySwapped = true;
    }
    vector<vector<int>> x_to_y (ver1);
    for (int i = 0; i < edges; i++) {
        int x, y;
        if (!xySwapped)
            input_file >> x >> y;
        else
            input_file >> y >> x;
        x--;
        y--;
        x_to_y[x].push_back(y);
    }
 
    vector<int> py (ver2, -1);
 
    int result = kuhn (x_to_y, py);
 
    output_file << result;
 
    output_file.close();
    input_file.close();
 
    return 0;
}

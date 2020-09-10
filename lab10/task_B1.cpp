#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
 
using namespace std;
 
 
int main() {
 
    ifstream input_file("spantree.in");
    ofstream output_file("spantree.out");
 
 
    int ver;
    input_file >> ver;
    vector<pair<int, int>> point;
    float g [ver][ver];
    const int INF = 1000000000;
    vector<float> min_e(ver, INF);
    min_e[0] = 0;
    vector<bool> used(ver, false);
    float count = 0;
 
    for (int i = 0; i < ver; i++) {
        int X, Y;
        input_file >> X >> Y;
        point.emplace_back(make_pair(X, Y));
    }
 
    g[ver-1][ver-1] = INF;
    for (int i = 0; i < ver-1; i++) {
        for (int j = i; j < ver; j++) {
            if (i == j)
                g[i][j] = INF;
            else {
                float val = sqrt(pow(point[j].first - point[i].first, 2) +
                                  pow(point[j].second - point[i].second, 2));
                g[i][j] = val;
                g[j][i] = val;
            }
        }
    }
 
    for (int i = 0; i < ver; i++) {
        int v = -1;
        for (int j = 0; j < ver; j++)
            if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
                v = j;
 
        used[v] = true;
        for (int to = 0; to < ver; to++)
            if (g[v][to] < min_e[to]) {
                min_e[to] = g[v][to];
            }
 
        count += min_e[v];
    }
 
    output_file.precision(20);
    output_file << count;
 
    output_file.close();
    input_file.close();
 
    return 0;
}

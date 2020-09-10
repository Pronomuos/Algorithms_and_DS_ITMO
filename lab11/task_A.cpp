#include <iostream>
#include <vector>
#include <fstream>
 
using namespace std;
 
int main() {
 
    ifstream input_file ("pathmgep.in");
    ofstream output_file("pathmgep.out");
 
    int ver, st, fin;
    input_file >> ver >> st >> fin;
    st--;
    fin--;
    int g [ver][ver];
 
    for (int i = 0; i < ver; i++)
        for (int j = 0; j < ver; j++) {
            int n;
            input_file >> n;
            g[i][j] = (n != -1 && n != 0) ? n : INT_MAX;
        }
 
    vector<bool> visited (ver, false);
    vector<long long> d (ver);
    for (int i = 0; i < ver; i++)
        d[i] = (g[st][i] == INT_MAX) ? LLONG_MAX : g[st][i];
 
    d[st] = 0;
    int index = 0;
    for (int i = 0; i < ver ; i++) {
        long long min = LLONG_MAX;
        for (int j = 0; j < ver; j++)
            if (!visited[j] && d[j] < min) {
                min = d[j];
                index = j;
            }
 
        visited[index] = true;
 
        for (int j = 0; j < ver; j++)
            if (!visited[j] && g[index][j] != INT_MAX && d[index] != LLONG_MAX && (d[index] + g[index][j] < d[j]))
                d[j] = d[index] + g[index][j];
    }
 
    output_file << ((d[fin] != LLONG_MAX) ? d[fin] : -1);
 
    output_file.close();
    input_file.close();
 
    return 0;
}

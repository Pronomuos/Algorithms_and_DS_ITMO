#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
int dsu_get (int v, vector<int> &p) {
    return (v == p[v]) ? v : (p[v] = dsu_get (p[v], p));
}
 
void dsu_unite (int a, int b, vector<int> &p, vector<int> &size) {
    a = dsu_get (a , p);
    b = dsu_get (b, p);
    if (a != b) {
        if (size[a] < size[b])
            swap(a, b);
 
        p[a] = b;
        size[a] += size[b];
    }
}
 
int partition (vector<pair<int, pair<int, int>>> &g, int low, int high) {
    int pivot = g[high].first;
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++)
    {
 
        if (g[j].first < pivot)
        {
            i++;
            swap(g[i], g[j]);
        }
    }
    swap(g[i + 1], g[high]);
    return (i + 1);
}
 
void quick_sort(vector<pair<int, pair<int, int>>> &g, int low, int high) {
    if (low < high)
    {
        int pi = partition(g, low, high);
 
        quick_sort(g, low, pi - 1);
        quick_sort(g, pi + 1, high);
    }
}
 
int main() {
 
    ifstream input_file("spantree3.in");
    ofstream output_file("spantree3.out");
 
    int ver, edges;
    input_file >> ver >> edges;
    vector<pair<int, pair<int, int>>> g;
    long long count = 0;
 
    for (int i = 0; i < edges; i++) {
        int ver1, ver2, cost;
        input_file >> ver1 >> ver2 >> cost;
        ver1--;
        ver2--;
        g.emplace_back(cost, make_pair(ver1, ver2));
    }
 
    quick_sort(g, 0, edges - 1);
    vector<int> p (ver);
    vector<int> size (ver);
    for (int i = 0; i < ver; ++i) {
        p[i] = i;
        size[i] = 1;
    }
 
    for (int i=0; i<edges; ++i)
    {
        int a = g[i].second.first,  b = g[i].second.second,  cost = g[i].first;
        if (dsu_get(a, p) != dsu_get(b,p)) {
            count += cost;
            dsu_unite(a, b, p, size);
        }
    }
 
    output_file << count;
 
    output_file.close();
    input_file.close();
 
    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
int main() {
 
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
 
    int ver, edges;
    input_file >> ver >> edges;
    vector<int> g (ver);
 
    for (int i = 0; i < edges; i++) {
        int ver1, ver2;
        input_file >> ver1 >> ver2;
        ver1--;
        ver2--;
        g[ver1] += 1;
        g[ver2] += 1;
    }
 
    for (int i = 0; i < ver; i++)
        output_file << g[i] << " ";
        
     input_file.close();
     output_file.close();
 
    return 0;
}

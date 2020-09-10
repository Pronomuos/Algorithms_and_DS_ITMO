#include <iostream>
#include <fstream>
 
int main() {
 
    std::ifstream input_file ("input.txt");
    std::ofstream output_file ("output.txt");
 
    int ver, edges;
    input_file >> ver >> edges;
    int v1 [edges], v2 [edges];
    bool multiple_edges = false;
 
    for (int col = 0; col < edges; col++) {
            input_file >> v1 [col] >> v2 [col];
    }
 
    for (int i = 0; i < edges-1; i++) {
        for (int j = i + 1; j < edges; j++) {
            if ((v1[i] == v1[j] && v2[i] == v2[j])
                || (v2[j] == v1[i] && v1[j] == v2[i])) {
                multiple_edges = true;
            }
        }
    }
 
    if (multiple_edges) {
        output_file  << "YES";
    } else {
        output_file  << "NO";
    }
 
    input_file.close();
    output_file.close();
 
    return 0;
}

#include <iostream>
#include <fstream>
 
int main() {
 
    std::ifstream input_file ("input.txt");
    std::ofstream output_file ("output.txt");
 
    int ver, edges;
    input_file >> ver >> edges;
    int matrix[ver][ver];
 
    for (int col = 0; col < ver; col++){
        for (int row = 0; row < ver; row++) {
            matrix[col][row] = 0;
        }
    }
 
    for (int m = 0; m < edges; m++){
        int i, ii;
        input_file >> i >> ii;
        matrix [i-1][ii-1] = 1;
    }
 
    input_file.close();
 
    for (int col = 0; col < ver; col++){
        for (int row = 0; row < ver; row++) {
           output_file << matrix[col][row] << " ";
        }
        output_file  << '\n';
    }
 
    output_file.close();
 
    return 0;
}

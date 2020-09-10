#include <iostream>
#include <fstream>
 
int main() {
 
    std::ifstream input_file ("input.txt");
    std::ofstream output_file ("output.txt");
 
    int n;
    input_file >> n;
    int matrix[n][n];
    bool g_is_undirected = true;
 
    for (int col = 0; col < n; col++) {
        for (int row = 0; row < n; row++) {
            input_file >> matrix[col][row];
        }
    }
 
        for (int col = 0; col < n; col++) {
            for (int row = 0; row < n; row++) {
                if (matrix[col][row] != matrix[row][col] || matrix[col][col] != 0) {
                    g_is_undirected = false;
                }
            }
        }
 
    if (g_is_undirected) {
        output_file << "YES";
    } else {
        output_file << "NO";
    }
    
    input_file.close();
    output_file.close();
    return 0;
}

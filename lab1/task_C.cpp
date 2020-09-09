#include <iostream>
#include <fstream>
 
using namespace std;
 
int main() {
    ifstream input_file ("turtle.in");
    ofstream output_file ("turtle.out");
 
    int h, w;
    input_file >> h >> w;
    int matrix [h][w];
 
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            input_file >> matrix[i][j];
 
    for (int i = h - 2; i >=0; i--)
        matrix[i][0] += matrix[i + 1][0];
 
    for (int i = 1; i < w; i++)
        matrix[h - 1][i] += matrix[h - 1][i - 1];
 
 
    for (int i = h - 2; i >= 0; i--)
        for (int j = 1; j < w; j++)
            matrix[i][j] += max(matrix[i + 1][j], matrix[i][j - 1]);
 
    output_file << matrix[0][w - 1];
 
    input_file.close();
    output_file.close();
}

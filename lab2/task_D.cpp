#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
int main() {
    ifstream input_file ("antiqs.in");
    ofstream output_file ("antiqs.out");
 
    int n;
    input_file >> n;
    vector<int> numbers (n);
    for (int i = 0; i < n; i++)
        numbers[i] = i + 1;
    for (int i = 0; i < n; i++)
        swap(numbers[i], numbers[i >> 1]);
 
 
    for (int el : numbers)
        output_file << el << " ";
 
    input_file.close();
    output_file.close();
}

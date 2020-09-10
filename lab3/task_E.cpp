#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
void count_sort(vector<string> &strs, int pos) {
    int n = strs.size();
    vector<string> output (n);
    int count[256] = {0};
 
    for (int i = 0; i < n; i ++)
        count[strs[i][pos]]++;
 
    for (int i = 1; i < 256; i++)
        count[i] += count[i - 1];
 
    for (int i = n - 1; i >= 0; i--) {
        output[count[strs[i][pos]] - 1] = strs[i];
        count[strs[i][pos]]--;
    }
 
    for (int i = 0; i < n; i++)
        strs[i] = output[i];
}
 
void radix_sort(vector<string> &strs, int k, int m) {
 
    for (int i = m - 1; i > m - 1 - k; i--)
        count_sort(strs, i);
 
}
 
 
int main() {
    ifstream input_file ("radixsort.in");
    ofstream output_file ("radixsort.out");
 
    int n, m, k;
    input_file >> n >> m >> k;
    vector<string> strs (n);
    for (int i = 0; i < n; i++) {
        string str;
        input_file >> str;
        strs[i] = str;
    }
 
    radix_sort(strs, k, m);
    for (int i = 0; i < n; i++)
        output_file << strs[i] << "\n";
 
 
    input_file.close();
    output_file.close();
}

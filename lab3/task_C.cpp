#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
bool isHeap (vector<long long> &a) {
    bool isHeap = true;
    int n = a.size();
    for (int i = 1; i <= n; i++) {
        if (2 * i <= n) {
            if (a[i - 1] > a[2 * i - 1])
                return false;
        } else if (2 * i + 1 <= n)
            if (a[i - 1] > a[2 * i])
                return false;
    }
 
    return true;
}
 
int main() {
    ifstream input_file ("isheap.in");
    ofstream output_file ("isheap.out");
 
    int n;
    input_file >> n;
    vector<long long> a (n);
    for (int i = 0; i < n; i++) {
        long long num;
        input_file >> num;
        a[i] = num;
    }
 
    output_file << (isHeap(a)? "YES" : "NO");
 
    input_file.close();
    output_file.close();
}

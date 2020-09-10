#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
void make_heap(vector<long long> &arr, int n, int i)
{
    int root = i, l = 2 * i + 1, r = 2 * i + 2;
 
    if (l < n && arr[l] > arr[root])
        root = l;
    if (r < n && arr[r] > arr[root])
        root = r;
 
    if (arr[root] != arr[i]) {
        swap(arr[i], arr[root]);
        make_heap(arr, n, root);
    }
}
 
void heap_sort(vector<long long> &arr) {
 
    int n = arr.size();
 
    for (int i = n / 2 - 1; i >= 0; i--)
        make_heap(arr, n, i);
 
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        make_heap(arr, i, 0);
    }
}
 
int main() {
    ifstream input_file ("sort.in");
    ofstream output_file ("sort.out");
 
    int n;
    input_file >> n;
    vector<long long> a (n);
    for (int i = 0; i < n; i++) {
        long long num;
        input_file >> num;
        a[i] = num;
    }
 
    heap_sort(a);
    for (auto el : a)
        output_file << el << " ";
 
    input_file.close();
    output_file.close();
}

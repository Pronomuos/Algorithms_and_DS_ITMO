#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
int find_kth(vector<int> &numbers, int k) {
 
    int low = 0, high = numbers.size() - 1;
 
    while (low < high)
    {
        int x = numbers[k], i = low, j = high;
        do
        {
            while (numbers[i] < x)
                i++;
            while (numbers[j] > x)
                j--;
            if (i <= j)
                swap (numbers[i++], numbers[j--]);
 
        } while (i <= j);
 
        if (j < k)
            low = i;
        if (i > k)
            high = j;
 
    }
 
    return numbers[k];
}
 
int main() {
    ifstream input_file ("kth.in");
    ofstream output_file ("kth.out");
 
    int n, k;
    input_file >> n >> k;
    k--;
    int A, B, C;
    vector<int> a(n, 0);
    input_file >> A >> B >> C >> a[0] >> a[1];
    for (int i = 2; i < n; i++) {
        a[i] = A * a[i - 2] + B * a[i - 1] + C;
    }
 
    output_file << find_kth(a, k);
 
    input_file.close();
    output_file.close();
}

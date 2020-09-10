#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
void merge(vector<long long> &arr, int l, int m, int r, long long &count)
{
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    vector<long long> L (n1), R (n2);
 
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
        {
            arr[k++] = R[j++];
            count += n1 - i;
        }
 
    }
 
    while (i < n1)
        arr[k++] = L[i++];
 
    while (j < n2)
        arr[k++] = R[j++];
 
}
 
void mergeSort(vector<long long> &arr, int l, int r, long long &count)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m, count);
        mergeSort(arr, m + 1, r, count);
        merge(arr, l, m, r, count);
    }
}
 
int main() {
    ifstream input_file ("inversions.in");
    ofstream output_file ("inversions.out");
 
    vector<long long> numbers;
    int num;
    input_file >> num;
    for (int i = 0; i < num; i++) {
        long long number;
        input_file >> number;
        numbers.push_back(number);
    }
 
    long long count = 0;
    mergeSort(numbers, 0,  num - 1, count);
 
    output_file << count;
 
    input_file.close();
    output_file.close();
}

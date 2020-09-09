#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
int partition (vector<long long> &numbers, int low, int high) {
    int pivot = numbers[high];
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) {
 
        if (numbers[j] < pivot) {
            i++;
            swap(numbers[i], numbers[j]);
        }
    }
    swap(numbers[i + 1], numbers[high]);
    return (i + 1);
}
 
void quick_sort(vector<long long> &numbers, int low, int high) {
    if (low < high) {
        int pivot = partition(numbers, low, high);
 
        quick_sort(numbers, low, pivot - 1);
        quick_sort(numbers, pivot + 1, high);
    }
}
 
int main() {
    ifstream input_file ("smallsort.in");
    ofstream output_file ("smallsort.out");
 
    vector<long long> numbers;
    int count;
    input_file >> count;
    for (int i = 0; i < count; i++) {
        long long num;
        input_file >> num;
        numbers.push_back(num);
    }
 
    quick_sort(numbers, 0, count - 1);
 
    for (int i = 0; i < count; i++)
        output_file << numbers[i] << " ";
 
    input_file.close();
    output_file.close();
}

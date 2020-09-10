#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
int partition (vector<long long> &numbers, int low, int high) {
 
    int random = low + rand() % (high - low);
    swap(numbers[random], numbers[high]);
    long long pivot = numbers[high];
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
 
void qsort(vector<long long> &numbers, int low, int high) {
    if (low < high) {
        int pivot = partition(numbers, low, high);
 
        qsort(numbers, low, pivot - 1);
        qsort(numbers, pivot + 1, high);
    }
}
 
int main() {
    ifstream input_file ("sort.in");
    ofstream output_file ("sort.out");
 
    vector<long long> numbers;
    int count;
    input_file >> count;
    for (int i = 0; i < count; i++) {
        long long num;
        input_file >> num;
        numbers.push_back(num);
    }
 
    qsort(numbers, 0, count - 1);
 
    for (int i = 0; i < count; i++)
        output_file << numbers[i] << " ";
 
 
 
    input_file.close();
    output_file.close();
}

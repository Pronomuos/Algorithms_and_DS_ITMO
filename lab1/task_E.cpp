#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
int partition (vector<pair<float, int>> &numbers, int low, int high) {
    float pivot = numbers[high].first;
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) {
 
        if (numbers[j].first < pivot) {
            i++;
            swap(numbers[i], numbers[j]);
        }
    }
    swap(numbers[i + 1], numbers[high]);
    return (i + 1);
}
 
void quick_sort(vector<pair<float, int>> &numbers, int low, int high) {
    if (low < high) {
        int pivot = partition(numbers, low, high);
 
        quick_sort(numbers, low, pivot - 1);
        quick_sort(numbers, pivot + 1, high);
    }
}
 
int main() {
    ifstream input_file ("sortland.in");
    ofstream output_file ("sortland.out");
 
    vector<pair<float, int>> numbers;
    int count;
    input_file >> count;
    for (int i = 0; i < count; i++) {
        float num;
        input_file >> num;
        numbers.emplace_back(num, i + 1);
    }
 
    quick_sort(numbers, 0, count - 1);
 
 
    output_file << numbers[0].second << " " << numbers[count/2].second << " " << numbers [count - 1].second;
 
    input_file.close();
    output_file.close();
}

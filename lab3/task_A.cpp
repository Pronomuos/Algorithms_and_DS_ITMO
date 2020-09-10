#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
int left(vector<int> &arr, int low, int high, int key)
{
    int result = -1;
 
    while (low <= high) {
        int mid = low + (high - low + 1) / 2;
        int midVal = arr[mid];
 
        if (midVal < key)
            low = mid + 1;
 
        else if (midVal > key)
            high = mid - 1;
 
        else if (midVal == key) {
            result = mid;
            high = mid - 1;
        }
    }
 
    return result;
}
 
int right(vector<int> &arr, int low, int high, int key)
{
    int result = -1;
 
    while (low <= high) {
        int mid = low + (high - low + 1) / 2;
        int midVal = arr[mid];
 
        if (midVal < key)
            low = mid + 1;
 
        else if (midVal > key)
            high = mid - 1;
 
        else if (midVal == key) {
            result = mid;
            low = mid + 1;
        }
    }
 
    return result;
}
 
int main() {
    ifstream input_file ("binsearch.in");
    ofstream output_file ("binsearch.out");
 
    int n;
    input_file >> n;
    vector<int> numbers;
    for (int i = 0; i < n; i++) {
        int num;
        input_file >> num;
        numbers.push_back(num);
    }
    int m;
    input_file >> m;
    vector<int> requests;
    for (int i = 0; i < m; i++) {
        int req;
        input_file >> req;
        requests.push_back(req);
    }
 
    for (int i = 0; i < m; i++) {
        int st = left(numbers, 0, numbers.size() - 1, requests[i]) + 1;
        int end = right(numbers, 0,   numbers.size() - 1, requests[i]) + 1;
        output_file << (st ? st : -1) << " " << (end ? end : -1) << "\n";
    }
 
    input_file.close();
    output_file.close();
}

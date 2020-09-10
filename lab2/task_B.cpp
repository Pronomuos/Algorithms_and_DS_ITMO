#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>
 
using namespace std;
 
void merge(vector<tuple<string, int, string>> &arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    vector<tuple<string, int, string>> L (n1), R (n2);
 
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
 
    while (i < n1)
        arr[k++] = L[i++];
 
    while (j < n2)
        arr[k++] = R[j++];
}
 
void mergeSort(vector<tuple<string, int, string>> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}
 
int main() {
    ifstream input_file ("race.in");
    ofstream output_file ("race.out");
 
 
    vector<tuple<string, int, string>> race;
    int participants;
    input_file >> participants;
    for (int i = 0; i < participants; i++) {
        string country, name;
        input_file >> country >> name;
        race.emplace_back(country, i, name);
    }
 
    mergeSort(race, 0, race.size() - 1);
    string country = get<0>(race[0]);
    output_file << "=== " << country << " ===\n";
 
    for (int i = 0; i < participants; i++) {
        if (country != get<0>(race[i])) {
            country = get<0>(race[i]);
            output_file << "=== " << country << " ===\n";
        }
 
        output_file << get<2>(race[i]) << "\n";
    }
 
 
    input_file.close();
    output_file.close();
}

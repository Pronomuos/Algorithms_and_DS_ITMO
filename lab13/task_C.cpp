#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
vector<int> prefix_function (string s) {
 
    vector<int> p (s.size());
    for (int i = 1; i < s.size(); ++i) {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j])
            j = p [j-1];
        if (s[i] == s[j])  ++j;
        p[i] = j;
    }
    return p;
}
 
int main() {
    ifstream input_file ("prefix.in");
    ofstream output_file ("prefix.out");
 
    string s;
    input_file >> s;
    vector<int> result = prefix_function(s);
    for (int i : result)
        output_file << i << " ";
 
    input_file.close();
    output_file.close();
}

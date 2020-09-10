#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
vector<int> prefix_function (string s) {
 
    vector<int> p (s.length());
    for (int i = 1; i < s.length(); ++i) {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j])
            j = p [j - 1];
        if (s[i] == s[j])
            ++j;
        p[i] = j;
    }
    return p;
}
 
vector<int> kmp (const string& pattern, const string& text) {
    int pl = pattern.length();
    vector<int> answer;
    vector<int> p = prefix_function(pattern + '#' + text);
    for (int i = 0; i < text.length(); i++)
        if (p[pl + i + 1] == pl)
            answer.push_back(i + 2 - pl);
 
     return answer;
}
 
int main() {
    ifstream input_file ("search1.in");
    ofstream output_file ("search1.out");
 
    string p, t;
    input_file >> p >> t;
    vector<int> result = kmp(p, t);
    output_file << result.size() << "\n";
    for (int i : result)
        output_file << i << " ";
 
    input_file.close();
    output_file.close();
}

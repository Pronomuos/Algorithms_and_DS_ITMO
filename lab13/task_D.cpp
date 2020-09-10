#include <iostream>
#include <vector>
 
using namespace std;
 
vector<int> prefix_function (string s) {
 
    vector<int> p (s.size());
    for (int i = 1; i < s.size(); ++i) {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j])
            j = p [j - 1];
        if (s[i] == s[j])
            ++j;
        p[i] = j;
    }
    return p;
}
 
vector<vector<int>> kmp_machine (string &pattern, int power_alph) {
    pattern += "#";
    int pl = pattern.length();
    vector<int> p = prefix_function (pattern);
    vector < vector<int> > answer (pl, vector<int> (power_alph));
    for (int i = 0; i < pl; i++)
        for (int letter = 0; letter < power_alph; letter++) {
            if (i > 0 && static_cast<char>(letter + 353) != pattern[i])
                answer[i][letter] = answer[p[i - 1]][letter];
            else
                answer[i][letter] = i + (static_cast<char>(letter + 353) == pattern[i]);
        }
 
    return answer;
}
 
int main() {
 
    int power_alph;
    string pattern;
    cin >> power_alph >> pattern;
 
    vector<vector<int>> answer = kmp_machine(pattern, power_alph);
    for (const auto& line : answer) {
        for (int el : line)
            cout << el << " ";
 
        cout << "\n";
    }
 
    return 0;
}

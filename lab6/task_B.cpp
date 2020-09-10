#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
const int inf = 2e9;
 
struct Node {
    int value, left_child, right_child;
};
 
class Bi_tree {
public:
    void read (ifstream &input) {
        int num, value, left_child, right_child;
        input >> num;
        for (int i = 0; i < num; ++i) {
            Node node {};
            input >> value >> left_child  >> right_child;
            tree_vec.push_back({value, --left_child, --right_child});
        }
    }
 
    void solve (ofstream &output) {
        if (tree_vec.empty() || check_binary(0, -inf, inf))
            output << "YES\n";
        else
            output << "NO\n";
   }
 
private:
    vector<Node> tree_vec;
 
    bool check_binary (int cur_id, int lower, int upper) {
 
            int left_id = tree_vec[cur_id].left_child,
                right_id = tree_vec[cur_id].right_child;
 
            if (tree_vec[cur_id].value <= lower || tree_vec[cur_id].value >= upper)
                return false;
 
            if (left_id != -1) {
                if (tree_vec[left_id].value >= tree_vec[cur_id].value)
                    return false;
                if (!check_binary(left_id, lower, tree_vec[cur_id].value))
                    return false;
            }
            if (right_id != -1) {
                if (tree_vec[right_id].value <= tree_vec[cur_id].value)
                    return false;
                if (!check_binary(right_id, tree_vec[cur_id].value, upper))
                    return false;
            }
 
        return true;
    }
};
 
int main() {
    ifstream input_file ("check.in");
    ofstream output_file ("check.out");
 
    Bi_tree tree;
    tree.read(input_file);
    tree.solve(output_file);
 
    return 0;
}

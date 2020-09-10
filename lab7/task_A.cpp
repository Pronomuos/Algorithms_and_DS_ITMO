#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
struct Node {
    int left_child, right_child, height;
};
 
class Bi_tree {
public:
 
    void read (ifstream &input) {
        int num;
        input >> num;
        for (int i = 0; i < num; ++i) {
            int value, left_child, right_child;
            input >> value >> left_child >> right_child;
            tree_vec.push_back({--left_child, --right_child});
        }
 
        input.close();
    }
 
    void solve (ofstream &output) {
        if (!tree_vec.empty()) {
            find_height(0);
            for (auto &node : tree_vec) {
                int left_h = node.left_child == -1 ? 0 : tree_vec[node.left_child].height;
                int right_h = node.right_child == -1 ? 0 : tree_vec[node.right_child].height;
                output << right_h - left_h << "\n";
            }
        }
        else
            output << 0;
 
        output.close();
    }
 
private:
    vector<Node> tree_vec;
 
    int find_height (int id) {
        if (id == -1)
            return 0;
 
        int left = find_height(tree_vec[id].left_child) + 1;
        int right = find_height(tree_vec[id].right_child) + 1;
 
        tree_vec[id].height = left > right ? left : right;
 
        return tree_vec[id].height;
    }
 
};
 
int main() {
    ifstream input_file ("balance.in");
    ofstream output_file ("balance.out");
 
    Bi_tree tree;
    tree.read(input_file);
    tree.solve(output_file);
 
    return 0;
}

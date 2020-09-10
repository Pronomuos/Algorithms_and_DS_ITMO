#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
struct Node {
    int value, right_child, left_child;
};
 
class Bi_tree {
public:
 
    void read (ifstream &input) {
        int num;
        input >> num;
        for (int i = 0; i < num; ++i) {
            Node node {};
            input >> node.value >> node.left_child >> node.right_child;
            tree_vec.emplace_back(node);
        }
    }
 
    void solve (ofstream &output) {
        if (!tree_vec.empty())
            output << find_height(1) + 1;
        else
            output << 0;
   }
 
private:
    vector<Node> tree_vec;
 
    int find_height (int id) {
 
        int left, right, max;
 
        if (tree_vec[id - 1].left_child != 0)
            left = find_height(tree_vec[id - 1].left_child);
        else
            left = -1;
 
        if (tree_vec[id - 1].right_child != 0)
            right = find_height(tree_vec[id - 1].right_child);
        else
            right = -1;
 
        max = left > right ? left : right;
        return ++max;
    }
 
};
 
int main() {
    ifstream input_file ("height.in");
    ofstream output_file ("height.out");
 
    Bi_tree tree;
    tree.read(input_file);
    tree.solve(output_file);
 
    return 0;
}

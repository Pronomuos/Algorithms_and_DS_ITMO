#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
struct Node {
    int value = 0, index = 0, height = 0;
    shared_ptr<Node> left_child = nullptr, right_child = nullptr;
    Node () {}
    Node (int _value) : value(_value) {}
};
 
class Bi_tree {
public:
    void read (ifstream &input) {
        input >> size;
        vector<shared_ptr<Node>> tree_vec (size);
        for (int i = 0; i < size; ++i)
            tree_vec[i] = make_shared<Node>();
        root = tree_vec[0];
        for (int i = 0; i < size; ++i) {
            int value, left_child, right_child;
            input >> value >> left_child >> right_child;
            tree_vec[i]->value = value;
            tree_vec[i]->left_child = left_child == 0 ? nullptr : tree_vec[left_child - 1];
            tree_vec[i]->right_child = right_child == 0 ? nullptr : tree_vec[right_child - 1];
        }
        input.close();
    }
 
    void balance () {
        find_height(root);
        int left_h = root->right_child->left_child == nullptr ? 0 : root->right_child->left_child->height;
        int right_h = root->right_child->right_child == nullptr ? 0 : root->right_child->right_child->height;
        if (left_h - right_h == 1)
            root = big_rotate_left(root);
        else
            root = rotate_left(root);
 
    }
 
    void print (ofstream &output) {
        int i = 0;
        make_indices(root, i);
        output << size << "\n";
        print (output, root);
 
        output.close();
    }
 
    void insert (int value) {
        root = insert(root, value);
        balance();
    }
 
private:
    shared_ptr<Node> root = nullptr;
    int size = 0;
 
    int find_height (const shared_ptr<Node>& node) {
        if (node == nullptr)
            return 0;
 
        int left = find_height(node->left_child) + 1;
        int right = find_height(node->right_child) + 1;
 
        node->height = left > right ? left : right;
 
        return node->height;
    }
 
    shared_ptr<Node> rotate_left (const shared_ptr<Node>& node) {
        shared_ptr<Node> temp (node->right_child);
        node->right_child = temp->left_child;
        temp->left_child = node;
        return temp;
    }
 
    shared_ptr<Node> rotate_right (const shared_ptr<Node>& node) {
        shared_ptr<Node> temp (node->left_child);
        node->left_child = temp->right_child;
        temp->right_child = node;
        return temp;
    }
 
    shared_ptr<Node> big_rotate_left (const shared_ptr<Node>& node) {
        shared_ptr<Node> temp (node->right_child->left_child);
        node->right_child = rotate_right(node->right_child);
        rotate_left(node);
        return temp;
    }
 
    void print (ofstream &output, const shared_ptr<Node> &node) {
        if (node == nullptr)
            return;
 
        output << node->value << " "
        << (node->left_child == nullptr ? 0 : node->left_child->index) << " "
        << (node->right_child == nullptr ? 0 : node->right_child->index) << "\n";
        print (output, node->left_child);
        print (output, node->right_child);
    }
 
    void make_indices (const shared_ptr<Node>& node, int &i) {
        if (node == nullptr)
            return;
 
        node->index = ++i;
        make_indices(node->left_child, i);
        make_indices(node->right_child, i);
    }
 
    shared_ptr<Node> insert (const shared_ptr<Node>& node, int value) {
        if (node == nullptr)
            return make_shared<Node>(value);
 
        if (node->value < value)
            node->right_child = insert(node->right_child, value);
        else
            node->left_child = insert(node->left_child, value);
 
        return node;
    }
};
 
int main() {
    ifstream input_file ("rotation.in");
    ofstream output_file ("rotation.out");
 
    Bi_tree tree;
    tree.read(input_file);
    tree.balance();
    tree.print(output_file);
 
    return 0;
}

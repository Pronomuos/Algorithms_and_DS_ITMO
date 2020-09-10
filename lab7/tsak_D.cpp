#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
struct Node {
    int value = 0, index = 0;
    shared_ptr<Node> left_child = nullptr, right_child = nullptr;
    Node () = default;
    explicit Node (int _value) : value(_value) {}
};
 
class Bi_tree {
public:
    void read (ifstream &input) {
        input >> size;
        if (size) {
            vector<shared_ptr<Node>> tree_vec(size);
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
        }
 
        int value;
        input >> value;
        deletion(value);
 
        input.close();
    }
 
    void print (ofstream &output) {
        int i = 0;
        update_indices(root, i);
        output << size << "\n";
        print (output, root);
 
        output.close();
    }
 
    void insert (int value) {
        ++size;
        root = insert(root, value);
    }
 
    void deletion (int value) {
        --size;
        root = deletion(root, value);
    }
 
private:
    shared_ptr<Node> root = nullptr;
    int size = 0;
 
    int find_height (const shared_ptr<Node>& node) {
        if (node == nullptr)
            return 0;
 
        int left = find_height(node->left_child) + 1;
        int right = find_height(node->right_child) + 1;
 
        return left > right ? left : right;
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
 
    shared_ptr<Node> big_rotate_right (const shared_ptr<Node>& node) {
        shared_ptr<Node> temp (node->left_child->right_child);
        node->left_child = rotate_left(node->left_child);
        rotate_right(node);
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
 
    void update_indices (const shared_ptr<Node>& node, int &i) {
        if (node == nullptr)
            return;
 
        node->index = ++i;
        update_indices(node->left_child, i);
        update_indices(node->right_child, i);
    }
 
    shared_ptr<Node> insert (shared_ptr<Node>& node, int value) {
        if (node == nullptr)
            return make_shared<Node>(value);
 
        if (node->value < value)
            node->right_child = insert(node->right_child, value);
        else
            node->left_child = insert(node->left_child, value);
 
        return balance(node);
    }
 
    shared_ptr<Node> balance (shared_ptr<Node>& node) {
 
        int height = find_balance(node);
        if (height == -2)
            return find_balance(node->right_child) == 1 ? big_rotate_left(node) : rotate_left(node);
        else if (height == 2)
            return find_balance(node->left_child) == -1 ? big_rotate_right(node) : rotate_right(node);
        else
            return node;
    }
 
    int find_balance (const shared_ptr<Node> &node) {
        return find_height(node->left_child) - find_height(node->right_child);
    }
 
   shared_ptr<Node> deletion (shared_ptr<Node> &node, int value) {
        if (node == nullptr)
            return node;
        if (node->value > value)
            node->left_child = deletion(node->left_child, value);
        else if (node->value < value)
            node->right_child = deletion(node->right_child, value);
        else {
            if (node->right_child == nullptr && node->left_child == nullptr)
                return nullptr;
            else if (node->left_child == nullptr)
                return node->right_child;
            else
                node->left_child = delete_max(node, node->left_child);
        }
        return balance(node);
    }
 
    shared_ptr<Node> delete_max (shared_ptr<Node> &start, shared_ptr<Node> &node) {
        if (node->right_child == nullptr) {
            start->value = node->value;
            return node->left_child;
        }
        node->right_child = delete_max(start, node->right_child);
        return balance(node);
    }
};
 
int main() {
    ifstream input_file ("deletion.in");
    ofstream output_file ("deletion.out");
 
    Bi_tree tree;
    tree.read(input_file);
    tree.print(output_file);
 
    return 0;
}

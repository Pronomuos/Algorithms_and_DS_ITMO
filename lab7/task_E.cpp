#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
struct Node {
    int value = 0, height = 1;
    shared_ptr<Node> left_child = nullptr, right_child = nullptr;
    Node () = default;
    explicit Node (int _value) : value(_value) {}
};
 
class Bi_tree {
public:
    void read_and_solve (ifstream &input, ofstream &output) {
        int count, value;
        char cmd;
        input >> count;
        for (int i = 0; i < count; ++i) {
            input >> cmd >> value;
            switch (cmd) {
                case 'A':
                    insert(value);
                    output << find_balance(root) << '\n';
                    break;
                case 'D':
                    deletion(value);
                    output << find_balance(root) << '\n';
                    break;
                case 'C':
                    exists(output, value);
                    break;
            }
        }
 
        input.close();
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
 
    void exists (ofstream &output, int value) {
        output << (exists(root, value) ? "Y\n" : "N\n");
    }
 
private:
    shared_ptr<Node> root = nullptr;
    int size = 0;
 
    int update_height (const shared_ptr<Node>& node) {
        node->height = max(node->right_child == nullptr ? 0 : node->right_child->height,
                node->left_child == nullptr ? 0 : node->left_child->height) + 1;
 
        return node->height;
    }
 
    shared_ptr<Node> rotate_left (const shared_ptr<Node>& node) {
        shared_ptr<Node> temp (node->right_child);
        node->right_child = temp->left_child;
        temp->left_child = node;
        update_height(node);
        update_height(temp);
        return temp;
    }
 
    shared_ptr<Node> rotate_right (const shared_ptr<Node>& node) {
        shared_ptr<Node> temp (node->left_child);
        node->left_child = temp->right_child;
        temp->right_child = node;
        update_height(node);
        update_height(temp);
        return temp;
    }
 
 
    shared_ptr<Node> insert (shared_ptr<Node>& node, int value) {
        if (node == nullptr)
            return make_shared<Node>(value);
 
        if (node->value < value)
            node->right_child = insert(node->right_child, value);
        else if (node->value > value)
            node->left_child = insert(node->left_child, value);
 
        return balance(node);
    }
 
    shared_ptr<Node> balance (shared_ptr<Node>& node) {
 
        update_height(node);
        int height = find_balance(node);
        if (height == 2) {
            if (find_balance(node->right_child) == -1)
                node->right_child = rotate_right(node->right_child);
            return rotate_left(node);
        }
        else if (height == -2) {
            if (find_balance(node->left_child) == 1)
                node->left_child = rotate_left(node->left_child);
            return rotate_right(node);
        }
 
        return node;
    }
 
    int find_balance (const shared_ptr<Node> &node) {
        if (node == nullptr)
            return 0;
        return (node->right_child == nullptr ? 0 : node->right_child->height) -
               (node->left_child == nullptr ? 0 : node->left_child->height);
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
 
    bool exists (const shared_ptr<Node> &node, int value) {
        if (node == nullptr)
            return false;
 
        if (node->value > value)
            return exists(node->left_child, value);
        else if (node->value < value)
            return exists(node->right_child, value);
 
        return true;
 
    }
};
 
int main() {
    ifstream input_file ("avlset.in");
    ofstream output_file ("avlset.out");
 
    Bi_tree tree;
    tree.read_and_solve(input_file, output_file);
 
 
    return 0;
}

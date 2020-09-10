#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
 
using namespace std;
 
struct Node {
    int key;
    shared_ptr<Node> left_child = nullptr, right_child = nullptr;
    Node (int _key, shared_ptr<Node> _left_child, shared_ptr<Node> _right_child) :
            key(_key), left_child(std::move(std::move(_left_child))), right_child (std::move(_right_child)) {}
};
 
class Bi_tree {
public:
    void read_and_solve (ifstream &input, ofstream &output) {
        std::string cmd;
        int key;
        while (input >> cmd) {
            input >> key;
            if (cmd == "insert")
                main_root = insert(main_root, key);
            else if (cmd == "delete")
                main_root = delete_key (main_root, key);
            else if (cmd == "exists")
                output << (exists (main_root, key) ? "true\n" : "false\n");
            else if (cmd == "next" || cmd == "prev") {
                int result;
                if (cmd == "next")
                    result = next(key);
                else
                    result = prev(key);
 
                if (result == INT_MAX)
                    output << "none\n";
                else
                    output << result << '\n';
            }
        }
    }
 
 
private:
    shared_ptr<Node> main_root = nullptr;
 
    shared_ptr<Node> insert (shared_ptr<Node> root, int key) {
        if (root == nullptr)
            return make_shared<Node>(key, nullptr, nullptr);
        else if (key < root->key)
            root->left_child = insert (root->left_child, key);
        else if (key > root->key)
            root->right_child = insert(root->right_child, key);
 
        return root;
    }
 
 
    shared_ptr<Node> delete_key (shared_ptr<Node> root, int key) {
        if (root == nullptr)
            return root;
        if (key < root->key)
            root->left_child = delete_key(root->left_child, key);
        else if (key > root->key)
            root->right_child = delete_key(root->right_child, key);
        else if (root->left_child != nullptr && root->right_child != nullptr) {
            root->key = next(root->key);
            root->right_child = delete_key (root->right_child, root->key);
        }
        else {
            if (root->left_child != nullptr)
                root = root->left_child;
            else if (root->right_child != nullptr)
                root = root->right_child;
            else
                root = nullptr;
        }
 
        return root;
    }
 
    bool exists (const shared_ptr<Node>& node, int key) {
        if (node == nullptr)
            return false;
        else if (key == node->key)
            return true;
 
        if (key < node->key)
            return exists (node->left_child, key);
        else
            return exists (node->right_child, key);
    }
 
    int next (int key) {
        shared_ptr<Node> current = main_root, successor = nullptr;
        while (current != nullptr) {
            if (current->key > key) {
                successor = current;
                current = current->left_child;
            }
            else
                current = current->right_child;
        }
 
        return (successor != nullptr) ? successor->key : INT_MAX;
    }
 
    int prev (int key) {
        shared_ptr<Node> current = main_root, successor = nullptr;
        while (current != nullptr) {
            if (current->key < key) {
                successor = current;
                current = current->right_child;
            }
            else
                current = current->left_child;
        }
 
        return (successor != nullptr) ? successor->key : INT_MAX;
    }
};
 
int main() {
    ifstream input_file ("bstsimple.in");
    ofstream output_file ("bstsimple.out");
 
    Bi_tree tree;
    tree.read_and_solve(input_file, output_file);
 
    return 0;
}

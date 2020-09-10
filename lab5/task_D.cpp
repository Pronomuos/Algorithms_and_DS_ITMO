#include <iostream>
#include <vector>
#include <fstream>
#include <list>
 
using namespace std;
 
template <class T>
class Bi_tree {
private:
    struct Node {
        T value;
        shared_ptr<Node> left_child = nullptr, right_child = nullptr;
        Node(T _value, shared_ptr<Node> _left_child, shared_ptr<Node> _right_child) :
                value(_value), left_child(std::move(std::move(_left_child))), right_child (std::move(_right_child)) {}
        Node () = default;
    };
 
    shared_ptr<Node> main_root = nullptr;
    int size = 0;
 
public:
    Bi_tree (T value) {
        insert(value);
    }
    void insert(T key) {
        main_root = insert (main_root, key);
    }
 
    void delete_key(T key) {
        main_root = delete_key (main_root, key);
    }
 
    void clear () {
        size = 0;
        main_root = nullptr;
    }
 
    void print (ofstream &output) {
        output << size << " ";
        print(output, main_root);
        output << '\n';
    }
 
 
private:
    shared_ptr<Node> insert (shared_ptr<Node> root, T key) {
        if (root == nullptr) {
            ++size;
            return make_shared<Node>(key, nullptr, nullptr);
        }
        else if (key < root->value)
            root->left_child = insert (root->left_child, key);
        else if (key > root->value)
            root->right_child = insert(root->right_child, key);
 
        return root;
    }
 
 
    shared_ptr<Node> delete_key (shared_ptr<Node> root, T key) {
        if (root == nullptr)
            return root;
        if (key < root->value)
            root->left_child = delete_key(root->left_child, key);
        else if (key > root->value)
            root->right_child = delete_key(root->right_child, key);
        else if (root->left_child != nullptr && root->right_child != nullptr) {
            root->value = next(root->value);
            root->right_child = delete_key (root->right_child, root->value);
        }
        else {
            if (root->left_child != nullptr)
                root = root->left_child;
            else if (root->right_child != nullptr)
                root = root->right_child;
            else
                root = nullptr;
 
            --size;
        }
 
        return root;
    }
 
    bool exists (const shared_ptr<Node>& node, T key) {
        if (node == nullptr)
            return false;
        else if (key == node->value)
            return true;
 
        if (key < node->value)
            return exists (node->left_child, key);
        else
            return exists (node->right_child, key);
    }
 
    T next(T key) {
        shared_ptr<Node> current = main_root, successor = nullptr;
        while (current != nullptr) {
            if (current->value > key) {
                successor = current;
                current = current->left_child;
            }
            else
                current = current->right_child;
        }
 
        return (successor != nullptr) ? successor->value : "%";
    }
 
    T prev(T key) {
        shared_ptr<Node> current = main_root, successor = nullptr;
        while (current != nullptr) {
            if (current->value < key) {
                successor = current;
                current = current->right_child;
            }
            else
                current = current->left_child;
        }
 
        return (successor != nullptr) ? successor->value : "%";
    }
 
    void print (ofstream &output, const shared_ptr<Node> &node) {
        if (node == nullptr)
            return;
 
        output << node->value << " ";
        print (output, node->left_child);
        print (output, node->right_child);
    }
};
 
class Multi_map {
public:
    Multi_map () {
        _hash_table.resize(_size);
    }
    Multi_map (unsigned size) : _size(size) {
        _hash_table.resize(size);
    }
 
    void read_and_solve (ifstream &input, ofstream &output) {
        string cmd, key, value;
        while (input >> cmd) {
            input >> key;
            if (cmd == "put") {
                input >> value;
                put_value(key, value);
            }
            else if (cmd == "delete") {
                input >> value;
                delete_key(key, value);
            }
            else if (cmd == "deleteall")
                delete_all(key);
            else if (cmd == "get")
                get_value(key, output);
        }
 
        input.close();
        output.close();
    }
 
    void put_value (string &key, string &value) {
        unsigned index = get_key (key);
        for (auto &el: _hash_table[index])
            if (el.first == key) {
                el.second.insert(value);
                return;
            }
 
        Bi_tree<string> tree(value);
        _hash_table[index].push_back({key, tree});
    }
 
    void delete_key (string &key, string &value) {
        unsigned i = get_key(key);
        for (auto &el : _hash_table[i])
            if (el.first == key) {
                el.second.delete_key(value);
                return;
            }
    }
 
    void delete_all (string &key)  {
        unsigned i = get_key(key);
        for (auto &el : _hash_table[i])
            if (el.first == key) {
                el.second.clear();
                return;
            }
    }
 
    void get_value (string &key, ofstream &output) {
        unsigned index = get_key(key);
        for (auto &el: _hash_table[index])
            if (el.first == key) {
                el.second.print(output);
                return;
            }
        output << 0 << "\n";
    }
 
private:
    vector<list<pair<string, Bi_tree<string>>>> _hash_table;
    unsigned _size = 1e6;
 
    unsigned get_key (string &key) {
        unsigned index = 0;
        for (char l : key)
            index = (144 * index + (l - 'a')) % _size;
 
        return index;
    }
};
 
int main() {
 
    ifstream input_file ("multimap.in");
    ofstream output_file ("multimap.out");
 
    Multi_map map;
    map.read_and_solve(input_file, output_file);
 
    return 0;
}

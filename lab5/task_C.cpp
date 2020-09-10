#include <iostream>
#include <vector>
#include <fstream>
#include <list>
 
using namespace std;
 
struct Element {
    string key, value;
    shared_ptr<Element> prev, next;
    Element (string _key, string _value, shared_ptr<Element> _prev, shared_ptr<Element> _next) :
    key(_key), value(_value), prev(_prev), next(_next) {}
};
 
class Linked_map {
public:
    Linked_map () {
        _hash_table.resize(_size);
    }
    Linked_map (unsigned size) : _size(size) {
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
            else if (cmd == "delete")
               delete_key(key);
            else if (cmd == "get")
                output <<  get_value(key) << '\n';
            else if (cmd == "prev")
                output << prev(key) << '\n';
            else if (cmd == "next")
                output << next(key) << '\n';
        }
 
        input.close();
        output.close();
    }
 
    void put_value (string &key, string &value) {
        unsigned index = get_key (key);
        for (auto &el: _hash_table[index])
            if (el->key == key) {
                el->value = value;
                return;
            }
            auto temp = make_shared<Element>(key, value, last, nullptr);
            if (last != nullptr)
                last->next = temp;
            last = temp;
            _hash_table[index].push_back(temp);
 
    }
 
    void delete_key (string &key) {
        unsigned i = get_key(key);
        for (auto &el : _hash_table[i])
            if (el->key == key) {
                if (el->prev != nullptr)
                    el->prev->next = el->next;
                if (el->next != nullptr)
                    el->next->prev = el->prev;
                else
                    last = el->prev;
                _hash_table[i].remove(el);
                return;
            }
    }
 
    string get_value (string &key) {
        unsigned index = get_key (key);
        for (auto &el: _hash_table[index])
            if (el->key == key)
                return el->value;
 
        return "none";
    }
 
    string prev (string &key) {
        unsigned index = get_key (key);
        for (auto &el: _hash_table[index])
            if (el->key == key)
                return el->prev == nullptr ? "none" : el->prev->value;
 
        return "none";
    }
 
    string next (string &key) {
        unsigned index = get_key (key);
        for (auto &el: _hash_table[index])
            if (el->key == key)
                return el->next == nullptr ? "none" : el->next->value;
 
        return "none";
    }
 
 
private:
    vector<list<shared_ptr<Element>>> _hash_table;
    shared_ptr<Element> last;
    unsigned _size = 1e6;
 
    unsigned get_key (string &key) {
        unsigned index = 0;
        for (char l : key)
            index = (144 * index + (l - 'a')) % _size;
 
        return index;
    }
};
 
int main() {
 
    ifstream input_file ("linkedmap.in");
    ofstream output_file ("linkedmap.out");
 
    Linked_map map;
    map.read_and_solve(input_file, output_file);
 
    return 0;
}

#include <iostream>
#include <vector>
#include <fstream>
 
using namespace std;
 
struct Element {
    string key, value;
};
 
class myMap {
public:
    myMap () {
        _hash_table.resize(_size);
    }
    myMap (unsigned size) : _size(size) {
        _hash_table.resize(size);
    }
 
    void put_value (string &key, string &value) {
        unsigned index = get_key (key);
        for (auto &el: _hash_table[index])
            if (el.key == key) {
                el.value = value;
                return;
            }
 
         _hash_table[index].push_back({key, value});
 
    }
 
    void delete_key (string &key) {
        unsigned i = get_key(key);
        for (int j = 0; j < _hash_table[i].size(); j++)
            if (_hash_table[i][j].key == key) {
                swap(_hash_table[i][j], _hash_table[i][_hash_table[i].size() - 1]);
                _hash_table[i].pop_back();
                return;
            }
    }
 
    string get_value (string &key) {
        unsigned index = get_key (key);
        for (auto &el: _hash_table[index])
            if (el.key == key)
                return el.value;
 
        return "none";
    }
 
private:
   vector<vector<Element>> _hash_table;
    unsigned _size = 1e6;
 
   unsigned get_key (string &key) {
       unsigned index = 0;
       for (char l : key)
           index = (144 * index + (l - 'a')) % _size;
 
       return index;
   }
};
 
int main() {
 
   ifstream input_file ("map.in");
   ofstream output_file ("map.out");
 
    myMap map;
    string cmd, key, value;
    while (input_file >> cmd) {
        input_file >> key;
        switch (cmd[0]) {
            case 'p':
                input_file >> value;
                map.put_value(key, value);
                break;
            case 'd':
                map.delete_key(key);
                break;
            case 'g':
                output_file << map.get_value(key) << "\n";
                break;
            default:
                break;
        }
    }
 
    input_file.close();
    output_file.close();
 
    return 0;
}

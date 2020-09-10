#include <iostream>
#include <vector>
#include <fstream>
 
using namespace std;
 
template <class T>
class mySet {
public:
    mySet () {
        _hash_table.resize(_size);
    }
    mySet (unsigned size) : _size(size) {
        _hash_table.resize(size);
    }
 
    bool exists (T key) {
        unsigned index = get_index(key);
        for (int i : _hash_table[index])
            if (i == key)
                return true;
 
        return false;
    }
 
    void insert (T key) {
        if (exists(key))
            return;
 
        unsigned index = get_index(key);
        _hash_table[index].push_back(key);
    }
 
    void delete_el (T key) {
        unsigned i = get_index(key);
        for (int j = 0; j < _hash_table[i].size(); j++)
            if (_hash_table[i][j] == key) {
                swap(_hash_table[i][j], _hash_table[i][_hash_table[i].size() - 1]);
                _hash_table[i].pop_back();
                return;
            }
 
    }
 
private:
   vector<vector<T>> _hash_table;
    unsigned _size = 1e6;
 
   unsigned get_index (T key) {
       return key % _size;
   }
};
 
int main() {
 
   ifstream input_file ("set.in");
   ofstream output_file ("set.out");
 
    mySet<int> set;
    string cmd;
    int key;
    while (input_file >> cmd) {
        input_file >> key;
        switch (cmd[0]) {
            case 'i':
                set.insert(key);
                break;
            case 'd':
                set.delete_el(key);
                break;
            case 'e':
                output_file << ((set.exists(key))? "true" : "false") << "\n";
                break;
            default:
                break;
        }
    }
 
    input_file.close();
    output_file.close();
 
    return 0;
}

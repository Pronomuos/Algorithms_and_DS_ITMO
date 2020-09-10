#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
const int range = 1e6;
struct Node {
    int key, index;
};
 
class Priority_queue {
private:
    Node m_arr [range];
    int indexes [range];
    int m_size = 0;
public:
    Priority_queue () = default;
 
    void push(int x, int index) {
        m_arr[m_size] = {x, index};
        indexes[index] = m_size++;
        shift_up(m_size - 1);
    }
 
    void shift_down (int i) {
        while (2 * i + 1 < m_size) {
            int left = 2 * i + 1, right = 2 * i + 2, j = left;
            if (right < m_size && m_arr[right].key < m_arr[left].key)
                j = right;
            if (m_arr[i].key <= m_arr[j].key)
                break;
            swap (indexes[m_arr[i].index], indexes[m_arr[j].index]);
            swap (m_arr[i], m_arr[j]);
            i = j;
        }
    }
 
    void shift_up (int i) {
        while (i && m_arr[i].key < m_arr[(i - 1) / 2].key) {
            swap(indexes[m_arr[i].index], indexes[m_arr[(i - 1) / 2].index]);
            swap(m_arr[i], m_arr[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
 
    int extract_min () {
        if (m_size) {
            int min = m_arr[0].key;
            m_size--;
            swap (indexes[m_arr[0].index], indexes[m_arr[m_size].index]);
            swap (m_arr[0], m_arr[m_size]);
            shift_down(0);
            return min;
        } else
            return INT_MIN;
    }
 
    void decrease_key (int index, int value) {
        m_arr[indexes[index]].key = value;
        shift_up(indexes[index]);
        shift_down(indexes[index]);
    }
 
};
 
int main() {
    ifstream input_file ("priorityqueue.in");
    ofstream output_file ("priorityqueue.out");
 
    Priority_queue q;
    string command;
    int counter = 1;
    while (input_file >> command) {
            if (command == "push"){
                int num;
                input_file >> num;
                q.push(num, counter);
            }
            else if (command == "extract-min") {
                int min = q.extract_min();
                if (min == INT_MIN)
                    output_file << "*\n";
                else
                    output_file << min << "\n";
                }
            else if (command == "decrease-key") {
                int index, num;
                input_file >> index >> num;
                q.decrease_key(index, num);
            }
           counter++;
    }
 
    input_file.close();
    output_file.close();
}

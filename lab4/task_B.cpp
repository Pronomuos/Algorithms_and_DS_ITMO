#include <iostream>
#include <fstream>
 
using namespace std;
 
const int range = 1e6;
 
class Queue {
private:
    int arr [range];
    int head = 0;
    int tail = 0;
public:
    void push (int num) {
        arr[head++] = num;
    }
    int pop_front () {
        return arr[tail++];
    }
};
 
int main() {
    ifstream input_file ("queue.in");
    ofstream output_file ("queue.out");
 
    int n;
    input_file >> n;
    Queue q;
    for (int i = 0; i < n; i++) {
       char operation;
       input_file >> operation;
       if (operation == '+') {
           int num;
           input_file >> num;
           q.push(num);
       }
       else
           output_file << q.pop_front() << "\n";
    }
 
 
    input_file.close();
    output_file.close();
}

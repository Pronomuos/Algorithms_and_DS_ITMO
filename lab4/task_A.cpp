#include <iostream>
#include <fstream>
 
using namespace std;
 
const int range = 1e6;
 
class Stack {
private:
    int arr [range];
    int count = 0;
public:
    void push (int num) {
        arr[count++] = num;
    }
    int pop_back () {
        return arr[--count];
    }
};
 
int main() {
    ifstream input_file ("stack.in");
    ofstream output_file ("stack.out");
 
    int n;
    input_file >> n;
    Stack q;
    for (int i = 0; i < n; i++) {
       char operation;
       input_file >> operation;
       if (operation == '+') {
           int num;
           input_file >> num;
           q.push(num);
       }
       else
           output_file << q.pop_back() << "\n";
    }
 
 
    input_file.close();
    output_file.close();
}

#include <iostream>
#include <fstream>
 
using namespace std;
 
class Stack {
private:
    int arr [100];
    int count = 0;
public:
    void push (int num) {
        arr[count++] = num;
    }
    int pop_back () {
        if (count)
            return arr[--count];
        else
            return 0;
    }
};
 
int main() {
    ifstream input_file ("postfix.in");
    ofstream output_file ("postfix.out");
 
    char ch;
    Stack st;
    while (!input_file.eof()) {
        input_file >> ch;
        if (input_file.eof())
            break;
        if (isdigit(ch))
            st.push(atoi(&ch));
        else
            switch (ch) {
                case '+':
                    st.push(st.pop_back() + st.pop_back());
                    break;
                case '-':
                    st.push(- st.pop_back() + st.pop_back());
                   break;
                case '*':
                    st.push(st.pop_back() * st.pop_back());
                    break;
                default:
                    break;
            }
        }
 
    output_file << st.pop_back() << "\n";
 
    input_file.close();
    output_file.close();
}

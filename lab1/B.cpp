#include <algorithm>
#include <fstream>
 
using namespace std;
 
 
int main() {
    ifstream input_file ("aplusbb.in");
    ofstream output_file ("aplusbb.out");
 
    long long a, b;
    input_file >> a >> b;
    output_file << a + (b * b);
 
    input_file.close();
    output_file.close();
}

#include <algorithm>
#include <fstream>
 
using namespace std;
 
 
int main() {
    ifstream input_file ("aplusb.in");
    ofstream output_file ("aplusb.out");
 
    long long a, b;
    input_file >> a >> b;
    output_file << a + b;
 
    input_file.close();
    output_file.close();
}

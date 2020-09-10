#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
const double eps = 1e-8;
 
double find_B(vector<double> &h, int n)
{
    double left = 0, right = h[0];
    while (right - left > eps) {
        h[1] = (left + right) / 2;
        bool aboveGround = false;
        for (int i = 1; i < n - 1; i++) {
            h[i + 1] = 2 * h[i] - h[i - 1] + 2;
            if (h[i + 1] < 0) {
                aboveGround = true;
                break;
            }
        }
        if (!aboveGround)
            right = h[1];
        else
            left = h[1];
    }
    return h[n - 1];
 
}
 
int main() {
    ifstream input_file ("garland.in");
    ofstream output_file ("garland.out");
 
    int n;
    input_file >> n;
    vector<double> height (n);
    input_file >> height[0];
    output_file.precision(8);
    output_file << find_B(height, n);
 
 
    input_file.close();
    output_file.close();
}

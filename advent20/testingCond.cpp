#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector <char> v2 = {'L', 'L', '#'};
    int ct = 0; 
    for (int n = 0; n < v2.size(); n++) {
        while (v2[n] != '#' && v2[n] != 'O') {
            cout << v2[n] << endl;
        }
    }

}
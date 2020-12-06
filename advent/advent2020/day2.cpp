#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main() {
    int validCt = 0;
    int min, max;
    char c1;
    stringstream ss1;
    string s1;
    while (getline(cin, s1)) {
        if (s1=="") break;
        istringstream ss(s1);
        ss >> min >> c1 >> max >> c1 >> s1 >> s1;
        if (c1 == s1[min-1] ^ c1 == s1[max-1]) {
            validCt++;
        }
    }
    cout << validCt << endl;
    return 0;
}

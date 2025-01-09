#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream inputFile;
    inputFile.open("inputs/d3.txt");
    int ct = 0;
    string s1;
    if (inputFile) {
        bool skip = false;
        int pos = 0;
        int it = 0;

        while (getline(inputFile, s1)) {
            if (it==0) {it++; continue;}
            skip = !skip;

            if (skip) {
                continue;
            }
            cout << s1;
            pos += 1;

            if (pos >= s1.size()) {
                pos %= s1.size();
            }
            cout << " AND POS IS: " << pos << " and char is " << s1[pos] << endl;

            if (s1[pos] == '#') {
                ct++;
            }
        }
    }
    cout << ct << endl;
    return 0;
}

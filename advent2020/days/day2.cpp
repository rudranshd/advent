#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int ctChar(char c, string s) {
    int ct= 0;
    for (auto x : s) {
        if (x == c) ct++;
    }
    return ct;
}

int main() {
    ifstream inputFile;
    inputFile.open("../inputs/d2.txt");
    if (!inputFile) {
        cout << "fuck" << endl;
    }
    int validCt = 0;
    int min, max;
    char c1;
    stringstream ss1;
    string s1;
    while (getline(inputFile, s1)) {
        if (s1=="") break;
        istringstream ss(s1);
        ss >> min >> c1 >> max;
        ss >> c1 >> s1 >> s1; // 1-3 a: abcde

        // int currCt = ctChar(c1, s1);
        // if (currCt >= min && currCt <= max) {
        //     validCt++;
        // }

        if (c1 == s1[min-1] ^ c1 == s1[max-1]) {
            validCt++;
        }
    }
    cout << validCt << endl;
    return 0;
}
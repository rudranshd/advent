#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

int calcRow(string rows) {
    int lo = 0; 
    int hi = 127;
    int curr;
    int i = 0;
    while (rows[i] == 'F' || rows[i] == 'B') {
        int sum = hi+lo;
        int avg = sum/2;
        if (rows[i] == 'F') {
            hi = avg ;           
        } else if (rows[i] == 'B') {
            lo = avg + 1;
        }
        i++;
    }
    curr = (lo + hi) /2;
    return curr;
}

int calcColumn(string cols) {
    int lo = 0;
    int hi = 7;
    int curr;
    for (int i = 0; i < cols.size(); i++) {
        int sum = hi+lo;
        int avg = sum/2;
        if (cols[i] == 'L') {
            hi = avg;
        } else if (cols[i] == 'R') {
            lo = avg + 1;
        }
    }    
    curr = (lo + hi) /2;
    return curr;
}

int calcID(string s) {
    return 8*calcRow(s) + calcColumn(s);
}

int main() {
    ifstream inputFile;
    inputFile.open("inputs/d5.txt");
    string s1;
    vector <int> v1;
    int curr;

    unordered_map<int, int> map2;

    int ct = 0;
    for (int i = 0 ; i < 128; i ++) {
        for (int j = 0; j < 8; j++) {
            ct++;
            map2.insert(make_pair(i*8+j, ct));

        }
    }

    cout << map2.size() << endl;
    
    if (inputFile) {
        while (getline(inputFile, s1)) {
            int curr = calcID(s1);-
            map2.erase(curr);

        }
    }

    for (auto i : map2) {
        cout << i.first << endl;
    }


    
    return 0;
}
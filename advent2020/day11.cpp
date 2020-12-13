#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
using namespace std;

bool flipSee(vector<string> &v) {
    bool flag = false;
    vector<string> v1;
    v1 = v;
    for (int i = 1; i < v.size()-1; i++) {
        for (int j = 1; j < v[i].size(); j++) {
            int occCt = 0;
            int noccCt = 0;
            int y = i;
            int x = j;
            char c = v[i][j];
            char mL = v[i][j], mR = v[i][j], tL = v[i][j], tM = v[i][j], tR = v[i][j], bL = v[i][j], bM = v[i][j], bR = v[i][j];
            vector <char> v2 = {mL, mR, tL, tM, tR, bL, bM, bR};

            for (int n = 0; n < v2.size(); n++) {
                x = j;
                y = i;
                if (n == 0) { // mL
                    while (true) {
                        x--;
                        v2[n] = v[y][x];
                        if (v[y][x] == '#' || v[y][x] == 'O' || v[y][x] == 'L') break;                    
                    }
                }  else if (n == 1) { // mR
                    while (true) {
                        x++;
                        v2[n] = v[y][x];
                        if (x >= v[i].size() || v[y][x] == '#' || v[y][x] == 'O' || v[y][x] == 'L') break;
                    }
                }  else if (n == 2) { // tL
                    while (true) {
                        y--;
                        x--;
                        v2[n] = v[y][x];
                        if (v[y][x] == '#' || v[y][x] == 'O'|| v[y][x] == 'L') break;
                    }
                } else if (n == 3) { // tM
                    while (true) {
                        y--;
                        v2[n] = v[y][x];    
                        if (v[y][x] == '#' || v[y][x] == 'O'|| v[y][x] == 'L') break;

                    }    
                } else if (n == 4) { // tR
                    while (true) {
                        y--;
                        x++;
                        v2[n] = v[y][x];
                        if (x >= v[i].size() || v[y][x] == '#' || v[y][x] == 'O'|| v[y][x] == 'L') break;
                    }
                }  else if (n == 5) { // bL
                    while (true) {
                        y++;
                        x--;
                        v2[n] = v[y][x];
                        if (v[y][x] == '#' || v[y][x] == 'O'|| v[y][x] == 'L') break;
                    }           
                } else if (n == 6) { // bM
                    while (true) {
                        y++;
                        v2[n] = v[y][x];      
                        if (v[y][x] == '#' || v[y][x] == 'O'|| v[y][x] == 'L') break;
                    }                  
                } else if (n == 7) { // bR
                    while (true) {
                        y++;
                        x++;
                        v2[n] = v[y][x];     
                        if (x >= v[i].size() || v[y][x] == '#' || v[y][x] == 'O'|| v[y][x] == 'L') break;
                    }                   
                }
                    
            }
            
            for (auto x : v2) {
                if (x == '#') occCt++;
                else if (x == 'L') noccCt++;
            }

            if (c == 'L' && occCt == 0) {
                v1[i][j] = '#';
                flag = true;
            } else if (c == '#' && occCt >= 5) {
                v1[i][j] = 'L';

                flag = true;
            }
        }
    }
    if (flag) v = v1;
    return flag;

}


bool flipAdj(vector<string> &v) {
    bool flag = false;
    vector<string> v1;
    v1 = v;
    for (int i = 1; i < v.size()-1; i++) {
        for (int j = 1; j < v[i].size(); j++) {
            int occCt = 0;
            char c = v[i][j];

            char mL = v[i][j-1];
            if (mL == '#') occCt++;
            char mR = v[i][j+1];
            if (mR == '#') occCt++;
            char tL = v[i-1][j-1];
            if (tL == '#') occCt++;
            char tM = v[i-1][j];
            if (tM == '#') occCt++;
            char tR = v[i-1][j+1];
            if (tR == '#') occCt++;
            char bL = v[i+1][j-1];
            if (bL == '#') occCt++;
            char bM = v[i+1][j];
            if (bM == '#') occCt++;
            char bR = v[i+1][j+1];
            if (bR == '#') occCt++;

            if (c == 'L' && mL != '#' && mR != '#' 
            && tL != '#' && tM != '#' && tR != '#' 
            && bL != '#' && bM != '#' && bR != '#') {
                v1[i][j] = '#';
                flag = true;
            } else if (c == '#' && occCt >= 4) {
                v1[i][j] = 'L';
                flag = true;
            }
        }
    }

    if (flag) v = v1;
    return flag;

}

int main() {
    ifstream inputFile;
    inputFile.open("inputs/i11.txt");
    vector <string> v1;
    int extraSize;
    bool first = true;
    string s1;
    string extra;
    if (inputFile) {
        while (getline(inputFile, s1)) {
            extraSize = s1.size();
            if (first) {
                first = false;
                for (int i = 0; i < extraSize+2; i++) {
                    extra += "O";
                }
                v1.push_back(extra);
            }
            s1.insert(0, "O");
            s1.insert(extraSize+1, "O");
            v1.push_back(s1);
        }
        v1.push_back(extra);
    }

    for (auto x : v1) {
        for (auto y : x) cout << y;
        cout << endl;
    }

    while (flipSee(v1)) {
        // cout << endl;
        // for (auto x : v1) {
        //     for (auto y : x) cout << y;
        //     cout << endl;
        // }
    }

    int ct = 0;

    for (auto x : v1) {
        for (auto y : x) {
            if (y == '#') ct++;
        }
    }

    cout << "the number of occupied seats is: " << ct << endl;

    return 0;
}
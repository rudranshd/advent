#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

vector <char> directions = {'E', 'N', 'W', 'S'};
int findQuadrant(pair<int,int> p) {
    if (p.first >= 0 && p.second > 0) {
        return 1;
    } else if (p.first < 0 && p.second >= 0) {
        return 2;
    } else if (p.first <= 0 && p.second< 0) {
        return 3;
    } else if (p.first > 0 && p.second <= 0) {
        return 4;
    }
}

void calcMoveWP(string s, pair<int,int> &currPos, pair<int,int> &currWP) {
    char currMove = s[0];
    s.erase(s.begin()+0);
    int num = stoi(s);
    // if (num > 270 && (currMove == 'R' || currMove == 'L')) cout << "you fuckers "  << num << endl;


    if (currMove == 'F') {
        int x = currPos.first + currWP.first*num;
        int y = currPos.second + currWP.second*num;
        currPos.first = x;
        currPos.second = y;
    } else if (currMove == 'N') {
        currWP.second += num;
    }else if (currMove == 'S') {
        currWP.second -= num;
    }else if (currMove == 'E') {
        currWP.first += num;
    }else if (currMove == 'W') {
        currWP.first -= num;
    } else if (currMove == 'R') {
        int qWP = findQuadrant(currWP);
        int x,y;
        if (qWP == 1) {
            x = currWP.first, y = currWP.second;
        } else if (qWP == 2) {
            x = currWP.second, y = -currWP.first;
        }else if (qWP == 3) {
            x = -currWP.first, y = -currWP.second;
        }else if (qWP == 4) {
            x = -currWP.second, y = currWP.first;
        }
        vector<pair<int,int>> wpV = {{x,y},{-y, x},{-x,-y},{y,-x}};

        for (int i =0 ; i < num/90; i++) {
            qWP--;
            if (qWP == 0) qWP = 4;
        }

        currWP = wpV[qWP-1];

    }else if (currMove == 'L') {
        int qWP = findQuadrant(currWP);
        int x,y;
        if (qWP == 1) {
            x = currWP.first, y = currWP.second;
        } else if (qWP == 2) {
            x = currWP.second, y = -currWP.first;
        }else if (qWP == 3) {
            x = -currWP.first, y = -currWP.second;
        }else if (qWP == 4) {
            x = -currWP.second, y = currWP.first;
        }
        vector<pair<int,int>> wpV = {{x,y},{-y, x},{-x,-y},{y,-x}};

        for (int i =0 ; i < num/90; i++) {
            qWP++;
            if (qWP == 5) qWP = 1;
        }

        currWP = wpV[qWP-1];

        
    }

    // cout << currMove << " " << num << endl;
    // cout << currWP.first << " " << currWP.second << endl;
    // cout << currPos.first << " " << currPos.second << endl;
    // cout << endl;
}


void calcMove(string s, pair<int, int> &pos, char &dir) {
    char curr = s[0];
    s.erase(s.begin()+0);
    int num = stoi(s);
    vector<char>::const_iterator it = find(directions.begin(), directions.end(), dir);
    if (curr == 'R') {
        num /= 90;
        for (int i = 0; i < num; i++) {
            if (it == directions.begin()) it = directions.end()-1;
            else it--;
        }
    } else if (curr == 'L') {
        num /= 90;
        for (int i = 0; i < num; i++) {
            if (it == directions.end()-1) it = directions.begin();
            else it++;
        }
    } else if (curr == 'N') {
        pos.second += num;
    } else if (curr == 'S') {
        pos.second -= num;
    } else if (curr == 'E') {
        pos.first += num;
    } else if (curr == 'W') {
        pos.first -= num;
    } else if (curr == 'F') {
        if (dir == 'N') pos.second += num;
        else if (dir == 'S') pos.second -= num;
        else if (dir == 'E') pos.first += num;
        else if (dir == 'W') pos.first -= num;
    }
    dir = *it;
    cout << "now position is: " << pos.first << ", " << pos.second << endl;
}

int main() {
    ifstream inputFile;
    inputFile.open("../inputs/d12.txt");
    string s1;
    pair <int, int> currPos(0,0);
    pair <int, int> currWP(10,1);
    // char currDir = 'E';
    // int lineCt =0;
    if (inputFile) {
        while(getline(inputFile, s1)) {
            // calcMove(s1, currPos, currDir);
            calcMoveWP(s1, currPos, currWP);
            // if (currPos.first == 6076) {
            //     cout << "line " << lineCt << " is : "  << s1 << endl;
            //     cout << currPos.first << " " << currPos.second << endl;
            //     cout << currWP.first << " " << currWP.second << endl;

            //     cout << endl;
            // }
            // lineCt++;
        }
    }
    cout << "Manhattan distance is: " << abs(currPos.first) + abs(currPos.second) << endl;
    return 0;
}
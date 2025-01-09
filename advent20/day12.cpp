#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

vector <char> directions = {'E', 'N', 'W', 'S'};

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
    inputFile.open("inputs/i12.txt");
    string s1;
    pair <int, int> currPos(0,0);
    char currDir = 'E';
    if (inputFile) {
        while(getline(inputFile, s1)) {
            calcMove(s1, currPos, currDir);
        }
    }
    cout << "Manhattan distance is: " << abs(currPos.first) + abs(currPos.second) << endl;
    return 0;
}
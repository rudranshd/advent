#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>
#include <regex>
using namespace std;

void addRegex(string str, regex reg, vector<pair<string, int>> &v, int i) {
    sregex_iterator currentMatch(str.begin(), str.end(), reg);
    sregex_iterator lastMatch;
    while (currentMatch != lastMatch) {
        smatch match = *currentMatch;
        v.push_back(make_pair(match.str(), i));
        currentMatch++;
        i++;
    }
}

int main() {
    ifstream inputFile;
    inputFile.open("inputs/ii13.txt");
    regex nums("\\w+");
    vector <pair <string, int> > v1;
    string s1;
    int minAfter = 0;
    if (inputFile) {
        while (getline(inputFile, s1)) {
            addRegex(s1, nums, v1, minAfter);
        }
    }

    v1.erase(v1.begin());
    for (auto x : v1) cout << x.first << ": " << x.second << endl;

    int numToCheck;
    bool reset = true;
    int counter = 1;
    for (int i = 0; i <= v1.size(); i++) {
        cout << "float v1[i].first is: " << stoi(v1[i].first) << endl;
        int curr = ceil((float) numToCheck / (float) stoi(v1[i].first)) * stoi(v1[i].first) - numToCheck;
        if (v1[i].first == "x") continue; 
        else if (reset) {
            numToCheck = stoi(v1[0].first) * counter;
            counter ++;
            i = 0;
            reset = false;
            if (numToCheck > 1000000) break;
        }
        else {
            if (curr != v1[i].second) reset = true;
            else reset = false;
        }
    }

    cout << "numToCheck is: " << numToCheck << endl;


    // int minDiff = 9999999;
    // int minID = v1[1];
    // for (int i = 1; i < v1.size(); i++) {
    //     int diff = ceil((float)target/(float)v1[i]) * v1[i] - target;
    //     if (diff < minDiff) {
    //         minDiff = diff; 
    //         minID = v1[i];
    //     }
    // }

    // cout << "id of min bus is: " << minID << ", and min diff is: " << minDiff << endl;
    // cout << "thus product is: " << minID *minDiff << endl;

    return 0;
}
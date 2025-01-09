#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;



int main() {
    ifstream inputFile; 
    inputFile.open("inputs/d6.txt");
    string s1; 
    vector <string> group;
    unordered_map<char, int> gpMap; 
    int ct = 0;
    int sum = 0;
    if (inputFile) {
        while (getline(inputFile, s1)) {
            if (s1=="") {
                ct = 0;

                for (auto i : gpMap) {
                    if (i.second == group.size()) ct++;
                }

                sum += ct;

                group.clear();
                gpMap.clear();
            } else {
                group.push_back(s1);
                for (int i = 0 ; i < s1.size(); i++) {
                    gpMap[s1[i]]++;
                }
            }
        }
    }
    cout << "sum is: " << sum << endl;
}
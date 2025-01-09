#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <deque>
#include <unordered_map>
using namespace std;

bool twoSumExists(deque <long long int> dq, long long int target) {
    unordered_map <long long int, int> m;
    int ct = 0;
    for (auto x : dq) {
        if (m.find(target-x) != m.end()) {
            return true;
        } else {
            m[x] = ct;
            ct++;
        }
    }
    return false;
}

int main() {
    ifstream inputFile;
    string s1;
    deque <long long int> dq1;
    vector <int> v1;
    long long int invalid = 0;
    inputFile.open("inputs/d9.txt");
    if (inputFile) {
        while (getline(inputFile, s1)) {
            if (dq1.size() < 25) {
                dq1.push_back(stoll(s1));
                v1.push_back(stoi(s1));
            } else if (twoSumExists(dq1, stoll(s1))) {
                dq1.pop_front();
                dq1.push_back(stoll(s1));
                v1.push_back(stoi(s1));
            } else {
                invalid = stoll(s1);
                break;
            }
        }
    }

    cout << "invalid number is: " << invalid << endl;
    int l, r;
    int currSum = v1[0], start = 0;
    for (int i = 1; i < v1.size(); i++) {

        while (currSum > invalid && start < i-1) {
            currSum = currSum-v1[start];
            start++;
        }
        if (currSum == invalid) {
            l = start;
            r = i-1;
            cout << "sum found between idx: " << l << " and " << r << endl;
        }
        if (i < v1.size()) currSum += v1[i];
    }

    int max = 0, min = INT32_MAX;
    for (int i = l; i <= r; i++) {
        if (v1[i] > max) max = v1[i];
        if (v1[i] < min) min = v1[i]; 
    }    

    cout << "the sum is: " << max + min << endl;

    return 0;
}
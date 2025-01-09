#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

bool isValid(vector<int> v) {
    int diff;
    for (int i = 0; i < v.size()-1; i++) {
        diff = v[i]-v[i+1];
        if (diff > 3)  return false;
    }
    return true;
}

int tribonacci(int n) {
    if (n == 1) return 0;
    else if (n == 2) return 1;
    else if (n == 3) return 1;
    return tribonacci(n-1) + tribonacci(n-2) + tribonacci(n-3);
}

int main() {
    // for (int i = 1; i < 10; i++) {
    //     cout << tribonacci(i) << endl;
    // }
    ifstream inputFile;
    inputFile.open("inputs/i10.txt");
    string s1;
    vector <int> v1 = {0};
    int diff1 = 0, diff2 = 0, diff3 = 0, diffCurr;
    while (inputFile) {
        while (getline(inputFile, s1)) {
            v1.push_back(stoi(s1));
        }
    }

    sort(v1.begin(), v1.end());

    for (int i = 0; i < 10; i++) {
        cout << v1[i] << endl;
    }

    v1.push_back(v1.back()+3);

    for (int i = 0; i < v1.size() ; i++)  {
        if (i == 0) 
            diffCurr = v1[0];
        else 
            diffCurr = v1[i]-v1[i-1];
        
        if (diffCurr == 1) diff1++;
        else if (diffCurr == 2) diff2++;
        else if (diffCurr == 3)  {
            diff3++;
        }
    }

    cout << "there are " << diff1 << " differences of 1 jolt, and " << diff3 << " differences of 3 jolts" << endl;
    cout << "thus product is : " << diff1 * diff3 << endl << endl;
    
    int ct;
    long long int prod = 1;
    vector <int> vCurr;
    int lIdx = 0, rIdx = 0;
    for (int i = 0; i < v1.size(); i++) {
        ct = 0;
        if (i == 0) {
            lIdx = i;
            rIdx = i+1;
            while (v1[rIdx]-v1[lIdx] == 1) {
                ct++;
                rIdx++;
                lIdx++;
            }
            ct++;
            prod *= tribonacci(ct+1);
            cout << "FOR IDX 0: " << v1[i] << ", and ct is: " << ct-1 << ", and trib is: " << tribonacci(ct+1) << endl;
        }
        else if (v1[i]-v1[i-1] == 3 && v1[i+2]-v1[i] == 2 && v1[i+1]-v1[i] == 1) {
            lIdx = i;
            rIdx = i+1;
            while (v1[rIdx]-v1[lIdx] == 1) {
                ct++;
                rIdx++;
                lIdx++;
            }
            ct++;
            prod *= tribonacci(ct+1);
            cout << v1[i] << ", and ct is: " << ct-1 << ", and trib is: " << tribonacci(ct+1) << endl;
            cout << "now prod is: " << prod << endl;
        }
    }

    cout << "there are " << prod << " combinations of the adapters" << endl;

    return 0;
}
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector <int> v1;
    int in1;
    while (cin>>in1) v1.push_back(in1);
    for (int i = 0; i < v1.size() ; i++) {
        for (int j = 1; j < v1.size(); j++) {
            for (int k = 2; k < v1.size(); k++) {
                if (v1[i] + v1[j] + v1[k] == 2020)  {
                    cout << v1[i] * v1[j] * v1[k] << endl;
                }
            }
            
        }
    }
    return 0;
}
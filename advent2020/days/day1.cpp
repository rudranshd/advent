#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    ifstream inputFile;
    inputFile.open("../inputs/d1.txt");
    string s1;
    unordered_map<int, int> iMap;
    int ct = 0;
    if (inputFile) {
        while (getline(inputFile, s1)) {
            int i1 = stoi(s1);
            auto it = iMap.find(2020-i1);
            if (it != iMap.end()) {
                cout << i1 << ", " << it->first << endl;
                cout << "the product is: " << i1 * it->first << endl;
                return 0;
            }
            iMap[i1] = ct;
            ct++;
        }
    }

    // vector <int> v1;
    // int in1;
    // while (cin>>in1) v1.push_back(in1);
    // for (int i = 0; i < v1.size() ; i++) {
    //     for (int j = 1; j < v1.size(); j++) {
    //         for (int k = 2; k < v1.size(); k++) {
    //             if (v1[i] + v1[j] + v1[k] == 2020)  {
    //                 cout << v1[i] * v1[j] * v1[k] << endl;
    //             }
    //         }
            
    //     }
    // }

    return 0;
}
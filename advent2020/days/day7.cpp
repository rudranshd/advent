#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <stack>
using namespace std;

// void helper1(string cB, unordered_map<string, vector<string>> &mp, int &gCt, bool found) {
//     if (cB == "shinygold") {
//         gCt++;
//         found = true;
//     } else if (mp[cB].empty()) {
//         return;
//     } else {
//         for (auto x : mp[cB]) {
//             int prev = gCt;
//             helper1(x, mp, gCt, found);
//             if (prev != gCt) return;
//         }
//     }
// }



int helper2(string cB, unordered_map<string, vector<pair<string, int>>> &mp) {
    stack <pair<string,int>> st;
    st.push({"shinygold",1});
    int sum = 0;

    while (!st.empty()) {
        pair<string,int> curr = st.top();
        auto bags = mp[curr.first];
        auto mul = curr.second;
        st.pop();

        for (auto x : bags) { // x.first = bag_name, x.second = bag_number
            st.push({x.first, x.second*mul});
            sum += x.second*mul;
        }

    }
    return sum;
}

int main() {
    ifstream inputFile; 
    inputFile.open("../inputs/d7.txt");
    unordered_map<string, vector<pair<string, int>>> mp;

    int goldCount = 0, individualBagCount = 0;

    string s1; 
    if (inputFile) {
        while(getline(inputFile, s1)) {
            string temp, currBag, currContains;
            int bagCt=0;
            vector<pair<string, int>> otherBags;
            stringstream ss(s1);
            
            ss >> temp;
            currBag += temp;
            ss >> temp;
            currBag += temp;
            
            while (getline(ss, temp, ' ')) {
                if (isdigit(temp[0])) {
                    bagCt = stoi(temp);
                    temp = "";
                    // cout << bagCt << " ";
                    ss >> currContains;
                    temp += currContains;
                    ss >> currContains;
                    temp += currContains;

                    otherBags.push_back({temp, bagCt});
                } 
            }

            // cout << "currBag is: " << currBag << " and it contains: " << endl;
            // for (auto x : otherBags) {
            //     cout << x << endl;
            // }

            mp[currBag] = otherBags;
            
            // cout << endl;
        }
    }

    
    // int xx = 0;
    auto x = mp["shinygold"];
    individualBagCount = helper2("shinygold", mp);

    // for (auto x : mp) {
        // helper1(x.first, mp, goldCount, 0); // can memoize part1 by caching if bag finds sg in pair or vector
    // }
    
    // cout << "number of gold bags: " << goldCount-1 << endl;

    cout << "number of individual bags: " << individualBagCount << endl;
    

    return 0;
}
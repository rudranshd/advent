#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <map>
#include <regex>
using namespace std;



int main() {
    ifstream inputFile; 
    inputFile.open("inputs/d77.txt");
    map<string, string> m1;

    regex bagCurr ("(^[\\w]+\\s[\\w]+\\sbags)");
    regex bagLink ("\\d [\\w]+ [\\w]+\\sbags?");
    smatch match1, match2;

    string s1; 
    if (inputFile) {
        while(getline(inputFile, s1)) {
            if (regex_search(s1, match1, bagCurr)) {
                string container = match1[0];
                cout << match1.str() << endl;
                string contains = match2[0];
                cout << match2.str() << endl;
            }


        }
    }


    


    

    return 0;
}
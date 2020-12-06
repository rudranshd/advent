#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Passport {
    string byr;
    string iyr;
    string eyr;
    string hgt;
    string hcl;
    string ecl;    
    string pid;
    bool metric;
};

bool checkValid (Passport p1) {
    if (stoi(p1.byr) >= 1920 && stoi(p1.byr) <= 2002 
    && stoi(p1.iyr) >= 2010 && stoi(p1.iyr) <= 2020 
    && stoi(p1.eyr) >= 2020 && stoi(p1.eyr) <= 2030
    && p1.hcl.find("#") != string::npos && p1.hcl.size() == 7
    && (p1.ecl == "amb" || p1.ecl == "blu" || p1.ecl == "brn"|| p1.ecl == "gry"|| p1.ecl == "grn" || p1.ecl == "hzl"|| p1.ecl == "oth")
    ) {
        return true;
    }

    return false;
}

bool checkValid(string e1) {
    string s1 = "byr";
    string s2 = "iyr";
    string s3 = "eyr";
    string s4 = "hgt";
    string s5 = "hcl";
    string s6 = "ecl";
    string s7 = "pid";
    string s8 = "cid";
    if (e1.find(s1) != string::npos && e1.find(s2) != string::npos && e1.find(s3) != string::npos && e1.find(s4) != string::npos&& e1.find(s5) != string::npos&& e1.find(s6) != string::npos&& e1.find(s7) != string::npos) {
        return true;
    }
    return false;
}

int main() {
    ifstream inputFile;
    inputFile.open("inputs/d4.txt");
    string s1;
    string entry;
    int validCt = 0;
    vector<Passport> v1;
    if (inputFile) {
        while (getline(inputFile, s1)) {
            if  (s1=="") {
                if (checkValid(entry)) {
                    Passport newPass;
                    newPass.byr = entry.substr(entry.find("byr:")+4, entry.find(' ', entry.find("byr:") + 4) - entry.find("byr:") - 4);
                    newPass.iyr = entry.substr(entry.find("iyr:")+4, entry.find(' ', entry.find("iyr:") + 4) - entry.find("iyr:") - 4);
                    newPass.eyr = entry.substr(entry.find("eyr:")+4, entry.find(' ', entry.find("eyr:") + 4) - entry.find("eyr:") - 4);
                    if (entry.find("cm") != string::npos) {
                        newPass.hgt = entry.substr(entry.find("hgt:")+4, entry.find(' ', entry.find("hgt:") + 4) - entry.find("hgt:") - 4);
                        newPass.metric = true;
                    } else if (entry.find("in") != string::npos) {
                        newPass.hgt = entry.substr(entry.find("hgt:")+4, entry.find(' ', entry.find("hgt:") + 4) - entry.find("hgt:") - 4);
                        newPass.metric = false;
                    } else { continue; }
                    newPass.hcl = entry.substr(entry.find("hcl:")+4, entry.find(' ', entry.find("hcl:") + 4) - entry.find("hcl:") - 4);
                    newPass.ecl = entry.substr(entry.find("ecl:")+4, entry.find(' ', entry.find("ecl:") + 4) - entry.find("ecl:") - 4);
                    newPass.pid = entry.substr(entry.find("pid:")+4, entry.find(' ', entry.find("pid:") + 4) - entry.find("pid:") - 4);
                    
                    if (newPass.pid.size() > 9) { 
                        cout << newPass.pid << endl; 
                    }
                    
                    if (checkValid(newPass)) 
                        v1.push_back(newPass);

                    validCt++;
                }
                entry = "";
                continue;
            } else {
                entry += s1;
                entry += " ";
            }
        }
    }

    for (auto p : v1) {
        if (p.pid.size() > 9) {
            cout << p.pid << endl;
        }
    }

    cout << "there are " << v1.size() << " valid passwords in the file" << endl;
    cout << "there are " << validCt << " valid entries in the file" << endl;
    return 0;
}

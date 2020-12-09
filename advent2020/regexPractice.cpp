#include <iostream>
#include <regex>
#include <string>
using namespace std;

void PrintMatches(string str, regex reg) {
    smatch matches;
    cout << boolalpha;

    while(regex_search(str, matches, reg)) {
        // cout << "Is there  a match: " << matches.ready() << endl;
        // cout << "Are there no matches: " << matches.empty() << endl;
        // cout << "Number of matches: " << matches.size() << endl;
        cout << matches.str(1) << endl;
        str = matches.suffix().str();
        cout << endl;
    }
}

void PrintMatches2(string str, regex reg) {
    sregex_iterator currentMatch(str.begin(), str.end(), reg);
    sregex_iterator lastMatch;
    while (currentMatch != lastMatch) {
        smatch match = *currentMatch;
        cout << match.str() << endl;
        currentMatch++;
    }
    cout << endl;
}

int main() {
    string str = "The ape was at the apex";
    regex reg("(ape[^ ]?)"); // choose anything that has ape, space is optional
    PrintMatches(str, reg);

    string str2 = "I picked the pickle";
    regex reg2("(pick([^ ]+)?)"); // choose anything that has pick - more characters are optional
    PrintMatches2(str2, reg2);

    string str3 = "Cat rat mat fat pat";
    regex reg3("([crmfp]at)"); // choose anything with crmfp then at
    PrintMatches2(str3, reg3);
    regex reg4("([C-Fc-f]at)"); // choose anything between C-F and c-f, then at
    PrintMatches2(str3, reg4);
    regex reg5("([^Cr]at)"); // choose anything besides C or r and then at 
    PrintMatches2(str3, reg5);

    regex reg6("([Cr]at)"); 
    string owlFood = regex_replace(str3, reg6, "Owl"); // replace those that match regex with Owl
    cout << owlFood << endl;

    string str4 = "F.B.I. I.R.S. CIA";
    regex reg7 ("([^ ]\\..\\..\\.)");
    PrintMatches2(str4, reg7);

    string str8 = "This is a\n multiline string\n that has many lines";
    regex reg8 ("\n");
    string noLBstr = regex_replace(str8, reg8, " ");
    cout << noLBstr << endl;

    // \d [0-9]
    // \D [^0-9]

    string str9 = "12345";
    regex reg9 ("\\d"); // matches numbers
    PrintMatches2(str9, reg9);

    string str10 = "123 12345 123456 1234567";
    regex reg10 ("\\d{5,7}"); // matches numbers with length 5-7
    PrintMatches2(str10, reg10);

    // \w [a-zA-Z0-9]
    // \W [^a-zA-Z0-9]

    string str11 = "412-867-5309";
    regex reg11 ("\\w{3}-\\w{3}-\\w{4}"); 
    PrintMatches2(str11, reg11);

    // \s [/f/n/r/t/v]
    // \S [^/f/n/r/t/v]

    string str12 = "Toshio Muramatsu"; // takes white space
    regex reg12 ("\\w{2,20}\\s\\w{2,20}"); 
    PrintMatches2(str12, reg12);

    string str13 = "a as ape bug"; // takes white space
    regex reg13 ("a[a-z]+"); 
    PrintMatches2(str13, reg13);

    string str14 = "db@aol.com m@.com @apple.com db@.com";
    regex reg14 ("[\\w./%+-]{1,20}@[\\w.-]{2,20}\\.[A-Za-z]{2,3}");
    PrintMatches2(str14, reg14);

    return 0;
}
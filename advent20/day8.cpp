#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <list>
#include <regex>
using namespace std;

struct Node {
    string instr;
    int val;
    bool visited;
    bool flipped;
};

bool canFlip(list <Node> lN) {
    list <Node>::iterator it;
    for (it = lN.begin(); it != lN.end(); it++) {
        if (it->instr == "nop" && !it->flipped) {
            it->instr = "jmp";
            it->flipped = true;
            return true;
            break;
        }  else if (it->instr == "jmp" && !it->flipped) {
            it->instr = "nop";
            it ->flipped = true;
            return true;
            break;
        }
    }
    return false;

}

void flip(list <Node> *lN) {
    list <Node>::iterator it;
    for (it = lN->begin(); it != lN->end(); it++) {
        if (it->instr == "nop" && !it->flipped) {
            it->instr = "jmp";
            it->flipped = true;
            cout << "the flipped Node has instr: " << it->instr << ", and val: " << it->val << endl;
            break;
        }  else if (it->instr == "jmp" && !it->flipped) {
            it->instr = "nop";
            it ->flipped = true;
            cout << "the flipped Node has instr: " << it->instr << ", and val: " << it->val << endl;
            break;
        }
    }
    // return false;
}

void flipInstr(list <Node> *lN) {
    list <Node>::iterator it;
    for (it = lN->begin(); it != lN->end(); it++) {
        if (it->instr == "nop" && !it->flipped) {
            it->flipped = true;
            break;
        }  else if (it->instr == "jmp" && !it->flipped) {
            it ->flipped = true;
            break;
        }
    }
    // return false;
}

bool isInfinite(const list <Node> lN) {
    list <Node>::iterator it;
    list <Node> lN1(lN);
    for (it = lN1.begin(); it != lN1.end(); ) {
        if (it->visited == true)  {
            return true;
        }
        if (it->instr == "nop") {
            it->visited = true;
            it++;
        } else if (it->instr == "acc") {
            it->visited = true;
            it++;
        } else if (it->instr == "jmp") {
            it->visited = true;
            advance(it, it->val);
        }
    }
    return false;
}

int main() {
    int idx = 0;
    int accCt = 0;
    list <Node> listNode;
    vector <string> inputs;
    ifstream inputFile;
    string s1;
    regex num ("[+-][\\d]+");
    smatch match;
    inputFile.open("inputs/d8.txt");
    if (inputFile) {
        while (getline(inputFile, s1)) {
            Node currNode;
            regex_search(s1, match, num);

            currNode.instr = s1.substr(0,3);
            currNode.val = stoi(match[0]);
            currNode.visited = false;
            currNode.flipped = false;
            
            cout << "the node just inserted has instr: " << currNode.instr << ", and val: " << currNode.val << endl;

            listNode.push_back(currNode);
        }
    }
    
    list <Node> listNode2(listNode);
    list <Node> listNodePrev(listNode);

    while (true) {
        flipInstr(&listNodePrev);
        flip(&listNode2);
        if (!canFlip(listNode2)) {
            break;
        }
        if (!isInfinite(listNode2)) {
            break;
        } else {
            listNode2 = listNodePrev;
        }
    }

    list <Node>::iterator it;
    
    for (it = listNode2.begin(); it != listNode2.end(); ) {
        if (it->visited == true) break;

        if (it->instr == "nop") {
            it->visited = true;
            cout << "the current Node has instr: " << it->instr << ", and val: " << it->val << " ----------- the accumulator count is: " << accCt << endl;
            it++;
        } else if (it->instr == "acc") {
            it->visited = true;
            accCt += it->val;
            cout << "the current Node has instr: " << it->instr << ", and val: " << it->val << " ----------- the accumulator count is: " << accCt << endl;
            it++;
        } else if (it->instr == "jmp") {
            cout << "the current Node has instr: " << it->instr << ", and val: " << it->val << " ----------- the accumulator count is: " << accCt << endl;
            it->visited = true;
            advance(it, it->val);
        }
        
    }

    cout << endl << "accumulator count is: " << accCt << endl;
    return 0;
}
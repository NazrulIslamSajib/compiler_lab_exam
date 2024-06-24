#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
using namespace std;
map<char, vector<string>> grammar;
set<char> nonTerminals;
set<char> terminals;
map<char, set<char>> firstSets;
map<char, set<char>> followSets;
void addProduction(char nonTerminal, const string& production) {
    grammar[nonTerminal].push_back(production);
    nonTerminals.insert(nonTerminal);
    for (char ch : production) {
        if (isupper(ch)) {
            nonTerminals.insert(ch);
        } else {
            terminals.insert(ch);
        }
    }
}
void printGrammar() {
    for (auto& prod : grammar) {
        for (auto& rule : prod.second) {
            cout << prod.first << " -> " << rule << endl;
        }
    }
}
///first
set<char> computeFirst(char symbol) {
    if (terminals.count(symbol)) {
        return {symbol};
    }

    if (firstSets.count(symbol)) {
        return firstSets[symbol];
    }

    set<char> firstSet;
    for (auto& prod : grammar[symbol]) {
        for (char ch : prod) {
            set<char> firstOfCh = computeFirst(ch);
            firstSet.insert(firstOfCh.begin(), firstOfCh.end());
            if (firstOfCh.find('ε') == firstOfCh.end()) {
                break;
            }
        }
    }
    firstSets[symbol] = firstSet;
    return firstSet;
}

void computeFirstSets() {
    for (char nt : nonTerminals) {
        computeFirst(nt);
    }
}

void printFirstSets() {
    for (auto& entry : firstSets) {
        cout << "FIRST(" << entry.first << ") = { ";
        for (char ch : entry.second) {
            cout << ch << " ";
        }
        cout << "}" << endl;
    }
}
///follow
set<char> computeFollow(char symbol) {
    if (followSets.count(symbol)) {
        return followSets[symbol];
    }

    set<char> followSet;
    if (symbol == grammar.begin()->first) {
        followSet.insert('$'); // End of input symbol
    }

    for (auto& prod : grammar) {
        for (auto& rule : prod.second) {
            size_t pos = rule.find(symbol);
            while (pos != string::npos) {
                if (pos + 1 < rule.size()) {
                    char nextSymbol = rule[pos + 1];
                    set<char> firstOfNext = computeFirst(nextSymbol);
                    followSet.insert(firstOfNext.begin(), firstOfNext.end());
                    followSet.erase('ε');
                    if (firstOfNext.count('ε')) {
                        set<char> followOfNonTerminal = computeFollow(prod.first);
                        followSet.insert(followOfNonTerminal.begin(), followOfNonTerminal.end());
                    }
                } else {
                    if (prod.first != symbol) {
                        set<char> followOfNonTerminal = computeFollow(prod.first);
                        followSet.insert(followOfNonTerminal.begin(), followOfNonTerminal.end());
                    }
                }
                pos = rule.find(symbol, pos + 1);
            }
        }
    }

    followSets[symbol] = followSet;
    return followSet;
}

void computeFollowSets() {
    for (char nt : nonTerminals) {
        computeFollow(nt);
    }
}

void printFollowSets() {
    for (auto& entry : followSets) {
        cout << "FOLLOW(" << entry.first << ") = { ";
        for (char ch : entry.second) {
            cout << ch << " ";
        }
        cout << "}" << endl;
    }
}
///main
int main() {
    addProduction('E', "TX");
    addProduction('X', "+TX");
    addProduction('X', "ε");
    addProduction('T', "FY");
    addProduction('Y', "*FY");
    addProduction('Y', "ε");
    addProduction('F', "(E)");
    addProduction('F', "a");
    printGrammar();
    computeFirstSets();
    printFirstSets();
    computeFollowSets();
    printFollowSets();

    return 0;
}

//
// Created by lolsc on 03.12.2023.
//

#include "Day3.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <regex>

using namespace std;

//formatiert das input so, dass wenn man guckt, ob eine ein sonderzeichen drum rum hat, man nicht am rand sonderfälle hat
//tdlr; es füllt ringsrum um das input weitere punkte auf, um alles etwas zu vereinfachen
// beispiel: input: | .23 | output: | ..... |
//                  | *.. |         | ..23. |
//                  | 48* |         | .*... |
//                                  | .48*. |
//                                  | ..... |
vector<string> formatInput(ifstream& input) {
    string s;
    vector<string> v;
    while (getline(input, s)) {
        v.push_back(s);
    }

    int lineLength = v[0].size();
    string pointS;
    for (int i = 0; i < lineLength; i++) pointS += ".";

    reverse(v.begin(), v.end());
    v.push_back(pointS);
    reverse(v.begin(), v.end());
    v.push_back(pointS);
    for (int i = 0; i < v.size(); i++) v[i] = "." + v[i] + ".";
    return v;
}

string findNextNumber(string& s) {
    smatch m;
    string erg;
    regex_search(s, m, regex("[0-9]+"));
    for (auto e : m) erg += e;
    return erg;
}

bool hatZeichen(vector<string>& v, int stringIndex, size_t index, size_t nLength) {
    bool erg = false;

    for (int i = stringIndex-1; i <= stringIndex+1; i++) {
        string subs = v[i].substr(index-1, nLength+2);
        //cout << i-stringIndex+2 << ". substring " << subs << endl;
        vector<char> symbols = {'*', '#', '+', '$', '/', '%', '=', '-', '@', '&'};
        for (char c : subs) {
            for (char symbol : symbols) {
                if (c == symbol) erg = true;
            }
        }
    }

    return erg;
}

vector<vector<int>> getSternCoords(vector<string>& v, int stringIndex, int index, size_t nLength) {
    vector<vector<int>> erg;
    for (int i = stringIndex-1; i <= stringIndex+1; i++) {
        string subs = v[i].substr(index-1, nLength+2);
        for (int j = 0; j < subs.size(); j++) {
            vector<int> temp = {i, index+j-1};
            if (subs[j] == '*') {
                erg.push_back(temp);
                //cout << "Stern gefunden bei y" << temp[0] << " x" << temp[1] << endl;
            }
        }
    }
    return erg;
}

int part1(ifstream& input) {
    int erg = 0;
    vector<string> v = formatInput(input);
    string nn;
    int i = 0;
    for (string s : v) {
        size_t indexsum = 0;
        nn = findNextNumber(s);
        while (!nn.empty()) {
            size_t index = s.find(nn);
            if (hatZeichen(v, i, index+indexsum, nn.size())) erg += stoi(nn);
            s = s.replace(index, nn.size(), "");
            indexsum += nn.size();
            nn = findNextNumber(s);
        }
        i++;
    }
    return erg;
}


int part2 (ifstream& input) {
    int erg = 0;
    vector<string> v = formatInput(input);
    vector<vector<int>> sternVector;
    for (int i = 0; i < v.size(); i++) {
        vector<int> temp;
        for (int j = 0; j < v[i].size(); j++) temp.push_back(1);
        sternVector.push_back(temp);
    }
    vector<vector<int>> sternAnzahl;
    for (int i = 0; i < v.size(); i++) {
        vector<int> temp;
        for (int j = 0; j < v[i].size(); j++) temp.push_back(0);
        sternAnzahl.push_back(temp);
    }
    string nn;
    int i = 0;
    for (string s : v) {
        int indexsum = 0;
        nn = findNextNumber(s);
        while (!nn.empty()) {
            int index = s.find(nn);
            vector<vector<int>> coords = getSternCoords(v, i, index+indexsum, nn.size());
            if (!coords.empty()) {
                for (auto e : coords) {
                    sternVector[e[0]][e[1]] *= stoi(nn);
                    sternAnzahl[e[0]][e[1]]++;
                }
            }
            s = s.replace(index, nn.size(), "");
            indexsum += nn.size();
            nn = findNextNumber(s);
        }
        i++;
    }
    //cout << sternAnzahl[1][4] << endl;
    for (int y = 0; y < sternVector.size(); y++) {
        for (int x = 0; x < sternVector[0].size(); x++) {
            if (sternAnzahl[y][x] == 2) erg += sternVector[y][x];
        }
    }

    return erg;
}

int main() {
    ifstream input(R"(C:\Users\lolsc\Desktop\Code Stuff\Advent of Code 2023\3\Day3input.txt)");
    cout << "Part 1: " << part1(input) << endl;
    ifstream input2(R"(C:\Users\lolsc\Desktop\Code Stuff\Advent of Code 2023\3\Day3input.txt)");
    cout << "Part 2: " << part2(input2) << endl;
    return 0;
}
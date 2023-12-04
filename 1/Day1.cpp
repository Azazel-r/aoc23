//
// Created by lolsc on 01.12.2023.
//

#include "Day1.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <regex>
using namespace std;

int index(const string& s, vector<string>& v) {
    for (int i = 0; i < v.size(); i++) {
        if (s == v[i]) return i;
    }
    return -1;
}

string umwandeln(string& s) {
    vector<string> zahlen = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    string erg;
    for (int i = 0; i < s.size(); i++) {
        string subs = s.substr(0,i);
        string subs2 = subs;
        for (const string& e : zahlen) {
            subs2 = regex_replace(subs2, regex(e), to_string(index(e, zahlen)+1));
        }
        if (subs != subs2) {
            erg += subs2;
            break;
        }

    }
    if (erg.empty()) erg += s;
    for (int i = 0; i <= s.size(); i++) {
        string subs = s.substr(s.size()-i, i);
        string subs2 = subs;
        for (const string& e : zahlen) {
            subs2 = regex_replace(subs2, regex(e), to_string(index(e, zahlen)+1));
        }
        if (subs != subs2) {
            erg += subs2;
            break;
        }
    }
    return erg;
}

int part1(ifstream& input) {
    string s;
    int first, last, sum = 0;
    bool flag = true;
    while (getline(input, s)) {
        for (char& c : s) {
            if (isdigit(c)) {
                if (flag) {
                    first = (c - '0') * 10;
                    flag = false;
                }
                last = c - '0';
            }
        }
        sum += first + last;
        flag = true;
    }
    return sum;
}

int part2(ifstream& input) {
    string s;
    int first, last, sum = 0;
    bool flag = true;

    while (getline(input, s)) {
        s = umwandeln(s);
        for (char& c : s) {
            if (isdigit(c)) {
                if (flag) {
                    first = (c - '0') * 10;
                    flag = false;
                }
                last = c - '0';
            }
        }
        sum += first + last;
        flag = true;
    }

    return sum;
}

int main() {
    ifstream input(R"(C:\Users\lolsc\Desktop\Code Stuff\Advent of Code 2023\1\Day1input.txt)");
    cout << "Part 1: " << part1(input) << endl;
    ifstream input2(R"(C:\Users\lolsc\Desktop\Code Stuff\Advent of Code 2023\1\Day1input.txt)");
    cout << "Part 2: " << part2(input2) << endl;
    return 0;
}
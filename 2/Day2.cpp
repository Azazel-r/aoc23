//
// Created by lolsc on 02.12.2023.
//

#include "Day2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

vector<string> findall(string& s_original, const regex& r) {
    string s = s_original;
    vector<string> v;
    smatch m;
    string erg;
    do {
        erg = "";
        regex_search(s, m, r);
        for (auto x: m) erg += x;
        v.push_back(erg);
        s = regex_replace(s, regex(erg), "");
    } while (!erg.empty());
    if (v[v.size()-1].empty()) v.pop_back();
    return v;
}

int part1(ifstream& input) {
    string s;
    int erg = 0;
    int sum = 0;
    int gameNr = 0;
    regex r_red("(?:1[3-9]|2[0-9]) red");
    regex r_green("(?:1[4-9]|2[0-9]) green");
    regex r_blue("(?:1[5-9]|2[0-9]) blue");
    while (getline(input, s)) {
        gameNr++;
        vector<string> reds = findall(s, r_red);
        vector<string> greens = findall(s, r_green);
        vector<string> blues = findall(s, r_blue);
        if (reds.empty() && greens.empty() && blues.empty()) {
            erg += gameNr;
            sum++;
        }
    }
    return erg;
}

int part2(ifstream& input) {
    int erg = 0;
    string s;
    while (getline(input, s)) {
        int red_max = 0, green_max = 0, blue_max = 0;
        vector<string> reds = findall(s, regex(" [1-9][0-9]* red"));
        vector<string> greens = findall(s, regex(" [1-9][0-9]* green"));
        vector<string> blues = findall(s, regex(" [1-9][0-9]* blue"));
        for (int i = 0; i < reds.size(); i++) {
            regex_replace(reds[i], regex(" red"), "");
            if (stoi(reds[i]) > red_max) red_max = stoi(reds[i]);
        }
        for (int i = 0; i < greens.size(); i++) {
            regex_replace(greens[i], regex(" green"), "");
            if (stoi(greens[i]) > green_max) green_max = stoi(greens[i]);
        }
        for (int i = 0; i < blues.size(); i++) {
            regex_replace(blues[i], regex(" blue"), "");
            if (stoi(blues[i]) > blue_max) blue_max = stoi(blues[i]);
        }
        erg += red_max * green_max * blue_max;
    }

    return erg;
}

int main() {
    ifstream input(R"(C:\Users\lolsc\Desktop\Code Stuff\Advent of Code 2023\2\Day2input.txt)");
    cout << "Part 1: " << part1(input) << endl;
    ifstream input2(R"(C:\Users\lolsc\Desktop\Code Stuff\Advent of Code 2023\2\Day2input.txt)");
    ifstream test(R"(C:\Users\lolsc\Desktop\Code Stuff\Advent of Code 2023\test.txt)");
    cout << "Part 2: " << part2(input2) << endl;
}
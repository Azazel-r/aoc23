//
// Created by lolsc on 04.12.2023.
//

#include "Day4.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

// rekursive power-funktion da C++ scheinbar keine eigene hat...
int pow(int x, int p) {
    if (p == 0) return 1;
    if (p == 1) return x;
    int temp = pow(x, p/2);
    if (p%2 == 0) return temp * temp;
    else return x * temp * temp;
}

// summe aller werte eines int-vectors, also zb sum({1,2,3,4}) = 10
int sum(vector<int> v) {
    int erg = 0;
    for (int n : v) erg += n;
    return erg;
}

// splittet einen string in einen string-vector, jeweils geteilt durch den char c
// achtung, kann manchmal leere strings ("") enthalten :/
vector<string> split(string& s, char c) {
    stringstream str(s);
    string segment;
    vector<string> erg;
    while(getline(str, segment, c)) erg.push_back(segment);
    return erg;
}

// nimmt einen string des inputs von tag 4 an, und gibt zurück, wie viel gewinne man auf der scratchcard gemacht hat
//beispiel: "Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1" => 2
int anzahlWins(string& s) {
    int erg = 0;
    s = regex_replace(s, regex("Card[ ]+[0-9]+:"), "");
    vector<string> v = split(s, '|');
    vector<string> temp;
    vector<int> winNumbers, yourNumbers;
    temp = split(v[0], ' ');
    for (auto e : temp) if (!e.empty()) winNumbers.push_back(stoi(e));
    temp = split(v[1], ' ');
    for (auto e : temp) if (!e.empty()) yourNumbers.push_back(stoi(e));
    for (int wNumber : winNumbers) {
        for (int yNumber: yourNumbers) {
            if (wNumber == yNumber) erg++;
        }
    }
    return erg;
}

// löst part 1
// idee: für jede zeile die anzahl der wins getten, und die punktzahl für jede zeile ist 2^(wins-1) // außer für wins = 0
int part1 (ifstream& input) {
    int erg = 0;
    string s;
    while (getline(input, s)) {
        int wins = anzahlWins(s);
        if (wins > 0) erg += pow(2, wins-1);
    }
    return erg;
}

// löst part 2
// idee: speichert die anzahl der cards die man hat in einem int-vector, wo jeweils "Card i" der position i-1 im vector entspricht
// am anfang hat man von jeder card eine. jetzt iteriert man durch die strings bzw. gleichzeitig auch den vector durch.
// zu beginn schaut man, wieviel man bei card 1 gewonnen hat, und erhöht dementsprechend für die nächsten cards deren anzahl
// ab card 2 macht man das ganze nicht nur einmal, sondern so oft wie viel cards man bei index 2-1 = 1 hat (wegen card 2)
// zum schluss zieht man die summe aller cards und gibt diese zurück
int part2 (ifstream& input, int length) {
    string s;
    int index = 0;
    vector<int> anzahl;
    for (int i = 0; i < length; i++) anzahl.push_back(1);

    while (getline(input, s)) {
        int wins = anzahlWins(s);
        for (int j = 0; j < anzahl[index]; j++) {
            for (int k = 1; k <= wins; k++) {
                if (index + k < length) anzahl[index + k] += 1;
            }
        }
        index++;
    }
    return sum(anzahl);
}

int main() {
    string input_path = R"(C:\Users\lolsc\Desktop\Code Stuff\Advent of Code 2023\4\Day4input.txt)";
    int n = 189; // LÄNGE DES INPUTS (AKA WIEVIEL ZEILEN DAS INPUT FILE HAT) HIER EINGEBEN!!!!
    ifstream input(input_path);
    cout << "Part 1: " << part1(input) << endl;
    ifstream input2(input_path); // muss zweimal inputten, da der erste ifstream quasi "verbraucht" ist
    cout << "Part 2: " << part2(input2, n) << endl;

    return 0;
}
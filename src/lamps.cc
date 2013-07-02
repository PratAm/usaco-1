/*
ID: joao.c.1
PROG: lamps
LANG: C++
*/

#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

string pressButton1(string input) {
    string output = "";

    for (unsigned int i = 0; i < input.size(); i++) {
        if (input[i] == '0')
            output += '1';
        else
            output += '0';
    }

    return output;
}

string pressButton2(string input) {
    string output = "";

    for (unsigned int i = 0; i < input.size(); i++) {
        if ((i + 1) % 2 != 0) {
            if (input[i] == '0')
                output += '1';
            else
                output += '0';
        } else {
            output += input[i];
        }
    }

    return output;
}

string pressButton3(string input) {
    string output = "";

    for (unsigned int i = 0; i < input.size(); i++) {
        if ((i + 1) % 2 == 0) {
            if (input[i] == '0')
                output += '1';
            else
                output += '0';
        } else {
            output += input[i];
        }
    }

    return output;
}

string pressButton4(string input) {
    string output = "";

    for (unsigned int i = 0; i < input.size(); i++) {
        if (i % 3 == 0) {
            if (input[i] == '0')
                output += '1';
            else
                output += '0';
        } else {
            output += input[i];
        }
    }

    return output;
}

void buildStates(string current,
                 int n,
                 int nsteps,
                 map<int, set<string> > & previous) {
    if (n < 4) {
        string next;

        if (n == 0)
            next = pressButton1(current);
        else if (n == 1)
            next = pressButton2(current);
        else if (n == 2)
            next = pressButton3(current);
        else if (n == 3)
            next = pressButton4(current);

        previous[nsteps + 2].insert(current);
        previous[nsteps + 1].insert(next);

        buildStates(current, n + 1, nsteps, previous);
        buildStates(next, n + 1, nsteps + 1, previous);
    }
}

map<int, set<string> > buildStates(string start) {
    map<int, set<string> > states;
    states[0].insert(start);

    buildStates(start, 0, 0, states);

    return states;
}

bool consistent(string lamps, vector<int> lampsOn, vector<int> lampsOff) {
    for (unsigned int i = 0; i < lampsOn.size(); i++)
        if (lamps[lampsOn[i]] == '0')
            return false;

    for (unsigned int i = 0; i < lampsOff.size(); i++)
        if (lamps[lampsOff[i]] == '1')
            return false;

    return true;
}

set<string> getPossibleConfigurations(int N, int C, vector<int> lampsOn,
                                                    vector<int> lampsOff) {
    string startString = string(N, '1');
    map<int, set<string> > states = buildStates(startString);

    set<string> configurations;

    while (C >= 0) {
        if (states.find(C) != states.end()) {
            set<string> toConsider = states[C];
            for (set<string>::iterator itr = toConsider.begin();
                 itr != toConsider.end();
                 itr++) {
                if (consistent(*itr, lampsOn, lampsOff))
                    configurations.insert(*itr);
            }
        }

        C -= 2;
    }

    return configurations;
}

int main() {
    ifstream fin("lamps.in");
    ofstream fout("lamps.out");

    vector<int> lampsOn;
    vector<int> lampsOff;

    int N, C;
    fin >> N >> C;

    int temp;
    while (fin >> temp && temp != -1)
        lampsOn.push_back(temp - 1);
    while (fin >> temp && temp != -1)
        lampsOff.push_back(temp - 1);

    set<string> configurations =
        getPossibleConfigurations(N, C, lampsOn, lampsOff);

    if (configurations.size() == 0) {
        fout << "IMPOSSIBLE" << endl;
    } else {
        for (set<string>::iterator itr = configurations.begin();
             itr != configurations.end();
             itr++)
            fout << *itr << endl;
    }

    return 0;
}

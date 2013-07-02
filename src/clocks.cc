/*
ID: joao.c.1
PROG: clocks
LANG: C++
*/

#include <fstream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int moves[10][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {3, 3, 0, 3, 3, 0, 0, 0, 0},  // ABDE
                    {3, 3, 3, 0, 0, 0, 0, 0, 0},  // ABC
                    {0, 3, 3, 0, 3, 3, 0, 0, 0},  // BCEF
                    {3, 0, 0, 3, 0, 0, 3, 0, 0},  // ADG
                    {0, 3, 0, 3, 3, 3, 0, 3, 0},  // BDEFH
                    {0, 0, 3, 0, 0, 3, 0, 0, 3},  // CFI
                    {0, 0, 0, 3, 3, 0, 3, 3, 0},  // DEGH
                    {0, 0, 0, 0, 0, 0, 3, 3, 3},  // GHI
                    {0, 0, 0, 0, 3, 3, 0, 3, 3}}; // EFHI

struct ClockSet {
    int clocks[9];
};

int turnClock(int hour, int sum) {
    int h = (hour + sum) % 12;
    if (h == 0)
        return 12;
    return h;
}

ClockSet apply(ClockSet clockSet, int move) {
    for (int i = 0; i < 9; i++)
        clockSet.clocks[i] = turnClock(clockSet.clocks[i], moves[move][i]);
    return clockSet;
}

ClockSet apply(ClockSet clockSet, vector<int> moves) {
    for (unsigned int i = 0; i < moves.size(); i++)
        clockSet = apply(clockSet, moves[i]);
    return clockSet;
}

bool solved(ClockSet clockSet) {
    for (unsigned int i = 0; i < 9; i++)
        if (clockSet.clocks[i] != 12)
            return false;
    return true;
}

vector<int> getMoves(const ClockSet & clockSet) {
    queue<vector<int> > q;
    q.push(vector<int>());

    while (!q.empty()) {
        vector<int> solution = q.front();
        q.pop();

        ClockSet state = apply(clockSet, solution);
        if (solved(state))
            return solution;

        int start = 1;
        int N = solution.size();
        if (N > 0)
            start = solution.back();
        if (N >= 3 &&
            solution[N - 1] == solution[N - 2] &&
            solution[N - 1] == solution[N - 3]) {
            start = start + 1;
        }

        for (unsigned int i = start; i <= 9; i++) {
            vector<int> nextSol = solution;
            nextSol.push_back(i);
            q.push(nextSol);
        }
    }

    return vector<int>();
}

int main() {
    ifstream fin("clocks.in");
    ofstream fout("clocks.out");

    ClockSet clockSet;
    for (int i = 0; i < 9; i++)
        fin >> clockSet.clocks[i];

    int maxdepth = 1;
    for (int i = 0; i < 9; i++)
        maxdepth *= 4;

    vector<int> moves = getMoves(clockSet);
    for (unsigned int i = 0; i < moves.size(); i++) {
        fout << moves[i];
        if (i + 1 < moves.size())
            fout << " ";
        else
            fout << endl;
    }

    return 0;
}

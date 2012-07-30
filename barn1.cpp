/*
ID: joao.c.1
PROG: barn1
LANG: C++
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int getMinimumNumberOfBlockedStalls(vector<int> occupiedStalls,
                                    unsigned int boards) {
    sort(occupiedStalls.begin(), occupiedStalls.end());
    int N = occupiedStalls.size();
    int blockedStalls = occupiedStalls[N - 1] - occupiedStalls[0] + 1;

    vector<int> intervals;
    for (unsigned int i = 1; i < occupiedStalls.size(); i++)
        intervals.push_back((occupiedStalls[i] - occupiedStalls[i - 1]) - 1);
    sort(intervals.begin(), intervals.end());
    reverse(intervals.begin(), intervals.end());

    for (unsigned int i = 0; i < boards - 1 && i < intervals.size(); i++)
        blockedStalls -= intervals[i];

    return blockedStalls;
}

int main() {
    ifstream fin("barn1.in");
    ofstream fout("barn1.out");

    int M, S, C;
    vector<int> occupiedStalls;
    fin >> M >> S >> C;

    for (int i = 0; i < C; i++) {
        int stall;
        fin >> stall;
        occupiedStalls.push_back(stall);
    }

    fout << getMinimumNumberOfBlockedStalls(occupiedStalls, M) << endl;

    return 0;
}

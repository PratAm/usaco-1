/*
ID: joao.c.1
PROG: fence8
LANG: C++
*/

#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

bool possibleCut(const vector<int> & boards,
                 const vector<int> & rails,
                 const int maxRail,
                 const vector<int> & boardsSum,
                 vector<bool> & usedRails,
                 int currentBoard,
                 int currentBoardLeft,
                 int railLengthLeft) {
    int N = boards.size();
    if (currentBoard >= N)
        return true;

    if (boardsSum[N] - boardsSum[currentBoard + 1] + currentBoardLeft < railLengthLeft)
        return false;

    for (int r = maxRail - 1; r >= 0; r--) {
        if (!usedRails[r] && rails[r] <= currentBoardLeft) {
            usedRails[r] = true;
            if (possibleCut(boards,
                            rails,
                            maxRail,
                            boardsSum,
                            usedRails,
                            currentBoard,
                            currentBoardLeft - rails[r],
                            railLengthLeft - rails[r]))
                return true;
            usedRails[r] = false;
            while (r > 0 && rails[r - 1] == rails[r])
                r--;
        }
    }

    if (currentBoard < N)
        return possibleCut(boards,
                           rails,
                           maxRail,
                           boardsSum,
                           usedRails,
                           currentBoard + 1,
                           boards[currentBoard + 1],
                           railLengthLeft);
    return false;
}

int getNumberOfFenceRails(vector<int> boards, vector<int> rails) {
    sort(boards.begin(), boards.end());
    sort(rails.begin(), rails.end());

    while (rails.back() > boards.back())
        rails.erase(rails.begin() + rails.size() - 1);

    int N = boards.size();
    int R = rails.size();

    vector<int> boardsSum = vector<int>(N + 1, 0);
    for (int i = 1; i <= N; i++)
        boardsSum[i] = boardsSum[i - 1] + boards[i - 1];

    vector<int> railsSum = vector<int>(R + 1, 0);
    for (int i = 1; i <= R; i++)
        railsSum[i] = railsSum[i - 1] + rails[i - 1];

    while (R >= 1 && railsSum[R] > boardsSum[N]) {
        R--;
        rails.erase(rails.begin() + rails.size() - 1);
    }

    int totalCut = 0;

    for (totalCut = 1; totalCut <= R; totalCut++) {
        vector<bool> usedRails = vector<bool>(R, false);
        int railLengthLeft = 0;
        for (int j = 0; j < totalCut; j++)
            railLengthLeft += rails[j];

        if (!possibleCut(boards, rails, totalCut, boardsSum, usedRails, 0, boards[0], railLengthLeft))
            break;
    }

    return totalCut - 1;
}

int main() {
    ifstream fin("fence8.in");
    ofstream fout("fence8.out");

    int N, R, board, rail;
    vector<int> boards;
    vector<int> rails;

    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> board;
        boards.push_back(board);
    }

    fin >> R;
    for (int i = 0; i < R; i++) {
        fin >> rail;
        rails.push_back(rail);
    }

    fout << getNumberOfFenceRails(boards, rails) << endl;

    return 0;
}

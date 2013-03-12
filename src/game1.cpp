/*
ID: joao.c.1
PROG: game1
LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

pair<int, int> getScores(vector<int> board) {
    int N = board.size();
    int T = 0;
    for (int i = 0; i < N; i++)
        T += board[i];

    vector<vector<int> > best = vector<vector<int> >(N, vector<int>(N, 0));
    vector<vector<int> > choose = vector<vector<int> >(N, vector<int>(N, -1));

    for (int i = 0; i < N; i++) {
        best[i][i] = board[i];
        choose[i][i] = i;
    }

    for (int i = 0; i < N - 1; i++) {
        if (board[i] > board[i + 1]) {
            best[i][i + 1] = board[i];
            choose[i][i + 1] = i;
        } else {
            best[i][i + 1] = board[i + 1];
            choose[i][i + 1] = i + 1;
        }
    }

    for (int l = 3; l <= N; l++) {
        for (int i = 0; i < N - l + 1; i++) {
            int cr = choose[i + 1][i + l - 1];
            int mbr = best[i + 2][i + l - 1];
            if (cr == i + l - 1)
                mbr = best[i + 1][i + l - 2];
            int cl = choose[i][i + l - 2];
            int mbl = best[i + 1][i + l - 2];
            if (cl == i + l - 2)
                mbl = best[i][i + l - 3];

            if (board[i] + mbr > board[i + l - 1] + mbl) {
                best[i][i + l - 1] = board[i] + mbr;
                choose[i][i + l - 1] = i;
            } else {
                best[i][i + l - 1] = board[i + l - 1] + mbl;
                choose[i][i + l - 1] = i + l - 1;
            }
        }
    }

    pair<int, int> res;
    res.first = best[0][N - 1];
    if (choose[0][N - 1] == 0)
        res.second = best[1][N - 1];
    else
        res.second = best[0][N - 2];

    return res;
}

int main() {
    ifstream fin("game1.in");
    ofstream fout("game1.out");

    int N, temp;
    vector<int> board;
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> temp;
        board.push_back(temp);
    }

    pair<int, int> scores = getScores(board);
    fout << scores.first << " " << scores.second << endl;

    return 0;
}

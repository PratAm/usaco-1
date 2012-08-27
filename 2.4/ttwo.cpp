/*
ID: joao.c.1
PROG: ttwo
LANG: C++
*/

#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Position {
    int i;
    int j;
    int r;

    bool operator < (const Position & p) const {
        return (i < p.i) ||
            (i == p.i && j < p.j) ||
            (i == p.i && j == p.j && r < p.r);
    }
};

int getNumberOfMinutesUntilMeeting(vector<string> grid) {
    int N = 10;
    int m[][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    pair<Position, Position> positions;
    set<pair<Position, Position> > visited;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 'F') {
                positions.first.i = i;
                positions.first.j = j;
                positions.first.r = 0;

                grid[i][j] = '.';
            }

            if (grid[i][j] == 'C') {
                positions.second.i = i;
                positions.second.j = j;
                positions.second.r = 0;

                grid[i][j] = '.';
            }
        }
    }

    int moves = 0;

    while (positions.first.i != positions.second.i ||
           positions.first.j != positions.second.j) {

        if (visited.find(positions) != visited.end())
            return 0;
        visited.insert(positions);

        int fdi = m[positions.first.r][0];
        int fdj = m[positions.first.r][1];

        if (positions.first.i + fdi < 0 ||
            positions.first.i + fdi >= N ||
            positions.first.j + fdj < 0 ||
            positions.first.j + fdj >= N ||
            grid[positions.first.i + fdi][positions.first.j + fdj] == '*') {
            positions.first.r = (positions.first.r + 1) % 4;
        } else {
            positions.first.i = positions.first.i + fdi;
            positions.first.j = positions.first.j + fdj;
        }

        int cdi = m[positions.second.r][0];
        int cdj = m[positions.second.r][1];

        if (positions.second.i + cdi < 0 ||
            positions.second.i + cdi >= N ||
            positions.second.j + cdj < 0 ||
            positions.second.j + cdj >= N ||
            grid[positions.second.i + cdi][positions.second.j + cdj] == '*') {
            positions.second.r = (positions.second.r + 1) % 4;
        } else {
            positions.second.i = positions.second.i + cdi;
            positions.second.j = positions.second.j + cdj;
        }

        moves++;
    }

    return moves;
}

int main() {
    ifstream fin("ttwo.in");
    ofstream fout("ttwo.out");

    vector<string> grid;
    for (int i = 0; i < 10; i++) {
        string s;
        fin >> s;
        grid.push_back(s);
    }

    fout << getNumberOfMinutesUntilMeeting(grid) << endl;

    return 0;
}

/*
ID: joao.c.1
PROG: camelot
LANG: C++
*/

#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

#define MAX_C 26
#define MAX_R 30

struct State {
    int d;
    int c;
    int r;
    bool k;

    State(int _d, int _c, int _r, bool _k): d(_d), c(_c), r(_r), k(_k) { }

    bool operator<(const State & that) const {
        return d > that.d;
    }
};

int kingDistance(pair<int, int> p1, pair<int, int> p2) {
    return max(abs(p1.first - p2.first), abs(p1.second - p2.second));
}

int getMinimumMoves(int R, int C, pair<char, int> king,
                    vector<pair<char, int> > knights) {
    int d[MAX_C][MAX_R][MAX_C][MAX_R][2];
    memset(d, -1, sizeof(d));

    int kMoves[][2] = {{-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}};
    int K = knights.size();
    pair<int, int> k = make_pair(king.first - 'A', king.second - 1);
    vector<pair<int, int> > ns;
    for (int i = 0; i < K; i++)
        ns.push_back(make_pair(knights[i].first - 'A', knights[i].second - 1));

    for (int i = 0; i < K; i++) {
        pair<int, int> start = ns[i];
        State s1 = State(0, start.first, start.second, false);
        State s2 = State(kingDistance(start, k), start.first, start.second, true);

        priority_queue<State> pq;
        pq.push(s1);
        pq.push(s2);

        while (!pq.empty()) {
            State s = pq.top(); pq.pop();

            int & current = d[start.first][start.second][s.c][s.r][s.k];
            if (current == -1 || s.d <= current) {
                current = s.d;

                for (int j = 0; j < 8; j++) {
                    State n1 = State(s.d + 1, s.c + kMoves[j][0], s.r + kMoves[j][1], s.k);

                    if (n1.c < 0 || n1.c >= C || n1.r < 0 || n1.r >= R)
                        continue;

                    int & n1Current = d[start.first][start.second][n1.c][n1.r][n1.k];
                    if (n1Current == -1 || n1.d < n1Current) {
                        n1Current = n1.d;
                        pq.push(n1);
                    }

                    if (!s.k) {
                        State n2 =
                            State(s.d + 1 +
                                  kingDistance(k, make_pair(n1.c, n1.r)),
                                  n1.c, n1.r, true);
                        int & n2Current = d[start.first][start.second][n2.c][n2.r][true];
                        if (n2Current == -1 || n2.d < n2Current) {
                            n2Current = n2.d;
                            pq.push(n2);
                        }
                    }
                }
            }
        }
    }

    int best = -1;
    for (int i = 0; i < C; i++) {
        for (int j = 0; j < R; j++) {
            int current = 0;
            bool possible = true;
            for (int l = 0; l < K; l++) {
                if (d[ns[l].first][ns[l].second][i][j][false] < 0) {
                    possible = false;
                    break;
                }
                current += d[ns[l].first][ns[l].second][i][j][false];
            }

            if (!possible)
                continue;
            current += kingDistance(k, make_pair(i, j));

            int dSum = current;
            for (int l = 0; l < K; l++) {
                int newD =
                    dSum -
                    kingDistance(k, make_pair(i, j)) -
                    d[ns[l].first][ns[l].second][i][j][false] +
                    d[ns[l].first][ns[l].second][i][j][true];

                if (newD < current)
                    current = newD;
            }

            if (best == -1 || current < best)
                best = current;
        }
    }

    return best;
}

int main() {
    ifstream fin("camelot.in");
    ofstream fout("camelot.out");

    int R, C;
    pair<char, int> king, temp;
    vector<pair<char, int> > knights;

    fin >> R >> C;
    fin >> king.first >> king.second;
    while (fin >> temp.first >> temp.second)
        knights.push_back(temp);

    fout << getMinimumMoves(R, C, king, knights) << endl;

    return 0;
}

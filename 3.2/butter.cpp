/*
ID: joao.c.1
PROG: butter
LANG: C++
*/

#include <fstream>
#include <map>
#include <vector>

using namespace std;

int getMinimumWalkingDistance(int P,
                              vector<int> cows,
                              vector<pair<pair<int, int>, int> > c) {
    int C = c.size();
    int N = cows.size();
    vector<vector<int> > m = vector<vector<int> >(P, vector<int>(P, -1));

    for (int i = 0; i < P; i++)
        m[i][i] = 0;

    for (int i = 0; i < C; i++) {
        m[c[i].first.first - 1][c[i].first.second - 1] = c[i].second;
        m[c[i].first.second - 1][c[i].first.first - 1] = c[i].second;
    }

    for (int k = 0; k < P; k++)
        for (int i = 0; i < P; i++)
            if (m[i][k] >= 0)
                for (int j = 0; j < P; j++)
                    if (m[k][j] >= 0 &&
                        (m[i][k] + m[k][j] < m[i][j] || m[i][j] == -1))
                        m[i][j] = m[i][k] + m[k][j];

    int b = -1;
    for (int i = 0; i < P; i++) {
        int s = 0;
        for (int k = 0; k < N; k++)
            s += m[i][cows[k] - 1];
        if (b == -1 || s < b)
            b = s;
    }

    return b;
}

int main() {
    ifstream fin("butter.in");
    ofstream fout("butter.out");

    int N, P, C;
    fin >> N >> P >> C;

    vector<int> pasturesWithCowsOn;
    for (int i = 0; i < N; i++) {
        int t;
        fin >> t;
        pasturesWithCowsOn.push_back(t);
    }

    vector<pair<pair<int, int>, int> > connections;
    for (int i = 0; i < C; i++) {
        int p1, p2, l;
        fin >> p1 >> p2 >> l;
        connections.push_back(make_pair(make_pair(p1, p2), l));
    }

    fout << getMinimumWalkingDistance(P,
                                      pasturesWithCowsOn,
                                      connections) << endl;

    return 0;
}

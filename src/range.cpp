/*
ID: joao.c.1
PROG: range
LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

vector<pair<int, int> > getGrazingAreas(vector<string> field) {
    int N = field.size();
    vector<vector<vector<bool> > > ravaged =
        vector<vector<vector<bool> > >(N, vector<vector<bool> >(N, vector<bool>(N + 1, false)));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            ravaged[i][j][1] = (field[i][j] == '0');

    for (int l = 2; l <= N; l++) {
        for (int i = 0; i < N - l + 1; i++) {
            for (int j = 0; j < N - l + 1; j++) {
                int d = l / 2 + l % 2;
                int inc = l / 2;

                ravaged[i][j][l] =
                    ravaged[i][j][d] ||
                    ravaged[i + inc][j][d] ||
                    ravaged[i][j + inc][d] ||
                    ravaged[i + inc][j + inc][d];
            }
        }
    }

    vector<pair<int, int> > res;

    for (int l = 2; l <= N; l++) {
        int c = 0;
        for (int i = 0; i < N - l + 1; i++)
            for (int j = 0; j < N - l + 1; j++)
                if (!ravaged[i][j][l])
                    c++;
        if (c > 0)
            res.push_back(make_pair(l, c));
    }

    return res;
}

int main() {
    ifstream fin("range.in");
    ofstream fout("range.out");

    int N;
    string t;
    vector<string> field;
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> t;
        field.push_back(t);
    }

    vector<pair<int, int> > areas = getGrazingAreas(field);
    int A = areas.size();
    for (int i = 0; i < A; i++)
        fout << areas[i].first << " " << areas[i].second << endl;

    return 0;
}

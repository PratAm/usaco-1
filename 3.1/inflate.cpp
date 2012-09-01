/*
ID: joao.c.1
PROG: inflate
LANG: C++
*/

#include <fstream>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

int getMaximumPoints(vector<pair<int, int> > categories, int M) {
    int N = categories.size();
    vector<int> maxScore = vector<int>(M + 1, 0);

    for (int i = 0; i <= M; i++) {
        for (int j = 0; j < N; j++) {
            if (i - categories[j].second >= 0) {
                int tempScore = maxScore[i - categories[j].second] +
                    categories[j].first;
                if (tempScore > maxScore[i])
                    maxScore[i] = tempScore;
            }
        }
    }

    int bestScore = 0;
    for (int i = 0; i <= M; i++)
        if (maxScore[i] > bestScore)
            bestScore = maxScore[i];

    return bestScore;
}

int main() {
    ifstream fin("inflate.in");
    ofstream fout("inflate.out");

    int M, N;
    fin >> M >> N;
    vector<pair<int, int> > categories;

    for (int i = 0; i < N; i++) {
        int p, m;
        fin >> p >> m;
        categories.push_back(make_pair(p, m));
    }

    fout << getMaximumPoints(categories, M) << endl;

    return 0;
}

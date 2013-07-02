/*
ID: joao.c.1
PROG: rockers
LANG: C++
*/

#include <algorithm>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

int getMaxSongs(vector<int> songs, int T, int M) {
    int N = songs.size();
    int best[M * T + 1][N];
    memset(best, 0, sizeof(best));

    if (songs[0] <= T)
        for (int i = songs[0]; i <= M * T; i++)
            best[i][0] = 1;

    for (int i = 0; i < N; i++)
        best[0][i] = 0;

    for (int i = 1; i < N; i++) {
        for (int j = 1; j <= M * T; j++) {
            if (songs[i] > T || j < songs[i]) {
                best[j][i] = max(best[j - 1][i], best[j][i - 1]);
            } else {
                if ((j - 1) / T == (j - songs[i]) / T) {
                    best[j][i] =
                        max(max(best[j - 1][i],
                                best[j - songs[i]][i - 1] + 1),
                            best[j][i - 1]);
                } else {
                    best[j][i] = max(best[j - 1][i], best[j][i - 1]);
                }
            }
        }
    }

    return best[M * T][N - 1];
}

int main() {
    ifstream fin("rockers.in");
    ofstream fout("rockers.out");

    int N, T, M;
    fin >> N >> T >> M;
    vector<int> songs;
    for (int i = 0; i < N; i++) {
        int song;
        fin >> song;
        songs.push_back(song);
    }

    fout << getMaxSongs(songs, T, M) << endl;

    return 0;
}

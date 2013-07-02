/*
ID: joao.c.1
PROG: stamps
LANG: C++
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int getContiguousPostageValues(vector<int> stamps, int K) {
    sort(stamps.begin(), stamps.end());

    int S = stamps.size();
    int maxValue = stamps.back() * K;
    vector<int> minStamps(maxValue + 1, 0);

    for (int i = 1; i <= maxValue; i++) {
        for (int j = 0; j < S; j++) {
            if (i - stamps[j] >= 0 &&
                (minStamps[i - stamps[j]] != 0 || i - stamps[j] == 0) &&
                (minStamps[i] == 0 || minStamps[i - stamps[j]] + 1 < minStamps[i])) {
                minStamps[i] = minStamps[i - stamps[j]] + 1;
            }
        }
    }

    int n = 0;
    for (int i = 1; i <= maxValue && minStamps[i] != 0 && minStamps[i] <= K; i++)
        n++;

    return n;
}

int main() {
    ifstream fin("stamps.in");
    ofstream fout("stamps.out");

    int K, N;
    vector<int> stamps;
    fin >> K >> N;

    for (int i = 0; i < N; i++) {
        int s;
        fin >> s;
        stamps.push_back(s);
    }

    fout << getContiguousPostageValues(stamps, K) << endl;

    return 0;
}

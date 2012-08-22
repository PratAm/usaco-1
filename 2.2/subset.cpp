/*
ID: joao.c.1
PROG: subset
LANG: C++
*/

#include <fstream>
#include <vector>

using namespace std;

int getNumberOfSameSumPartitions(int N) {
    int totalSum = N * (N + 1) / 2;

    if (totalSum % 2 != 0)
        return 0;

    int targetSum = totalSum / 2;
    vector<vector<long long> > sums =
        vector<vector<long long> >(targetSum + 1, vector<long long>(N + 1, 0));

    sums[0][0] = 1;

    for (int i = 1; i <= N; i++) {
        for (int j = targetSum; j >= 0; j--)
            sums[j][i] = sums[j][i - 1];

        for (int j = targetSum; j >= 0; j--) {
            int prev = j - i;
            if (prev >= 0 && sums[prev][i - 1] > 0)
                sums[j][i] += sums[prev][i - 1];
        }
    }

    return sums[targetSum][N] / 2;
}

int main() {
    ifstream fin("subset.in");
    ofstream fout("subset.out");

    int N;
    fin >> N;
    fout << getNumberOfSameSumPartitions(N) << endl;

    return 0;
}

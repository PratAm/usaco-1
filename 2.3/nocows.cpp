/*
ID: joao.c.1
PROG: nocows
LANG: C++
*/

#include <fstream>
#include <map>

using namespace std;

#define MOD 9901

int getNumberOfPedigreesRelaxed(int N, int K) {
    static map<pair<int, int>, int> pedigrees;

    pair<int, int> c = make_pair(N, K);

    if (pedigrees.find(c) == pedigrees.end()) {
        pedigrees[c] = 0;
        if (N % 2 != 0 && K > 0) {
            if (N == 1)
                pedigrees[c] = 1;
            else {
                int R = N - 1;
                for (int i = 1; i < R; i += 2) {
                    pedigrees[c] = (pedigrees[c] +
                                    getNumberOfPedigreesRelaxed(i, K - 1) *
                                    getNumberOfPedigreesRelaxed(R - i, K - 1)) % MOD;
                }
            }
        }
    }

    return pedigrees[c];
}

int getNumberOfPedigrees(int N, int K) {
    static map<pair<int, int>, int> pedigrees;

    pair<int, int> c = make_pair(N, K);

    if (pedigrees.find(c) == pedigrees.end()) {
        pedigrees[c] = 0;
        if (N % 2 != 0 && K > 0 && N >= 2 * K - 1) {
            if (N == 1)
                pedigrees[c] = 1;
            else {
                int R = N - 1;
                for (int i = 1; i < R; i += 2) {
                    pedigrees[c] = (pedigrees[c] +
                                    getNumberOfPedigrees(i, K - 1) *
                                    getNumberOfPedigrees(R - i, K - 1)) % MOD;

                    pedigrees[c] = (pedigrees[c] +
                                    getNumberOfPedigrees(i, K - 1) *
                                    getNumberOfPedigreesRelaxed(R - i, K - 2)) % MOD;

                    pedigrees[c] = (pedigrees[c] +
                                    getNumberOfPedigreesRelaxed(i, K - 2) *
                                    getNumberOfPedigrees(R - i, K - 1)) % MOD;
                }
            }
        }
    }

    return pedigrees[c];
}

int main() {
    ifstream fin("nocows.in");
    ofstream fout("nocows.out");

    int N, K;
    fin >> N >> K;

    fout << getNumberOfPedigrees(N, K) << endl;

    return 0;
}

/*
ID: joao.c.1
PROG: fact4
LANG: C++
*/

#include <fstream>

using namespace std;

int getRightmostNonZeroDigitOfFactorial(int N) {
    int v = 1;

    for (int i = 1; i <= N; i++) {
        v *= i;

        int p = 1;
        int t = v;
        while (t % 10 == 0) {
            p *= 10;
            t /= 10;
        }

        v /= p;
        v %= 10000;
    }

    return v % 10;
}

int main() {
    ifstream fin("fact4.in");
    ofstream fout("fact4.out");

    int N;
    fin >> N;

    fout << getRightmostNonZeroDigitOfFactorial(N) << endl;

    return 0;
}

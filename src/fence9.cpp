/*
ID: joao.c.1
PROG: fence9
LANG: C++
*/

#include <cmath>
#include <fstream>

using namespace std;

#define EPS 1e-6

int N, M, P;

int getNCows() {
    int total = 0;

    double m1 = (double) N / M;
    double m2 = (double) (N - P) / M;
    for (int x = 1; x < M; x++) {
        double y1 = m1 * x;
        double y2 = P + m2 * x;

        int yy2 = floor(y2);
        if (y2 - yy2 > EPS)
            yy2++;

        int yy1 = ceil(y1);
        if (yy1 - y1 > EPS)
            yy1--;

        total += yy2 - yy1 - 1;
    }

    return total;
}

int main() {
    ifstream fin("fence9.in");
    ofstream fout("fence9.out");

    fin >> N >> M >> P;
    fout << getNCows() << endl;

    return 0;
}

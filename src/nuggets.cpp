/*
ID: joao.c.1
PROG: nuggets
LANG: C++
*/

#include <cstring>
#include <fstream>

using namespace std;

#define MAXN 10
#define MAXV 256
#define MAXS (MAXV * MAXV)

int N;
int nuggets[MAXN];
bool possible[MAXS];

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int getLargestNuggets() {
    bool valid = false;
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            if (gcd(nuggets[i], nuggets[j]) == 1)
                valid = true;

    if (valid) {
        memset(possible, false, sizeof(possible));
        possible[0] = true;

        for (int i = 1; i < MAXS; i++)
            for (int j = 0; j < N; j++)
                if (i - nuggets[j] >= 0)
                    possible[i] |= possible[i - nuggets[j]];

        for (int j = MAXS - 1; j >= 0; j--)
            if (!possible[j])
                return j;
    }
    return 0;
}

int main() {
    ifstream fin("nuggets.in");
    ofstream fout("nuggets.out");

    fin >> N;
    for (int i = 0; i < N; i++)
        fin >> nuggets[i];
    fout << getLargestNuggets() << endl;

    return 0;
}

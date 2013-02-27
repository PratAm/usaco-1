/*
ID: joao.c.1
PROG: kimbits
LANG: C++
*/

#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<unsigned int> > getPossibleStrings(int N, int L) {
    vector<vector<unsigned int> > ps =
        vector<vector<unsigned int> >(N + 1, vector<unsigned int>(L + 1, 0));
    vector<vector<unsigned int> > psu =
        vector<vector<unsigned int> >(N + 1, vector<unsigned int>(L + 1, 0));

    for (int i = 0; i <= N; i++)
        ps[i][0] = 1;

    for (int i = 1; i <= N; i++)
        for (int l = 1; l <= L; l++)
            ps[i][l] = ps[i - 1][l] + ps[i - 1][l - 1];

    for (int i = 0; i <= N; i++)
        for (int l = 0; l <= L; l++)
            for (int k = 0; k <= l; k++)
                psu[i][l] += ps[i][k];

    for (int i = 0; i <= L; i++)
        psu[0][i] = 1;

    return psu;
}

string getIthElement(int N, int L, unsigned int I) {
    static vector<vector<unsigned int> > p;
    if (p.size() == 0)
        p = getPossibleStrings(N, L);

    if (N <= 0)
        return "";
    else if (I > p[N - 1][L])
        return "1" + getIthElement(N - 1, L - 1, I - p[N - 1][L]);
    else
        return "0" + getIthElement(N - 1, L, I);
}

int main() {
    ifstream fin("kimbits.in");
    ofstream fout("kimbits.out");

    int N, L;
    unsigned int I;
    fin >> N >> L >> I;

    fout << getIthElement(N, L, I) << endl;

    return 0;
}

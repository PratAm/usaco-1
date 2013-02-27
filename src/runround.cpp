/*
ID: joao.c.1
PROG: runround
LANG: C++
*/

#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool isRunaroundNumber(unsigned long n) {
    vector<int> digits = vector<int>(10, 0);
    string s = "";

    while (n) {
        int d = n % 10;
        if (d == 0 || digits[d] > 0)
            return false;
        digits[d]++;
        n /= 10;
        s = (char) (d + '0') + s;
    }

    int d = s.size();
    int c = 0;

    for (int i = 0; i < d; i++) {
        int steps = s[c] - '0';
        c = (c + steps) % d;
        if (digits[s[c] - '0'] > 1)
            return false;
        digits[s[c] - '0']++;
    }

    return true;
}

unsigned getNextRunaroundNumber(unsigned long M) {
    int N = M + 1;

    while (!isRunaroundNumber(N))
        N++;

    return N;
}

int main() {
    ifstream fin("runround.in");
    ofstream fout("runround.out");

    unsigned long M;
    fin >> M;
    fout << getNextRunaroundNumber(M) << endl;

    return 0;
}

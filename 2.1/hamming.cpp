/*
ID: joao.c.1
PROG: hamming
LANG: C++
*/

#include <fstream>
#include <vector>

using namespace std;

int countBits(int n) {
    int c;
    for (c = 0; n; c++)
        n &= (n - 1);
    return c;
}

int hammingDistance(int a, int b) {
    return countBits(a ^ b);
}

bool valid(int n, vector<int> values, int D) {
    for (unsigned int i = 0; i < values.size(); i++) {
        if (hammingDistance(n, values[i]) < D)
            return false;
    }
    return true;
}

vector<int> getCodewords(int N, int B, int D, vector<int> current = vector<int>()) {
    int S = current.size();

    if (S == N)
        return current;
    else if (S == 0) {
        current.push_back(0);
        return getCodewords(N, B, D, current);
    } else {
        int maxN = 1 << B;
        for (int i = current.back() + 1; i < maxN; i++) {
            if (valid(i, current, D)) {
                vector<int> next = current;
                next.push_back(i);
                vector<int> res = getCodewords(N, B, D, next);
                if ((int) res.size() == N)
                    return res;
            }
        }

        return vector<int>();
    }
}

int main() {
    ifstream fin("hamming.in");
    ofstream fout("hamming.out");

    int N, B, D;
    fin >> N >> B >> D;

    vector<int> codewords = getCodewords(N, B, D);
    for (unsigned int i = 0; i < codewords.size(); i++) {
        fout << codewords[i];
        if (i + 1 < codewords.size() && (i + 1) % 10 != 0)
            fout << " ";
        else
            fout << endl;
    }

    return 0;
}

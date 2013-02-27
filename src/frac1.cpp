/*
ID: joao.c.1
PROG: frac1
LANG: C++
*/

#include <fstream>
#include <set>

using namespace std;

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

struct Fraction {
    int numerator;
    int denominator;

    Fraction(int _numerator, int _denominator) {
        int d = gcd(_numerator, _denominator);
        numerator = _numerator / d;
        denominator = _denominator / d;
    }

    bool operator<(const Fraction & f) const {
        return numerator * f.denominator < f.numerator * denominator;
    }
};

set<Fraction> getFractions(int N) {
    set<Fraction> fractions;

    fractions.insert(Fraction(0, 1));
    fractions.insert(Fraction(1, 1));

    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            fractions.insert(Fraction(i, j));
        }
    }

    return fractions;
}

int main() {
    ifstream fin("frac1.in");
    ofstream fout("frac1.out");

    int N;
    fin >> N;

    set<Fraction> fractions = getFractions(N);
    for (set<Fraction>::iterator itr = fractions.begin();
         itr != fractions.end();
         itr++) {
        fout << itr->numerator << "/" << itr->denominator << endl;
    }

    return 0;
}

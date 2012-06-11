/*
ID: joao.c.1
PROG: ride
LANG: C++
*/

#include <fstream>
#include <string>

using namespace std;

int convertToNumber(string s) {
    int n = 1;
    for (size_t i = 0; i < s.size(); i++)
        n = (n * (s[i] - 'A' + 1)) % 47;
    return n;
}

bool willBePicked(string comet, string group) {
    return convertToNumber(comet) == convertToNumber(group);
}

int main() {
    ifstream fin("ride.in");
    ofstream fout("ride.out");

    string comet, group;
    fin >> comet >> group;
    fout << (willBePicked(comet, group) ? "GO" : "STAY") << endl;

    return 0;
}

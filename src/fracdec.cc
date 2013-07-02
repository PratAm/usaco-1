/*
ID: joao.c.1
PROG: fracdec
LANG: C++
*/

#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

string getDecimalExpansion(int N, int D) {
    string expansion = "";
    int integer = N / D;
    ostringstream ss;
    ss << integer;
    expansion = ss.str() + ".";
    int decimal = N - integer * D;

    map<int, int> visited;
    while (decimal != 0) {
        if (visited.find(decimal) != visited.end()) {
            int p = visited[decimal];
            expansion = expansion.substr(0, p) + "(" +
                expansion.substr(p, expansion.size() - p) + ")";
            break;
        }

        int d = (decimal * 10) / D;
        expansion += d + '0';
        visited[decimal] = expansion.size() - 1;
        decimal = (decimal * 10) - d * D;
    }

    if (expansion[expansion.size() - 1] == '.')
        expansion += '0';

    return expansion;
}

int main() {
    ifstream fin("fracdec.in");
    ofstream fout("fracdec.out");

    int N, D;
    fin >> N >> D;

    string expansion = getDecimalExpansion(N, D);
    while (expansion.size() > 0) {
        string line = expansion;
        if (expansion.size() > 76)
            line = expansion.substr(0, 76);

        if (expansion.size() > 76)
            expansion = expansion.substr(76);
        else
            expansion = "";

        fout << line << endl;
    }

    return 0;
}

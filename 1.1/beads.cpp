/*
ID: joao.c.1
PROG: beads
LANG: C++
*/

#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ifstream fin("beads.in");
    ofstream fout("beads.out");

    unsigned int N;
    string necklace;
    fin >> N >> necklace;
    necklace += necklace;
    unsigned int maxBeads = 0;

    for (unsigned int i = 0; i < necklace.size(); i++) {
        int colorChanges = 0;
        char currentColor = necklace[i];
        for (unsigned int j = i + 1; j < necklace.size() && colorChanges < 2; j++) {
            if (necklace[j] != 'w') {
                if (currentColor == 'w')
                    currentColor = necklace[j];
                else if (currentColor != necklace[j])
                    colorChanges++;
                currentColor = necklace[j];
            }
            if ((j - i) > maxBeads)
                maxBeads = (j - i);
        }
    }

    fout << min(maxBeads, N) << endl;

    return 0;
}

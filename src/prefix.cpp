/*
ID: joao.c.1
PROG: prefix
LANG: C++
*/

#include <fstream>
#include <string>
#include <vector>

using namespace std;

int getLengthOfLongestPrefix(string sequence, vector<string> primitives) {
    int N = sequence.size();
    int P = primitives.size();
    vector<bool> prefix = vector<bool>(N + 1, false);
    int longest = 0;
    prefix[0] = true;

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < P; j++) {
            string primitive = primitives[j];
            int s = primitive.size();
            if (i - s >= 0 && prefix[i - s] &&
                    sequence.substr(i - s, s) == primitive) {
                prefix[i] = true;
                if (i > longest)
                    longest = i;
            }
        }
    }

    return longest;
}

int main() {
    ifstream fin("prefix.in");
    ofstream fout("prefix.out");

    vector<string> primitives;
    string sequence = "";
    string temp;

    while (fin >> temp && temp != ".")
        primitives.push_back(temp);
    while (fin >> temp)
        sequence += temp;

    fout << getLengthOfLongestPrefix(sequence, primitives) << endl;

    return 0;
}

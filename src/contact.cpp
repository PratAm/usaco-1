/*
ID: joao.c.1
PROG: contact
LANG: C++
*/

#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

bool patternComparator(const string & s1, const string & s2) {
    return s1.size() < s2.size() || (s1.size() == s2.size() && s1 < s2);
}

map<int, vector<string> > getRepeatingPatterns(string sequence, int A, int B) {
    int N = sequence.size();

    map<string, int> count;

    for (int i = 0; i < N; i++)
        for (int j = A; j <= B; j++)
            if (i + j <= N)
                count[sequence.substr(i, j)]++;

    map<int, vector<string> > patterns;

    for (map<string, int>::iterator itr = count.begin();
         itr != count.end();
         itr++)
        patterns[itr->second].push_back(itr->first);

    for (map<int, vector<string> >::iterator itr = patterns.begin();
         itr != patterns.end();
         itr++)
        sort(itr->second.begin(), itr->second.end(), patternComparator);

    return patterns;
}

int main() {
    ifstream fin("contact.in");
    ofstream fout("contact.out");

    int A, B, N;
    fin >> A >> B >> N;
    fin.get();

    string s = "";
    string temp;
    while (getline(fin, temp))
        s += temp;

    map<int, vector<string> > patterns = getRepeatingPatterns(s, A, B);
    int c = 0;

    for (map<int, vector<string> >::reverse_iterator itr = patterns.rbegin();
         itr != patterns.rend() && c < N;
         itr++, c++) {
        fout << itr->first << endl;
        vector<string> p = itr->second;
        int l = 1;
        for (unsigned int i = 0; i < p.size(); i++, l++) {
            fout << p[i];
            if (i + 1 < p.size() && l % 6 != 0)
                fout << " ";
            else
                fout << endl;
        }
    }

    return 0;
}

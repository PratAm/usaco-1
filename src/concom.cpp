/*
ID: joao.c.1
PROG: concom
LANG: C++
*/

#include <fstream>
#include <map>
#include <vector>

using namespace std;

struct ControlPercentage {
    int c1;
    int c2;
    int p;
};

void addOwn(int c1, int c2, int p,
            vector<vector<int> > & owns,
            vector<vector<bool> > & controls);
void addControl(int c1, int c2,
                vector<vector<int> > & owns,
                vector<vector<bool> > & controls);

void addControl(int c1, int c2,
                vector<vector<int> > & owns,
                vector<vector<bool> > & controls) {
    if (controls[c1][c2])
        return;

    controls[c1][c2] = true;

    for (unsigned int i = 0; i < controls.size(); i++)
        owns[c1][i] += owns[c2][i];

    for (unsigned int i = 0; i < controls.size(); i++)
        if (controls[i][c1])
            addControl(i, c2, owns, controls);

    for (unsigned int i = 0; i < controls.size(); i++)
        if (owns[c1][i] > 50)
            addControl(c1, i, owns, controls);
}

void addOwn(int c1, int c2, int p,
            vector<vector<int> > & owns,
            vector<vector<bool> > & controls) {
    for (unsigned int i = 0; i < controls.size(); i++)
        if (controls[i][c1])
            owns[i][c2] += p;

    for (unsigned int i = 0; i < controls.size(); i++)
        if (owns[i][c2] > 50)
            addControl(i, c2, owns, controls);
}

vector<pair<int, int> > getControllingCompanies(vector<ControlPercentage> controlPercentages) {
    int maxN = 0;
    int N = controlPercentages.size();

    for (int i = 0; i < N; i++) {
        if (controlPercentages[i].c1 > maxN)
            maxN = controlPercentages[i].c1;
        if (controlPercentages[i].c2 > maxN)
            maxN = controlPercentages[i].c2;
    }

    vector<vector<int> > owns =
        vector<vector<int> >(maxN + 1, vector<int>(maxN + 1, 0));

    vector<vector<bool> > controls =
        vector<vector<bool> >(maxN + 1, vector<bool>(maxN + 1, false));

    for (int i = 0; i <= maxN; i++)
        controls[i][i] = true;

    for (int i = 0; i < N; i++)
        addOwn(controlPercentages[i].c1,
               controlPercentages[i].c2,
               controlPercentages[i].p,
               owns,
               controls);

    vector<pair<int, int> > result;

    for (int i = 0; i <= maxN; i++)
        for (int j = 0; j <= maxN; j++)
            if (i != j && controls[i][j])
                result.push_back(make_pair(i, j));

    return result;
}

int main() {
    ifstream fin("concom.in");
    ofstream fout("concom.out");

    int N;
    vector<ControlPercentage> controls;
    fin >> N;

    for (int i = 0; i < N; i++) {
        ControlPercentage cp;
        fin >> cp.c1 >> cp.c2 >> cp.p;
        controls.push_back(cp);
    }

    vector<pair<int, int> > companies = getControllingCompanies(controls);
    for (unsigned int i = 0; i < companies.size(); i++)
        fout << companies[i].first << " " << companies[i].second << endl;

    return 0;
}

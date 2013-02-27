/*
ID: joao.c.1
PROG: msquare
LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

vector<int> applyTransformationA(vector<int> input) {
    for (int i = 0; i < 4; i++) {
        swap(input[i], input[7 - i]);
    }

    return input;
}

vector<int> applyTransformationB(vector<int> input) {
    int t0 = input[3];
    int t1 = input[4];
    for (int i = 0; i < 4; i++) {
        int v0 = input[i];
        int v1 = input[7 - i];
        input[i] = t0;
        input[7 - i] = t1;
        t0 = v0;
        t1 = v1;
    }

    return input;
}

vector<int> applyTransformationC(vector<int> input) {
    int idx[] = {1, 2, 5, 6};
    int t = input[idx[3]];
    for (int i = 0; i < 4; i++) {
        int v = input[idx[i]];
        input[idx[i]] = t;
        t = v;
    }

    return input;
}

string getTransformationSequence(vector<int> start, vector<int> target) {
    set<vector<int> > visited;

    queue<pair<string, vector<int> > > q;
    q.push(make_pair("", start));

    while (!q.empty()) {
        pair<string, vector<int> > c = q.front(); q.pop();

        if (c.second == target)
            return c.first;

        if (visited.find(c.second) == visited.end()) {
            visited.insert(c.second);

            q.push(make_pair(c.first + "A", applyTransformationA(c.second)));
            q.push(make_pair(c.first + "B", applyTransformationB(c.second)));
            q.push(make_pair(c.first + "C", applyTransformationC(c.second)));
        }
    }

    return "";
}

int main() {
    ifstream fin("msquare.in");
    ofstream fout("msquare.out");

    vector<int> start;
    start.push_back(1);
    start.push_back(2);
    start.push_back(3);
    start.push_back(4);
    start.push_back(5);
    start.push_back(6);
    start.push_back(7);
    start.push_back(8);

    vector<int> target;
    for (int i = 0; i < 8; i++) {
        int n;
        fin >> n;
        target.push_back(n);
    }

    string sequence = getTransformationSequence(start, target);
    fout << sequence.size() << endl;

    while (sequence.size() > 60) {
        fout << sequence.substr(0, 60) << endl;
        sequence = sequence.substr(60);
    }
    fout << sequence << endl;

    return 0;
}

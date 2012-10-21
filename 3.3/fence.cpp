/*
ID: joao.c.1
PROG: fence
LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

void findCircuit(int N,
                 vector<int> & circuit,
                 vector<vector<int> > & neighbors) {
    if (neighbors[N].size() == 0)
        circuit.push_back(N);
    else {
        while (neighbors[N].size() > 0) {
            int j = neighbors[N][0];
            neighbors[N].erase(neighbors[N].begin());
            for (unsigned int i = 0; i < neighbors[j].size(); i++) {
                if (neighbors[j][i] == N) {
                    neighbors[j].erase(neighbors[j].begin() + i);
                    break;
                }
            }
            findCircuit(j, circuit, neighbors);
        }
        circuit.push_back(N);
    }
}

vector<int> getIntersections(vector<pair<int, int> > fences) {
    int N = 1;
    int F = fences.size();
    for (int f = 0; f < F; f++) {
        if (fences[f].first > N)
            N = fences[f].first;
        if (fences[f].second > N)
            N = fences[f].second;
    }

    vector<vector<int> > neighbors = vector<vector<int> >(N + 1, vector<int>());
    for (int f = 0; f < F; f++) {
        neighbors[fences[f].first].push_back(fences[f].second);
        neighbors[fences[f].second].push_back(fences[f].first);
    }

    for (int i = 0; i <= N; i++) {
        sort(neighbors[i].begin(), neighbors[i].end());
    }

    vector<int> circuit;
    for (int i = 1; i <= N; i++) {
        if (neighbors[i].size() != 0 && neighbors[i].size() % 2 != 0) {
            findCircuit(i, circuit, neighbors);
            break;
        }
    }

    if (circuit.size() == 0) {
        for (int i = 1; i <= N; i++) {
            if (neighbors[i].size() != 0) {
                findCircuit(i, circuit, neighbors);
                break;
            }
        }
    }

    reverse(circuit.begin(), circuit.end());

    return circuit;
}

int main() {
    ifstream fin("fence.in");
    ofstream fout("fence.out");

    int F;
    fin >> F;

    vector<pair<int, int> > fences;
    for (int f = 0; f < F; f++) {
        int i, j;
        fin >> i >> j;
        fences.push_back(make_pair(i, j));
    }

    vector<int> intersections = getIntersections(fences);
    for (unsigned int i = 0; i < intersections.size(); i++)
        fout << intersections[i] << endl;

    return 0;
}

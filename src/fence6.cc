/*
ID: joao.c.1
PROG: fence6
LANG: C++
*/

#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int getShortestPerimeterAux(int startingFence,
                            int previousFence,
                            int currentFence,
                            int currentPerimeter,
                            int bestPerimeter,
                            set<pair<int, int> > & visited,
                            const vector<int> & lengths,
                            const vector<pair<vector<int>, vector<int> > > & connections) {
    visited.insert(make_pair(previousFence, currentFence));
    if (previousFence != currentFence && currentFence == startingFence)
        return currentPerimeter;
    if (currentPerimeter >= bestPerimeter)
        return numeric_limits<int>::max();

    vector<int> next = find(connections[currentFence].first.begin(),
                            connections[currentFence].first.end(),
                            previousFence) == connections[currentFence].first.end() ?
        connections[currentFence].first : connections[currentFence].second;

    int best = bestPerimeter;

    for (unsigned int i = 0; i < next.size(); i++) {
        if (visited.find(make_pair(currentFence, next[i])) == visited.end()) {
            int p = getShortestPerimeterAux(startingFence,
                                            currentFence,
                                            next[i],
                                            currentPerimeter + lengths[next[i]],
                                            bestPerimeter,
                                            visited,
                                            lengths,
                                            connections);
            best = min(best, p);
        }
    }

    return best;
}

int getShortestPerimeter(const vector<int> & lengths,
                         const vector<pair<vector<int>, vector<int> > > & connections) {
    int best = numeric_limits<int>::max();
    int N = lengths.size();

    for (int i = 0; i < N; i++) {
        set<pair<int, int> > visited;
        int p = getShortestPerimeterAux(i, i, i, 0, best, visited, lengths, connections);
        if (p < best)
            best = p;
    }

    return best;
}

int main() {
    ifstream fin("fence6.in");
    ofstream fout("fence6.out");

    int N, s, L, N1, N2, cs;
    fin >> N;

    vector<int> lengths = vector<int>(N, 0);
    vector<pair<vector<int>, vector<int> > > connections =
        vector<pair<vector<int>, vector<int> > >(N, make_pair(vector<int>(),
                                                              vector<int>()));

    for (int i = 0; i < N; i++) {
        fin >> s >> L >> N1 >> N2;
        s--;

        lengths[s] = L;
        for (int j = 0; j < N1; j++) {
            fin >> cs;
            cs--;
            connections[s].first.push_back(cs);
        }

        for (int j = 0; j < N2; j++) {
            fin >> cs;
            cs--;
            connections[s].second.push_back(cs);
        }
    }

    fout << getShortestPerimeter(lengths, connections) << endl;

    return 0;
}

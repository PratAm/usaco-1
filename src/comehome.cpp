/*
ID: joao.c.1
PROG: comehome
LANG: C++
*/

#include <fstream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

pair<char, int> getClosestPasture(map<char, vector<pair<char, int> > > connections) {
    map<char, int> distances;
    map<pair<char, char>, int> bestConnections;

    for (map<char, vector<pair<char, int> > >::iterator itr = connections.begin();
         itr != connections.end();
         itr++) {
        vector<pair<char, int> > c = itr->second;
        for (unsigned int i = 0; i < c.size(); i++) {
            pair<char, char> connection = make_pair(itr->first, c[i].first);
            if (bestConnections.find(connection) == bestConnections.end() ||
                bestConnections[connection] > c[i].second) {
                bestConnections[connection] = c[i].second;
            }
        }
    }

    connections.clear();
    for (map<pair<char, char>, int>::iterator itr = bestConnections.begin();
         itr != bestConnections.end();
         itr++)
        connections[itr->first.first].push_back(make_pair(itr->first.second, itr->second));

    pair<int, char> start = make_pair(0, 'Z');
    priority_queue<pair<int, char> > pq;
    pq.push(start);

    while (!pq.empty()) {
        pair<int, char> current = pq.top(); pq.pop();

        if (distances.find(current.second) == distances.end() ||
            distances[current.second] >= current.first) {
            distances[current.second] = current.first;

            vector<pair<char, int> > c = connections[current.second];
            int N = c.size();
            for (int i = 0; i < N; i++) {
                pq.push(make_pair(distances[current.second] + c[i].second,
                                  c[i].first));
            }
        }
    }

    pair<char, int> closest = make_pair('Z', 0);

    for (map<char, int>::iterator itr = distances.begin();
         itr != distances.end();
         itr++) {
        if ((itr->first >= 'A' && itr->first < 'Z') &&
            (closest.first == 'Z' || itr->second < closest.second))
            closest = *itr;
    }

    return closest;
}

int main() {
    ifstream fin("comehome.in");
    ofstream fout("comehome.out");

    int P;
    fin >> P;

    map<char, vector<pair<char, int> > > connections;

    for (int i = 0; i < P; i++) {
        char p1, p2;
        int dist;
        fin >> p1 >> p2 >> dist;
        connections[p1].push_back(make_pair(p2, dist));
        connections[p2].push_back(make_pair(p1, dist));
    }

    pair<char, int> pasture = getClosestPasture(connections);

    fout << pasture.first << " " << pasture.second << endl;

    return 0;
}

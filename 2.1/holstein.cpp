/*
ID: joao.c.1
PROG: holstein
LANG: C++
*/

#include <fstream>
#include <vector>
#include <queue>

using namespace std;

bool meetsRequirements(const vector<int> & requirements,
                       const vector<int> & scoops,
                       const vector<vector<int> > & feeds) {
    int N = requirements.size();
    vector<int> current(N, 0);

    for (unsigned int i = 0; i < scoops.size(); i++) {
        for (unsigned int j = 0; j < feeds[scoops[i]].size(); j++) {
            current[j] += feeds[scoops[i]][j];
        }
    }

    for (int i = 0; i < N; i++) {
        if (current[i] < requirements[i])
            return false;
    }

    return true;
}

vector<int> getScoops(vector<int> requirements, vector<vector<int> > feeds) {
    int N = feeds.size();
    queue<vector<int> > q;
    vector<int> best;

    for (int i = 0; i < N; i++)
        q.push(vector<int>(1, i));

    while (!q.empty()) {
        vector<int> current = q.front(); q.pop();

        if (meetsRequirements(requirements, current, feeds) &&
            (best.size() == 0 || current.size() < best.size())) {
            best = current;
        }

        for (int i = current.back() + 1; i < N; i++) {
            vector<int> next = current;
            next.push_back(i);
            q.push(next);
        }
    }

    return best;
}

int main() {
    ifstream fin("holstein.in");
    ofstream fout("holstein.out");

    int V, G;
    vector<int> requirements;
    vector<vector<int> > feeds;

    fin >> V;
    for (int i = 0; i < V; i++) {
        int requirement;
        fin >> requirement;
        requirements.push_back(requirement);
    }

    fin >> G;
    for (int i = 0; i < G; i++) {
        vector<int> feed;
        for (int j = 0; j < V; j++) {
            int vitaminLevel;
            fin >> vitaminLevel;
            feed.push_back(vitaminLevel);
        }
        feeds.push_back(feed);
    }

    vector<int> scoops = getScoops(requirements, feeds);
    fout << scoops.size();
    for (unsigned int i = 0; i < scoops.size(); i++)
        fout << " " << (scoops[i] + 1);
    fout << endl;

    return 0;
}

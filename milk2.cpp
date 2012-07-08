/*
ID: joao.c.1
PROG: milk2
LANG: C++
*/

#include <fstream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

bool formattedTimeIntervalComparator(pair<int, int> t1, pair<int, int> t2) {
    return t1.first < t2.first ||
                      (t1.first == t2.first && t1.second > t2.second);
}

pair<int, int> getLongestTimes(vector<pair<int, int> > milkIntervals) {
    pair<int, int> best;
    best.first = 0;
    best.second = 0;

    vector<pair<int, int> > formattedIntervals;
    for (unsigned int i = 0; i < milkIntervals.size(); i++) {
        formattedIntervals.push_back(make_pair(milkIntervals[i].first, +1));
        formattedIntervals.push_back(make_pair(milkIntervals[i].second, -1));
    }
    sort(formattedIntervals.begin(), formattedIntervals.end(),
         formattedTimeIntervalComparator);
    int start = formattedIntervals[0].first;
    for (unsigned int i = 0; i < formattedIntervals.size(); i++)
        formattedIntervals[i].first -= start;

    int currentStart = 0;
    int currentCount = 0;
    for (unsigned int i = 0; i < formattedIntervals.size(); i++) {
        int nextInc = formattedIntervals[i].second;
        if (currentCount == 0 && nextInc == 1) {
            best.second = max(best.second,
                              (formattedIntervals[i].first - currentStart));
            currentStart = formattedIntervals[i].first;
        } else if (currentCount == 1 && nextInc == -1) {
            best.first = max(best.first,
                             (formattedIntervals[i].first - currentStart));
            currentStart = formattedIntervals[i].first;
        }

        currentCount += nextInc;
    }

    return best;
}

int main() {
    ifstream fin("milk2.in");
    ofstream fout("milk2.out");

    vector<pair<int, int> > milkIntervals;

    int N;
    fin >> N;
    for (int i = 0; i < N; i++) {
        pair<int, int> milkInterval;
        fin >> milkInterval.first >> milkInterval.second;
        milkIntervals.push_back(milkInterval);
    }

    pair<int, int> best = getLongestTimes(milkIntervals);
    fout << best.first << " " << best.second << endl;

    return 0;
}

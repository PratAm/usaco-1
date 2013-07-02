/*
ID: joao.c.1
PROG: ratios
LANG: C++
*/

#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

#define FEED_MAX 100

struct Ratio {
    int x, y, z;
};

int validMixture(Ratio mixture, Ratio goal) {
    int v = -1;

    if (mixture.x == 0 && mixture.y == 0 && mixture.z == 0)
        return -1;

    if ((goal.x != 0 && mixture.x % goal.x != 0) ||
        (goal.x == 0 && mixture.x != 0)) {
        return -1;
    } else if (goal.x != 0) {
        v = mixture.x / goal.x;
    }

    if ((goal.y != 0 && mixture.y % goal.y != 0) ||
        (goal.y == 0 && mixture.y != 0)) {
        return -1;
    } else if (goal.y != 0) {
        if (v != -1 && mixture.y / goal.y != v)
            return -1;
        v = mixture.y / goal.y;
    }

    if ((goal.z != 0 && mixture.z % goal.z != 0) ||
        (goal.z == 0 && mixture.z != 0)) {
        return -1;
    } else if (goal.z != 0) {
        if (v != -1 && mixture.z / goal.z != v)
            return -1;
        v = mixture.z / goal.z;
    }

    return v;
}

vector<int> getUnitsForGoalRatio(vector<Ratio> mixtures, Ratio goal) {
    vector<int> best;

    for (int i = 0; i < FEED_MAX; i++) {
        for (int j = 0; j < FEED_MAX; j++) {
            for (int k = 0; k < FEED_MAX; k++) {
                Ratio mixture;
                mixture.x =
                    i * mixtures[0].x +
                    j * mixtures[1].x +
                    k * mixtures[2].x;
                mixture.y =
                    i * mixtures[0].y +
                    j * mixtures[1].y +
                    k * mixtures[2].y;
                mixture.z =
                    i * mixtures[0].z +
                    j * mixtures[1].z +
                    k * mixtures[2].z;
                int m = validMixture(mixture, goal);
                if (m != -1 &&
                    (best.size() == 0 ||
                     i + j + k < best[0] + best[1] + best[2])) {
                    best = vector<int>(4, 0);
                    best[0] = i;
                    best[1] = j;
                    best[2] = k;
                    best[3] = m;
                }
            }
        }
    }

    return best;
}

int main() {
    ifstream fin("ratios.in");
    ofstream fout("ratios.out");

    Ratio goal;
    fin >> goal.x >> goal.y >> goal.z;

    vector<Ratio> mixtures;
    for (int i = 0; i < 3; i++) {
        Ratio mixture;
        fin >> mixture.x >> mixture.y >> mixture.z;
        mixtures.push_back(mixture);
    }

    vector<int> units = getUnitsForGoalRatio(mixtures, goal);

    if (units.size() == 0)
        fout << "NONE" << endl;
    else
        fout << units[0] << " "
             << units[1] << " "
             << units[2] << " "
             << units[3] << endl;

    return 0;
}

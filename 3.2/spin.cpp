/*
ID: joao.c.1
PROG: spin
LANG: C++
*/

#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

struct Wheel {
    int rotationSpeed;
    vector<pair<int, int> > wedges;
};

void rotate(vector<Wheel> & wheels) {
    int N = wheels.size();
    for (int i = 0; i < N; i++) {
        int W = wheels[i].wedges.size();
        for (int j = 0; j < W; j++) {
            wheels[i].wedges[j].first =
                (wheels[i].wedges[j].first + wheels[i].rotationSpeed) % 360;
        }
    }
}

bool aligned(vector<Wheel> wheels) {
    static int spaces[360];

    int N = wheels.size();

    memset(spaces, 0, sizeof(spaces));

    for (int i = 0; i < N; i++) {
        int W = wheels[i].wedges.size();
        for (int j = 0; j < W; j++) {
            pair<int, int> wedge = wheels[i].wedges[j];
            for (int k = wedge.first; k <= wedge.first + wedge.second; k++) {
                spaces[k % 360] += 1 << i;
            }
        }
    }

    for (int i = 0; i < 360; i++)
        if (spaces[i] == (1 << N) - 1)
            return true;

    return false;
}

int getTimeWhenWedgesAlign(vector<Wheel> wheels) {
    int n = 0;

    while (!aligned(wheels) && n <= 360) {
        rotate(wheels);
        n++;
    }

    return n >= 360 ? -1 : n;
}

int main() {
    ifstream fin("spin.in");
    ofstream fout("spin.out");

    int N = 5;
    vector<Wheel> wheels;
    for (int i = 0; i < N; i++) {
        Wheel w;
        fin >> w.rotationSpeed;
        int wedges;
        fin >> wedges;
        for (int j = 0; j < wedges; j++) {
            int start, extent;
            fin >> start >> extent;
            w.wedges.push_back(make_pair(start, extent));
        }
        wheels.push_back(w);
    }

    int t = getTimeWhenWedgesAlign(wheels);
    if (t < 0)
        fout << "none" << endl;
    else
        fout << t << endl;

    return 0;
}

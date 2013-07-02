/*
ID: joao.c.1
PROG: fence4
LANG: C++
*/

#include <fstream>

using namespace std;

#define EPS 0.00001
#define MAXN 201
#define INF 1e10

int N;
int corners[MAXN][2];
int observer[2];
bool visible[MAXN];

int side(double sx, double sy, double ex, double ey, int p) {
    double dx, dy;
    double px, py;
    double t;

    dx = ex - sx;
    dy = ey - sy;

    px = corners[p][0] - sx;
    py = corners[p][1] - sy;

    t = dx * py - dy * px;

    if (t > EPS)
        return 0;
    if (t < -EPS)
        return 1;
    return 2;
}

bool segmentsIntersect(int s1, int s2) {
    double sx, sy;
    double ex, ey;

    sx = corners[s1][0];
    sy = corners[s1][1];
    ex = corners[s1 + 1][0];
    ey = corners[s1 + 1][1];

    if (side(sx, sy, ex, ey, s2) == side(sx, sy, ex, ey, s2 + 1))
        return false;

    sx = corners[s2][0];
    sy = corners[s2][1];
    ex = corners[s2 + 1][0];
    ey = corners[s2 + 1][1];

    if (side(sx, sy, ex, ey, s1) == side(sx, sy, ex, ey, s1 + 1))
        return false;

    return true;
}

bool validFence() {
    for (int i = 0; i < N; i++) {
        for (int j = i + 2; j < N; j++) {
            if (i == 0 && j == N - 1)
                continue;
            if (segmentsIntersect(i, j))
                return false;
        }
    }

    return true;
}

int firstIntersection(double sx, double sy, double ex, double ey) {
    double min, leftBrush, rightBrush;
    int best = N;

    min = leftBrush = rightBrush = INF;

    for (int i = 0; i < N; i++) {
        double ax = corners[i][0];
        double ay = corners[i][1];
        double bx = corners[i + 1][0];
        double by = corners[i + 1][1];

        double t = (ex - sx) * (ay - by) - (ey - sy) * (ax - bx);
        if (t > -EPS && t < EPS)
            continue;

        double cnst = (ax - sx) * (by - ay) - (ay - sy) * (bx - ax);
        double coeff = (ex - sx) * (by - ay) - (ey - sy) * (bx - ax);
        if (coeff > -EPS && coeff < EPS) {
            if (bx - ax > -EPS && bx - ax < EPS) {
                cnst = ax - sx;
                coeff = ex - sx;
            } else {
                cnst = ay - sy;
                coeff = ey - sy;
            }
        }
        double j = cnst / coeff;

        if (j < -EPS)
            continue;

        cnst = sx + (ex - sx) * j - ax;
        coeff = bx - ax;
        if (coeff > -EPS && coeff < EPS) {
            cnst = sy + (ey - sy) * j - ay;
            coeff = by - ay;
        }
        double k = cnst / coeff;

        if (k < -EPS || k > (1.0 + EPS))
            continue;

        double x = ax + (bx - ax) * k;
        double y = ay + (by - ay) * k;

        t = (x - sx) * (ex - sx) + (y - sy) * (ey - sy);

        if (t < -EPS || t > min)
            continue;

        if (k < EPS || k > (1 - EPS)) {
            int t1, t2;

            if (k < EPS) {
                t1 = i - 1;
                if (t1 < 0)
                    t1 += N;
                t2 = i + 1;
            } else {
                t1 = i;
                t2 = i + 2;
                if (t2 >= N)
                    t2 -= N;
            }

            int s1 = side(sx, sy, ex, ey, t1);
            int s2 = side(sx, sy, ex, ey, t2);
            if (s1 == s2) {
                if (s1 == 0 && t < leftBrush)
                    leftBrush = t;
                if (s1 == 1 && t < rightBrush)
                    rightBrush = t;
                continue;
            }
        }

        min = t;
        best = i;
    }

    if (min > leftBrush && min > rightBrush)
        return N;

    return best;
}

void calculateVisiblePoints() {
    for (int i = 0; i < N; i++) {
        visible[firstIntersection(observer[0],
                                  observer[1],
                                  corners[i][0],
                                  corners[i][1])] = true;

        visible[firstIntersection(observer[0],
                                  observer[1],
                                  (corners[i][0] + corners[i + 1][0]) * 0.5,
                                  (corners[i][1] + corners[i + 1][1]) * 0.5)] = true;
    }
}

int main() {
    ifstream fin("fence4.in");
    ofstream fout("fence4.out");

    fin >> N;
    fin >> observer[0] >> observer[1];
    for (int i = 0; i < N; i++) {
        fin >> corners[i][0] >> corners[i][1];
    }
    corners[N][0] = corners[0][0];
    corners[N][1] = corners[0][1];

    if (!validFence())
        fout << "NOFENCE" << endl;
    else {
        calculateVisiblePoints();

        int total = 0;
        for (int i = 0; i < N; i++)
            if (visible[i])
                total++;

        fout << total << endl;

        for (int i = 0; i < N - 2; i++)
            if (visible[i])
                fout << corners[i][0] << " " << corners[i][1] << " "
                     << corners[i + 1][0] << " " << corners[i + 1][1] << endl;

        if (visible[N - 1])
            fout << corners[0][0] << " " << corners[0][1] << " "
                 << corners[N - 1][0] << " " << corners[N - 1][1] << endl;
        if (visible[N - 2])
            fout << corners[N - 2][0] << " " << corners[N - 2][1] << " "
                 << corners[N - 1][0] << " " << corners[N - 1][1] << endl;
    }

    return 0;
}

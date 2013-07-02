/*
ID: joao.c.1
PROG: friday
LANG: C++
*/

#include <fstream>
#include <iostream>

using namespace std;

#define SATURDAY 0
#define SUNDAY 1
#define MONDAY 2
#define TUESDAY 3
#define WEDNESDAY 4
#define THURSDAY 5
#define FRIDAY 6

int DAYS_IN_MONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isLeapYear(int year) {
    if (year % 100 == 0)
        return year % 400 == 0;
    return year % 4 == 0;
}

int daysBetween(int d1, int m1, int y1, int d2, int m2, int y2) {
    int dayCount = 0;
    if (y2 != y1 || m2 != m1) {
        int dm = DAYS_IN_MONTH[m1];
        if (isLeapYear(y1) && m1 == 1)
            dm++;
        dayCount += ((dm - d1) + 1);
        int nm = m1 + 1;
        int ny = y1;
        if (nm >= 12) {
            nm = 0;
            ny++;
        }
        dayCount += daysBetween(1, nm, ny, d2, m2, y2);
    }
    return dayCount + (d2 - d1);
}

int main() {
    ifstream fin("friday.in");
    ofstream fout("friday.out");

    int N;
    fin >> N;

    int counts[7] = {0, 0, 0, 0, 0, 0, 0};
    int cm = 0;
    int cy = 1900;
    int cwd = (MONDAY + daysBetween(1, 0, 1900, 13, 0, 1900)) % 7;

    while (cy <= 1900 + N - 1) {
        counts[cwd]++;
        int nm = cm + 1;
        int ny = cy;
        if (nm >= 12) {
            nm = 0;
            ny++;
        }
        cwd = (cwd + daysBetween(13, cm, cy, 13, nm, ny)) % 7;
        cm = nm;
        cy = ny;
    }

    for (int i = 0; i < 7; i++) {
        fout << counts[i];
        if (i + 1 < 7)
            fout << " ";
        else
            fout << endl;
    }
}

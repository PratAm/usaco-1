/*
ID: joao.c.1
PROG: checker
LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

#define MAXROWS 13

struct Solution {
    int size;
    int rows[MAXROWS];
};

struct Globals {
    bool availableColumn[MAXROWS + 1];
    bool availableLeftDiagonal[2 * (MAXROWS + 1)];
    bool availableRightDiagonal[2 * (MAXROWS + 1)];
};

struct SolutionCompare {
    bool operator()(const Solution & s1, const Solution & s2) const {
        int N = min(s1.size, s2.size);
        for (int i = 0; i < N; i++) {
            if (s1.rows[i] > s2.rows[i]) {
                return false;
            } else if (s1.rows[i] < s2.rows[i]) {
                return true;
            }
        }
        return false;
    }
};

bool canPlace(const Solution * solution, int v, int N, const Globals * g) {
    int row = solution->size + 1;

    return g->availableColumn[v] &&
           g->availableLeftDiagonal[(row - v) + N] &&
           g->availableRightDiagonal[row + v];
}

Solution mirrorHorizontal(const Solution * solution) {
    int N = solution->size;
    Solution res;
    res.size = solution->size;
    for (int i = 0; i < N; i++) {
        res.rows[i] = N - solution->rows[i] + 1;
    }
    return res;
}

Solution mirrorVertical(const Solution * solution) {
    int N = solution->size;
    Solution res;
    res.size = solution->size;
    for (int i = N - 1; i >= 0; i--) {
        res.rows[N - 1 - i] = solution->rows[i];
    }
    return res;
}

vector<Solution> getSolutions(int N, Solution * current, Globals * g) {
    vector<Solution> solutions;

    if (current->size == N) {
        Solution s;
        s.size = current->size;
        for (int i = 0; i < current->size; i++)
            s.rows[i] = current->rows[i];
        solutions.push_back(s);
    } else {
        int max = N;
        if (current->size == 0)
            max = N / 2;

        for (int i = 1; i <= max; i++) {
            if (canPlace(current, i, N, g)) {
                g->availableColumn[i] = false;
                g->availableLeftDiagonal[(current->size + 1 - i) + N] = false;
                g->availableRightDiagonal[current->size + 1 + i] = false;
                current->rows[current->size++] = i;

                vector<Solution> nextSolutions = getSolutions(N, current, g);
                for (unsigned int j = 0; j < nextSolutions.size(); j++) {
                    solutions.push_back(nextSolutions[j]);
                }

                current->size--;
                g->availableColumn[i] = true;
                g->availableLeftDiagonal[(current->size + 1 - i) + N] = true;
                g->availableRightDiagonal[current->size + 1 + i] = true;
            }
        }
    }

    return solutions;
}

set<Solution, SolutionCompare> getSolutions(int N) {
    Solution * start = new Solution;
    start->size = 0;

    Globals * g = new Globals;
    int G = 2 * (MAXROWS + 1);
    for (int i = 0; i < G; i++) {
        g->availableLeftDiagonal[i] = true;
        g->availableRightDiagonal[i] = true;
        if (i <= MAXROWS)
            g->availableColumn[i] = true;
    }

    vector<Solution> tempSolutions = getSolutions(N, start, g);
    set<Solution, SolutionCompare> solutionSet;
    vector<Solution> finalSolutions;

    for (unsigned int i = 0; i < tempSolutions.size(); i++) {
        Solution o = tempSolutions[i];
        Solution mh = mirrorHorizontal(&o);
        Solution mv = mirrorVertical(&o);
        Solution mvh = mirrorVertical(&mh);

        solutionSet.insert(o);
        solutionSet.insert(mh);
        solutionSet.insert(mv);
        solutionSet.insert(mvh);
    }

    return solutionSet;
}

int main() {
    ifstream fin("checker.in");
    ofstream fout("checker.out");

    int N;
    fin >> N;

    set<Solution, SolutionCompare> solutions = getSolutions(N);

    int i = 0;
    set<Solution, SolutionCompare>::iterator itr = solutions.begin();
    while (i < 3) {
        Solution s = *itr;

        for (int j = 0; j < s.size; j++) {
            fout << s.rows[j];
            if (j + 1 < s.size)
                fout << " ";
            else
                fout << endl;
        }

        itr++;
        i++;
    }
    fout << solutions.size() << endl;

    return 0;
}

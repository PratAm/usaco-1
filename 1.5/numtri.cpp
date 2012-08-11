/*
ID: joao.c.1
PROG: numtri
LANG: C++
*/

#include <fstream>
#include <vector>

using namespace std;

int getLargestSum(vector<vector<int> > triangle) {
    int R = triangle.size();
    int C = triangle.back().size();
    int L = 0;

    vector<vector<int> > highestSum = vector<vector<int> >(R, vector<int>(C, 0));

    highestSum[0][0] = triangle[0][0];
    for (int i = 1; i < R; i++) {
        for (int j = 0; j <= i; j++) {
            highestSum[i][j] = highestSum[i - 1][j] + triangle[i][j];
            if (j > 0 && highestSum[i - 1][j - 1] + triangle[i][j] > highestSum[i][j])
                highestSum[i][j] = highestSum[i - 1][j - 1] + triangle[i][j];
            if (highestSum[i][j] > L)
                L = highestSum[i][j];
        }
    }

    return L;
}

int main() {
    ifstream fin("numtri.in");
    ofstream fout("numtri.out");

    int R;
    fin >> R;

    vector<vector<int> > triangle;
    for (int i = 0; i < R; i++) {
        vector<int> row;
        for (int j = 0; j <= i; j++) {
            int t;
            fin >> t;
            row.push_back(t);
        }
        triangle.push_back(row);
    }

    fout << getLargestSum(triangle) << endl;

    return 0;
}

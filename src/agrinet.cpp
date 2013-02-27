/*
ID: joao.c.1
PROG: agrinet
LANG: C++
*/

#include <fstream>
#include <vector>

using namespace std;

int getMinimumLengthOfFiber(vector<vector<int> > connectivityMatrix) {
    int N = connectivityMatrix.size();

    int treeSize = 0;
    int treeLength = 0;
    vector<bool> inTree = vector<bool>(N, false);
    vector<int> distance = vector<int>(N, 0);

    treeSize = 1;
    inTree[0] = true;
    for (int i = 1; i < N; i++)
        distance[i] = connectivityMatrix[0][i];

    while (treeSize != N) {
        int next = -1;

        for (int i = 0; i < N; i++) {
            if (!inTree[i] && (next == -1 || distance[i] < distance[next]))
                next = i;
        }

        inTree[next] = true;
        treeSize++;
        treeLength += distance[next];

        for (int i = 0; i < N; i++) {
            if (connectivityMatrix[next][i] < distance[i])
                distance[i] = connectivityMatrix[next][i];
        }
    }

    return treeLength;
}

int main() {
    ifstream fin("agrinet.in");
    ofstream fout("agrinet.out");

    int N;
    fin >> N;
    vector<vector<int> > connectivityMatrix =
        vector<vector<int> >(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int d;
            fin >> d;
            connectivityMatrix[i][j] = d;
        }
    }

    fout << getMinimumLengthOfFiber(connectivityMatrix) << endl;

    return 0;
}

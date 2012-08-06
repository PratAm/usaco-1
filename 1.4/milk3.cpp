/*
ID: joao.c.1
PROG: milk3
LANG: C++
*/

#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

struct BucketSet {
    int A;
    int B;
    int C;
};

vector<int> getPossibleAmountsOfMilk(int A, int B, int C) {
    bool visited[21][21][21];
    memset(visited, false, sizeof(visited));

    set<int> amounts;
    BucketSet bs;
    bs.A = 0; bs.B = 0; bs.C = C;

    queue<BucketSet> q;
    q.push(bs);

    while (!q.empty()) {
        BucketSet current = q.front(); q.pop();
        visited[current.A][current.B][current.C] = true;

        if (current.A == 0)
            amounts.insert(current.C);

        BucketSet AtoB = current;
        AtoB.A = current.A - min(B - current.B, current.A);
        AtoB.B = current.B + min(B - current.B, current.A);
        if (!visited[AtoB.A][AtoB.B][AtoB.C])
            q.push(AtoB);

        BucketSet AtoC = current;
        AtoC.A = current.A - min(C - current.C, current.A);
        AtoC.C = current.C + min(C - current.C, current.A);
        if (!visited[AtoC.A][AtoC.B][AtoC.C])
            q.push(AtoC);

        BucketSet BtoA = current;
        BtoA.B = current.B - min(A - current.A, current.B);
        BtoA.A = current.A + min(A - current.A, current.B);
        if (!visited[BtoA.A][BtoA.B][BtoA.C])
            q.push(BtoA);

        BucketSet BtoC = current;
        BtoC.B = current.B - min(C - current.C, current.B);
        BtoC.C = current.C + min(C - current.C, current.B);
        if (!visited[BtoC.A][BtoC.B][BtoC.C])
            q.push(BtoC);

        BucketSet CtoA = current;
        CtoA.C = current.C - min(A - current.A, current.C);
        CtoA.A = current.A + min(A - current.A, current.C);
        if (!visited[CtoA.A][CtoA.B][CtoA.C])
            q.push(CtoA);

        BucketSet CtoB = current;
        CtoB.C = current.C - min(B - current.B, current.C);
        CtoB.B = current.B + min(B - current.B, current.C);
        if (!visited[CtoB.A][CtoB.B][CtoB.C])
            q.push(CtoB);
    }

    vector<int> amountsVector;
    for (set<int>::iterator itr = amounts.begin(); itr != amounts.end(); itr++)
        amountsVector.push_back(*itr);

    return amountsVector;
}

int main() {
    ifstream fin("milk3.in");
    ofstream fout("milk3.out");

    int A, B, C;
    fin >> A >> B >> C;

    vector<int> amounts = getPossibleAmountsOfMilk(A, B, C);
    for (unsigned int i = 0; i < amounts.size(); i++) {
        fout << amounts[i];
        if (i + 1 < amounts.size())
            fout << " ";
        else
            fout << endl;
    }

    return 0;
}

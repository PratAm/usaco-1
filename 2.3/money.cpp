/*
ID: joao.c.1
PROG: money
LANG: C++
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

long long getWaysToConstructAmount(int N, vector<int> coins) {
    sort(coins.begin(), coins.end());
    int C = coins.size();

    vector<vector<long long> > money =
        vector<vector<long long> >(N + 1, vector<long long>(coins.size(), 0));

    for (int i = 0; i < C; i++)
        money[0][i] = 1;

    for (int i = 0; i < C; i++) {
        if (i > 0)
            for (int j = 0; j <= N; j++)
                money[j][i] = money[j][i - 1];

        for (int j = coins[i]; j <= N; j++)
            money[j][i] += money[j - coins[i]][i];
    }

    return money[N][coins.size() - 1];
}

int main() {
    ifstream fin("money.in");
    ofstream fout("money.out");

    int V, N;
    vector<int> coins;
    fin >> V >> N;

    for (int i = 0; i < V; i++) {
        int temp;
        fin >> temp;
        coins.push_back(temp);
    }

    fout << getWaysToConstructAmount(N, coins) << endl;

    return 0;
}

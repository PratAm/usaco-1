/*
ID: joao.c.1
PROG: humble
LANG: C++
*/

#include <fstream>
#include <set>
#include <vector>

using namespace std;

int getNthHumbleNumber(int N, vector<int> numbers) {
    int F = numbers.size();
    set<int> generated;

    for (int i = 0; i < F; i++)
        generated.insert(numbers[i]);

    int target = 0;
    int s = 0;
    int g = generated.size();
    int largest = numbers.back();

    set<int>::iterator itr = generated.begin();

    while (s < N) {
        int current = *generated.begin();
        generated.erase(generated.begin());
        g = generated.size();

        target = current;

        for (int i = 0; i < F; i++) {
            int next = current * numbers[i];
            if (next / numbers[i] == current &&
                next > target &&
                (g < N || next < largest)) {
                if (next > largest)
                    largest = next;
                generated.insert(next);
            }
        }

        s++;
    }

    return target;
}

int main() {
    ifstream fin("humble.in");
    ofstream fout("humble.out");

    int K, N;
    vector<int> factors;
    fin >> K >> N;

    for (int i = 0; i < K; i++) {
        int f;
        fin >> f;
        factors.push_back(f);
    }

    fout << getNthHumbleNumber(N, factors) << endl;

    return 0;
}

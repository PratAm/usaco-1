/*
ID: joao.c.1
PROG: zerosum
LANG: C++
*/

#include <fstream>
#include <set>
#include <string>

using namespace std;

bool zeroSumSequence(string sequence) {
    int sum = 0;
    int temp = 0;
    char op = '+';

    for (unsigned int i = 0; i <= sequence.size(); i++) {
        if (i % 2 == 0) {
            temp = temp * 10 + (sequence[i] - '0');
        } else if (i == sequence.size() || sequence[i] != ' ') {
            if (op == '+') {
                sum += temp;
                temp = 0;
            } else if (op == '-') {
                sum -= temp;
                temp = 0;
            }
            if (i < sequence.size() && sequence[i] != ' ')
                op = sequence[i];
        }
    }

    return sum == 0;
}

set<string> getZeroSumSequences(int N, int C = 0, set<string> current = set<string>()) {
    set<string> result;

    if (N == C) {
        for (set<string>::iterator itr = current.begin();
             itr != current.end();
             itr++) {
            if (zeroSumSequence(*itr))
                result.insert(*itr);
        }
    } else {
        int V = C + 1;
        int nops = 3;
        char ops[] = {'+', '-', ' '};

        set<string> next;

        if (C == 0) {
            next.insert("1");
        } else {
            for (set<string>::iterator itr = current.begin();
                 itr != current.end();
                 itr++) {
                for (int i = 0; i < nops; i++)
                    next.insert(*itr + ops[i] + (char) (V + '0'));
            }
        }

        result = getZeroSumSequences(N, C + 1, next);
    }

    return result;
}

int main() {
    ifstream fin("zerosum.in");
    ofstream fout("zerosum.out");

    int N;
    fin >> N;

    set<string> sequences = getZeroSumSequences(N);

    for (set<string>::iterator itr = sequences.begin();
         itr != sequences.end();
         itr++) {
        fout << *itr << endl;
    }

    return 0;
}

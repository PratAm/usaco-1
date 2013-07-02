/*
ID: joao.c.1
PROG: sort3
LANG: C++
*/

#include <fstream>
#include <vector>
#include <map>

using namespace std;

int getMinimalNumberOfExchanges(vector<int> sequence) {
    vector<int> sortedSequence;
    map<int, int> elementCount;
    int N = sequence.size();

    for (int i = 0; i < N; i++) {
        if (elementCount.find(sequence[i]) == elementCount.end())
            elementCount[sequence[i]] = 0;
        elementCount[sequence[i]]++;
    }

    for (map<int, int>::iterator itr = elementCount.begin();
         itr != elementCount.end();
         itr++) {
        int element = itr->first;
        int count = itr->second;
        for (int i = 0; i < count; i++)
            sortedSequence.push_back(element);
    }

    int exchanges = 0;

    for (int i = 0; i < N; i++)
        if (sequence[i] != sortedSequence[i])
            for (int j = i + 1; j < N; j++)
                if (sequence[j] != sortedSequence[j] &&
                    sequence[i] == sortedSequence[j] &&
                    sequence[j] == sortedSequence[i]) {
                    int temp = sequence[j];
                    sequence[j] = sequence[i];
                    sequence[i] = temp;
                    exchanges++;
                    break;
                }

    int notSorted = 0;
    for (int i = 0; i < N; i++)
        if (sequence[i] != sortedSequence[i])
            notSorted++;
    exchanges += (notSorted / 3) * 2;

    return exchanges;
}

int main() {
    ifstream fin("sort3.in");
    ofstream fout("sort3.out");

    int N;
    vector<int> sequence;
    fin >> N;
    for (int i = 0; i < N; i++) {
        int temp;
        fin >> temp;
        sequence.push_back(temp);
    }

    fout << getMinimalNumberOfExchanges(sequence) << endl;

    return 0;
}

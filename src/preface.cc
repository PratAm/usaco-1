/*
ID: joao.c.1
PROG: preface
LANG: C++
*/

#include <fstream>
#include <map>
#include <string>

using namespace std;

string convertToRomanNumeral(int N) {
    static map<int, string> numerals;
    if (numerals.size() == 0) {
        numerals[1] = "I"; numerals[2] = "II"; numerals[3] = "III";
        numerals[4] = "IV"; numerals[5] = "V"; numerals[6] = "VI";
        numerals[7] = "VII"; numerals[8] = "VIII"; numerals[9] = "IX";

        numerals[10] = "X"; numerals[20] = "XX"; numerals[30] = "XXX";
        numerals[40] = "XL"; numerals[50] = "L"; numerals[60] = "LX";
        numerals[70] = "LXX"; numerals[80] = "LXXX"; numerals[90] = "XC";

        numerals[100] = "C"; numerals[200] = "CC"; numerals[300] = "CCC";
        numerals[400] = "CD"; numerals[500] = "D"; numerals[600] = "DC";
        numerals[700] = "DCC"; numerals[800] = "DCCC"; numerals[900] = "CM";

        numerals[1000] = "M"; numerals[2000] = "MM"; numerals[3000] = "MMM";
    }

    int s = 1;
    string res = "";
    while (N) {
        res = numerals[(N % 10) * s] + res;
        N /= 10;
        s *= 10;
    }

    return res;
}

map<char, int> getLetters(int N) {
    map<char, int> count;

    for (int i = 1; i <= N; i++) {
        string roman = convertToRomanNumeral(i);
        for (unsigned int j = 0; j < roman.size(); j++) {
            if (count.find(roman[j]) == count.end())
                count[roman[j]] = 0;
            count[roman[j]]++;
        }
    }

    return count;
}

int main() {
    ifstream fin("preface.in");
    ofstream fout("preface.out");

    int N;
    fin >> N;
    map<char, int> charCount = getLetters(N);

    char numerals[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    for (int i = 0; i < 7; i++) {
        if (charCount.find(numerals[i]) != charCount.end())
            fout << numerals[i] << " " << charCount[numerals[i]] << endl;
    }

    return 0;
}

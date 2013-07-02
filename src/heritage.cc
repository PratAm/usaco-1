/*
ID: joao.c.1
PROG: heritage
LANG: C++
*/

#include <fstream>
#include <string>

using namespace std;

string postOrder(string inOrder, string preOrder) {
    int N = inOrder.size();
    if (N == 0 || N == 1)
        return inOrder;

    char root = preOrder[0];
    int rootPos = inOrder.find(root);
    string leftInOrder = inOrder.substr(0, rootPos);
    string leftPreOrder = preOrder.substr(1, leftInOrder.size());
    string rightInOrder = inOrder.substr(rootPos + 1);
    string rightPreOrder = preOrder.substr(1 + leftInOrder.size());

    return postOrder(leftInOrder, leftPreOrder) +
        postOrder(rightInOrder, rightPreOrder) +
        root;
}

int main() {
    ifstream fin("heritage.in");
    ofstream fout("heritage.out");

    string inOrder, preOrder;
    fin >> inOrder >> preOrder;

    fout << postOrder(inOrder, preOrder) << endl;

    return 0;
}

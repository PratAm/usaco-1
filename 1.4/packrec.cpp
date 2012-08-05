/*
ID: joao.c.1
PROG: packrec
LANG: C++
*/

#include <fstream>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

pair<int, int> layout1(vector<pair<int, int> > rectangles) {
    int width = 0;
    int height = 0;

    for (unsigned int i = 0; i < rectangles.size(); i++) {
        width += rectangles[i].first;
        if (rectangles[i].second > height)
            height = rectangles[i].second;
    }

    return make_pair(min(width, height), max(width, height));
}

pair<int, int> layout2(vector<pair<int, int> > rectangles) {
    int width = rectangles[0].second;
    int height = 0;

    int topWidth = 0;

    for (unsigned int i = 1; i < rectangles.size(); i++) {
        topWidth += rectangles[i].first;
        if (rectangles[i].second + rectangles[0].first > height)
            height = rectangles[i].second + rectangles[0].first;
    }

    if (topWidth > width)
        width = topWidth;

    return make_pair(min(width, height), max(width, height));
}

pair<int, int> layout3(vector<pair<int, int> > rectangles) {
    int width = rectangles[0].second + rectangles[1].first;
    int height = rectangles[1].second;

    int topWidth = rectangles[1].first;

    for (unsigned int i = 2; i < rectangles.size(); i++) {
        topWidth += rectangles[i].first;
        if (rectangles[i].second + rectangles[0].first > height)
            height = rectangles[i].second + rectangles[0].first;
    }

    if (topWidth > width)
        width = topWidth;

    return make_pair(min(width, height), max(width, height));
}

pair<int, int> layout4(vector<pair<int, int> > rectangles) {
    int width = max(rectangles[0].first, rectangles[1].first) +
        rectangles[2].first + rectangles[3].first;
    int height = rectangles[0].second + rectangles[1].second;

    for (unsigned int i = 2; i < rectangles.size(); i++) {
        if (rectangles[i].second > height)
            height = rectangles[i].second;
    }

    return make_pair(min(width, height), max(width, height));
}

pair<int, int> layout5(vector<pair<int, int> > rectangles) {
    int width = max(rectangles[0].first, rectangles[1].second) +
        rectangles[2].first + rectangles[3].first;
    int height = rectangles[0].second + rectangles[1].first;

    for (unsigned int i = 2; i < rectangles.size(); i++) {
        if (rectangles[i].second > height)
            height = rectangles[i].second;
    }

    return make_pair(min(width, height), max(width, height));
}

pair<int, int> layout6(vector<pair<int, int> > rectangles) {
    int width = max(rectangles[0].first + rectangles[1].first,
                    max(rectangles[2].first + rectangles[3].second,
                        rectangles[2].first + rectangles[1].first));
    int height = max(rectangles[0].second + rectangles[2].second,
                     max(rectangles[1].second + rectangles[3].first,
                         rectangles[0].second + rectangles[3].first));

    return make_pair(min(width, height), max(width, height));
}

int area(pair<int, int> rectangle) {
    return rectangle.first * rectangle.second;
}

set<pair<int, int> > getBestEnclosingRectangles(vector<pair<int, int> > rectangles,
                                                vector<pair<int, int> > solution = vector<pair<int, int> >()) {
    set<pair<int, int> > finalSolution;

    if (solution.size() == 4) {
        vector<pair<int, int> > sols;
        sols.push_back(layout1(solution));
        sols.push_back(layout2(solution));
        sols.push_back(layout3(solution));
        sols.push_back(layout4(solution));
        sols.push_back(layout5(solution));
        sols.push_back(layout6(solution));

        finalSolution.insert(sols[0]);
        for (unsigned int i = 1; i < sols.size(); i++) {
            pair<int, int> current = *finalSolution.begin();
            if (area(sols[i]) == area(current)) {
                finalSolution.insert(sols[i]);
            } else if (area(sols[i]) < area(current)) {
                finalSolution.clear();
                finalSolution.insert(sols[i]);
            }
        }
    } else {
        for (unsigned int i = 0; i < rectangles.size(); i++) {
            for (unsigned int j = 0; j < 2; j++) {
                vector<pair<int, int> > nextSolution = solution;
                bool swap = j % 2 != 0;
                if (swap)
                    nextSolution.push_back(rectangles[i]);
                else
                    nextSolution.push_back(make_pair(rectangles[i].second,
                                                     rectangles[i].first));

                vector<pair<int, int> > nextRectangles = rectangles;
                nextRectangles.erase(nextRectangles.begin() + i);

                set<pair<int, int> > isolution =
                    getBestEnclosingRectangles(nextRectangles, nextSolution);

                if (finalSolution.size() == 0)
                    finalSolution = isolution;
                else if (isolution.size() > 0) {
                    if (area(*isolution.begin()) == area(*finalSolution.begin())) {
                        for (set<pair<int, int> >::iterator itr = isolution.begin();
                             itr != isolution.end();
                             itr++) {
                            finalSolution.insert(*itr);
                        }
                    } else if (area(*isolution.begin()) < area(*finalSolution.begin())) {
                        finalSolution = isolution;
                    }
                }
            }
        }
    }

    return finalSolution;
}

int main() {
    ifstream fin("packrec.in");
    ofstream fout("packrec.out");

    vector<pair<int, int> > rectangles;
    int s1, s2;
    while (fin >> s1 >> s2) {
        pair<int, int> rec = make_pair(min(s1, s2), max(s1, s2));
        rectangles.push_back(rec);
    }

    set<pair<int, int> > result = getBestEnclosingRectangles(rectangles);
    fout << area(*result.begin()) << endl;
    for (set<pair<int, int> >::iterator itr = result.begin();
         itr != result.end();
         itr++)
        fout << itr->first << " " << itr->second << endl;

    return 0;
}

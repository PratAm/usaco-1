/*
ID: joao.c.1
PROG: rect1
LANG: C++
*/

#include <algorithm>
#include <cmath>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

struct Rectangle {
    int llx;
    int lly;
    int urx;
    int ury;
    int color;

    Rectangle() {}

    Rectangle(int _llx, int _lly, int _urx, int _ury, int _color) {
        llx = _llx;
        lly = _lly;
        urx = _urx;
        ury = _ury;
        color = _color;
    }

    int area() {
        return (urx - llx) * (ury - lly);
    }
};

bool intersects(Rectangle r1, Rectangle r2) {
    return !(r2.llx > r1.urx ||
             r2.urx < r1.llx ||
             r2.ury < r1.lly ||
             r2.lly > r1.ury);
}

vector<Rectangle> getIntersections(Rectangle r1, Rectangle r2) {
    vector<Rectangle> intersections;

    if (intersects(r1, r2)) {
        Rectangle i = Rectangle(max(r2.llx, r1.llx),
                                max(r2.lly, r1.lly),
                                min(r2.urx, r1.urx),
                                min(r2.ury, r1.ury),
                                r2.color);
        if (i.ury < r1.ury)
            intersections.push_back(Rectangle(r1.llx, i.ury, r1.urx, r1.ury, r1.color));
        if (i.llx > r1.llx)
            intersections.push_back(Rectangle(r1.llx, i.lly, i.llx, i.ury, r1.color));
        if (i.lly > r1.lly)
            intersections.push_back(Rectangle(r1.llx, r1.lly, r1.urx, i.lly, r1.color));
        if (i.urx < r1.urx)
            intersections.push_back(Rectangle(i.urx, i.lly, r1.urx, i.ury, r1.color));
    } else {
        intersections.push_back(r1);
    }

    return intersections;
}

map<int, int> getSheetColors(vector<Rectangle> rectangles, int W, int H) {
    vector<Rectangle> finalRectangles;
    finalRectangles.push_back(rectangles[0]);

    for (unsigned int i = 1; i < rectangles.size(); i++) {
        vector<Rectangle> tempRectangles;

        for (unsigned int j = 0; j < finalRectangles.size(); j++) {
            vector<Rectangle> resulting =
                getIntersections(finalRectangles[j], rectangles[i]);
            for (unsigned int k = 0; k < resulting.size(); k++)
                tempRectangles.push_back(resulting[k]);
        }

        tempRectangles.push_back(rectangles[i]);
        finalRectangles = tempRectangles;
    }

    int totalArea = 0;
    map<int, int> colors;

    for (unsigned int i = 0; i < finalRectangles.size(); i++) {
        if (colors.find(finalRectangles[i].color) == colors.end())
            colors[finalRectangles[i].color] = finalRectangles[i].area();
        else
            colors[finalRectangles[i].color] += finalRectangles[i].area();
        totalArea += finalRectangles[i].area();
    }

    colors[1] += (W * H) - totalArea;

    return colors;
}

int main() {
    ifstream fin("rect1.in");
    ofstream fout("rect1.out");

    int A, B, N;
    fin >> A >> B >> N;

    vector<Rectangle> rectangles;

    for (int i = 0; i < N; i++) {
        Rectangle r;
        fin >> r.llx >> r.lly >> r.urx >> r.ury >> r.color;
        rectangles.push_back(r);
    }

    map<int, int> colors = getSheetColors(rectangles, A, B);
    for (map<int, int>::iterator itr = colors.begin();
         itr != colors.end();
         itr++) {
        fout << itr->first << " " << itr->second << endl;
    }

    return 0;
}

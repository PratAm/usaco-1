/*
ID: joao.c.1
PROG: maze1
LANG: C++
*/

#include <fstream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

int getMinimalSteps(vector<string> maze) {
    int directions[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int D = 4;
    int W = maze[0].size();
    int H = maze.size();
    map<pair<int, int>, int> distances;
    vector<pair<int, int> > exits;

    for (unsigned int i = 0; i < maze[0].size(); i++) {
        if (maze[0][i] == ' ')
            exits.push_back(make_pair(1, i));
        if (maze[maze.size() - 1][i] == ' ')
            exits.push_back(make_pair(maze.size() - 2, i));
    }

    for (unsigned int i = 0; i < maze.size(); i++) {
        if (maze[i][0] == ' ')
            exits.push_back(make_pair(i, 1));
        if (maze[i][maze[i].size() - 1] == ' ')
            exits.push_back(make_pair(i, maze[i].size() - 2));
    }

    for (unsigned int i = 0; i < exits.size(); i++)
        distances[exits[i]] = 1;

    for (unsigned int i = 0; i < exits.size(); i++) {
        pair<int, int> exit = exits[i];
        set<pair<int, int> > visited;
        queue<pair<int, int> > q;
        q.push(exit);
        visited.insert(exit);

        while (!q.empty()) {
            pair<int, int> current = q.front(); q.pop();

            for (int i = 0; i < D; i++) {
                pair<int, int> wall = make_pair(current.first + directions[i][0],
                                                current.second + directions[i][1]);
                if (maze[wall.first][wall.second] == ' ' &&
                    wall.first + directions[i][0] >= 0 &&
                    wall.first + directions[i][0] < H &&
                    wall.second + directions[i][1] >= 0 &&
                    wall.second + directions[i][1] < W) {
                    pair<int, int> next = make_pair(wall.first + directions[i][0],
                                                    wall.second + directions[i][1]);

                    if (visited.find(next) == visited.end()) {
                        visited.insert(next);
                        q.push(next);

                        if (distances.find(next) == distances.end() ||
                            distances[next] > distances[current] + 1) {
                            distances[next] = distances[current] + 1;
                        }
                    }
                }
            }
        }
    }

    int best = 0;
    for (map<pair<int, int>, int>::iterator itr = distances.begin();
         itr != distances.end();
         itr++) {
        if (itr->second > best)
            best = itr->second;
    }

    return best;
}

int main() {
    ifstream fin("maze1.in");
    ofstream fout("maze1.out");

    int W, H;
    vector<string> maze;
    fin >> W >> H;
    fin.get();

    for (int i = 0; i < 2 * H + 1; i++) {
        string s;
        getline(fin, s);

        if (s.size() != (unsigned int) 2 * W + 1)
            s = s + string(2 * W + 1 - s.size(), ' ');

        maze.push_back(s);
    }

    fout << getMinimalSteps(maze) << endl;

    return 0;
}

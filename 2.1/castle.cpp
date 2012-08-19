/*
ID: joao.c.1
PROG: castle
LANG: C++
*/

#include <fstream>
#include <map>
#include <set>
#include <vector>

using namespace std;

#define WEST 1
#define NORTH 2
#define EAST 4
#define SOUTH 8

int directions[][3] = {{WEST, 0, -1}, {NORTH, -1, 0}, {EAST, 0, 1}, {SOUTH, 1, 0}};

struct Wall {
    int y;
    int x;
    char direction;
};

void assignRoom(vector<vector<int> > & castle,
                pair<int, int> coords,
                map<pair<int, int>, int> & rooms,
                int roomNumber) {
    if (rooms.find(coords) == rooms.end()) {
        rooms[coords] = roomNumber;

        for (int i = 0; i < 4; i++) {
            if (!(castle[coords.first][coords.second] & directions[i][0])) {
                pair<int, int> nextCoords =
                    make_pair(coords.first + directions[i][1],
                              coords.second + directions[i][2]);
                assignRoom(castle, nextCoords, rooms, roomNumber);
            }
        }
    }
}

map<pair<int, int>, int> getRooms(vector<vector<int> > castle) {
    map<pair<int, int>, int> rooms;

    int H = castle.size();
    int W = castle[0].size();
    int nRooms = 0;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            pair<int, int> coords = make_pair(i, j);
            if (rooms.find(coords) == rooms.end())
                assignRoom(castle, coords, rooms, nRooms++);
        }
    }

    return rooms;
}

map<int, int> getRoomSizes(map<pair<int, int>, int> rooms) {
    map<int, int> roomSizes;

    for (map<pair<int, int>, int>::iterator itr = rooms.begin();
         itr != rooms.end();
         itr++) {
        if (roomSizes.find(itr->second) == roomSizes.end())
            roomSizes[itr->second] = 1;
        else
            roomSizes[itr->second]++;
    }

    return roomSizes;
}

int getSizeOfLargestRoom(map<int, int> roomSizes) {
    int largest = 0;

    for (map<int, int>::iterator itr = roomSizes.begin();
         itr != roomSizes.end();
         itr++) {
        if (itr->second > largest)
            largest = itr->second;
    }

    return largest;
}

Wall getBestWallToRemove(map<pair<int, int>, int> rooms,
                         map<int, int> roomSizes,
                         vector<vector<int> > castle) {
    int bestRoom = 0;
    Wall bestWall;

    int H = castle.size();
    int W = castle[0].size();

    for (int j = 0; j < W; j++) {
        for (int i = H - 1; i >= 0; i--) {
            pair<int, int> current = make_pair(i, j);
            if (i - 1 >= 0) {
                pair<int, int> other = make_pair(i - 1, j);
                if (rooms[current] != rooms[other] &&
                    roomSizes[rooms[current]] + roomSizes[rooms[other]] > bestRoom) {
                    bestRoom = roomSizes[rooms[current]] + roomSizes[rooms[other]];
                    bestWall.y = i + 1;
                    bestWall.x = j + 1;
                    bestWall.direction = 'N';
                }
            }

            if (j + 1 < W) {
                pair<int, int> other = make_pair(i, j + 1);
                if (rooms[current] != rooms[other] &&
                    roomSizes[rooms[current]] + roomSizes[rooms[other]] > bestRoom) {
                    bestRoom = roomSizes[rooms[current]] + roomSizes[rooms[other]];
                    bestWall.y = i + 1;
                    bestWall.x = j + 1;
                    bestWall.direction = 'E';
                }
            }
        }
    }

    return bestWall;
}

int main() {
    ifstream fin("castle.in");
    ofstream fout("castle.out");

    int M, N;
    vector<vector<int> > castle;
    fin >> M >> N;
    for (int i = 0; i < N; i++) {
        vector<int> castleLine;
        for (int j = 0; j < M; j++) {
            int edge;
            fin >> edge;
            castleLine.push_back(edge);
        }
        castle.push_back(castleLine);
    }

    map<pair<int, int>, int> rooms = getRooms(castle);
    map<int, int> roomSizes = getRoomSizes(rooms);
    Wall bestWallToRemove = getBestWallToRemove(rooms, roomSizes, castle);
    int largestRoomPossible = 0;

    if (bestWallToRemove.direction == 'N') {
        pair<int, int> current = make_pair(bestWallToRemove.y - 1,
                                           bestWallToRemove.x - 1);
        pair<int, int> other = make_pair(current.first - 1, current.second);
        largestRoomPossible = roomSizes[rooms[current]] +
            roomSizes[rooms[other]];
    } else if (bestWallToRemove.direction == 'E') {
        pair<int, int> current = make_pair(bestWallToRemove.y - 1,
                                           bestWallToRemove.x - 1);
        pair<int, int> other = make_pair(current.first, current.second + 1);
        largestRoomPossible = roomSizes[rooms[current]] +
            roomSizes[rooms[other]];
    }

    fout << roomSizes.size() << endl;
    fout << getSizeOfLargestRoom(roomSizes) << endl;
    fout << largestRoomPossible << endl;
    fout << bestWallToRemove.y << " " << bestWallToRemove.x << " " << bestWallToRemove.direction << endl;

    return 0;
}

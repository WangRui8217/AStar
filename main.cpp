#include "AStar.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::list;
using std::vector;

int main() {
  vector<vector<int>> map = {{0, 0, 0, 0, 1, 1, 1, 1},
                             {0, 0, 0, 0, 0, 1, 1, 1},
                             {1, 1, 0, 1, 1, 0, 0, 0},
                             {1, 0, 0, 0, 0, 0, 0, 0}};

  int m = map.size();
  int n = map[0].size();

  AStar astar;

  astar.get_map(map);

  PointInfo start(0, 0);
  PointInfo end(3, 7);

  list<PointInfo *> path = astar.getPath(start, end, false);
  for (auto &point : path) {
    cout << "(" << point->row << "," << point->col << ")";
    cout << " F=" << point->F << " G=" << point->G << " H=" << point->H << endl;
    map[point->row][point->col] = 2;
  }

  for (int i = 0; i < 10; i++) {
    cout << "# ";
  }
  cout << '\n' << "map(\"2\" means path, \"1\" means obstacle): " << endl;

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cout << map[i][j] << ' ';
    }
    cout << '\n';
  }

  return 0;
}
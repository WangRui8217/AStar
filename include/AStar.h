#ifndef ASTAR_H_
#define ASTAR_H_

#include <iostream>
#include <list>
#include <vector>

const int CostStr = 5;
const int CostObl = 7;

using std::list;
using std::vector;

struct PointInfo {
  int row, col;
  int F, G, H;
  PointInfo *pre;
  PointInfo(int x, int y) : row(x), col(y), F(0), G(0), H(0), pre(nullptr) {}
};

class AStar {
private:
  //计算F、G、H
  int get_G(PointInfo *star, PointInfo *now);
  int get_H(PointInfo *now, PointInfo *end);
  int get_F(PointInfo *now);

  vector<vector<int>> _map;
  list<PointInfo *> open_set;
  list<PointInfo *> close_set;

  PointInfo *FindPath(PointInfo &p_star, PointInfo &p_end,
                      bool is_ignore_corner);

  vector<PointInfo *> AvailPointsAround(const PointInfo *point,
                                        bool is_ignore_corner) const;

  bool isAvail(const PointInfo *point, const PointInfo *next,
               bool is_ignore_corner) const;

  PointInfo *isInSet(const list<PointInfo *> &set,
                     const PointInfo *point) const;

  PointInfo *MinCostPoint();

public:
  void get_map(vector<vector<int>> &map);

  list<PointInfo *> getPath(PointInfo &p_start, PointInfo &p_end,
                            bool is_ignore_corner);
};

#endif
#include "AStar.h"
#include <cmath>
#include <iostream>
#include <vector>

using std::list;
using std::vector;

int AStar::get_G(PointInfo *star, PointInfo *now) {
  int G_now = CostStr;
  if (abs(now->row - star->row) + abs(now->col - star->col) == 2) {
    G_now = CostObl;
  }
  int G_pre = now->pre == nullptr ? 0 : now->pre->G;
  return G_pre + G_now;
}

int AStar::get_H(PointInfo *now, PointInfo *end) {
  return sqrt(pow((double)(end->row - now->row), 2) +
              pow((double)(end->col - now->col), 2)) *
         CostStr;
}

int AStar::get_F(PointInfo *now) { return now->G + now->H; }

void AStar::get_map(vector<vector<int>> &map) { _map = map; };

PointInfo *AStar::FindPath(PointInfo &p_star, PointInfo &p_end,
                           bool is_ignore_corner) {
  open_set.push_back(new PointInfo(p_star.row, p_star.col));
  while (!open_set.empty()) {
    auto now_point = MinCostPoint();
    open_set.remove(now_point);
    close_set.push_back(now_point);
    auto points_around = AvailPointsAround(now_point, is_ignore_corner);
    for (auto &next : points_around) {
      if (!isInSet(open_set, next)) {
        open_set.push_back(next);
        next->pre = now_point;
        next->G = get_G(now_point, next);
        next->H = get_H(next, &p_end);
        next->F = get_F(next);
      } else {
        int temp_G = get_G(now_point, next);
        if (temp_G < next->G) {
          next->G = temp_G;
          next->F = get_F(next);
          next->pre = now_point;
        }
      }
      auto ret_point = isInSet(open_set, &p_end);
      if (ret_point) {
        return ret_point;
      }
    }
  }
  return nullptr;
}

list<PointInfo *> AStar::getPath(PointInfo &p_star, PointInfo &p_end,
                                 bool is_ignore_corner) {
  auto p_result = FindPath(p_star, p_end, is_ignore_corner);
  list<PointInfo *> path;
  while (p_result) {
    path.push_front(p_result);
    p_result = p_result->pre;
  }
  open_set.clear();
  close_set.clear();
  return path;
}

vector<PointInfo *> AStar::AvailPointsAround(const PointInfo *point,
                                             bool is_ignore_corner) const {
  vector<PointInfo *> points_around;
  for (int i = point->row - 1; i <= point->row + 1; i++) {
    for (int j = point->col - 1; j <= point->col + 1; j++) {
      if (isAvail(point, new PointInfo(i, j), is_ignore_corner)) {
        points_around.push_back(new PointInfo(i, j));
      }
    }
  }
  return points_around;
}

bool AStar::isAvail(const PointInfo *point, const PointInfo *next,
                    bool is_ignore_corner) const {
  if (next->row < 0 || next->row > _map.size() - 1 || next->col < 0 ||
      next->col > _map[0].size() - 1 || _map[next->row][next->col] == 1 ||
      (next->row == point->row && next->col == point->col) ||
      isInSet(close_set, next)) {
    return false;
  } else if (abs(next->row - point->row) + abs(next->col - point->col) == 1) {
    return true;
  } else if (_map[point->row][next->col] + _map[next->row][point->col] != 2) {
    return true;
  } else {
    return is_ignore_corner;
  }
}

PointInfo *AStar::isInSet(const list<PointInfo *> &list,
                          const PointInfo *point) const {
  for (auto pt : list) {
    if (pt->row == point->row && pt->col == point->col) {
      return pt;
    }
  }
  return nullptr;
}

PointInfo *AStar::MinCostPoint() {
  if (!open_set.empty()) {
    auto mincostpoint = open_set.front();
    for (auto &point : open_set) {
      if (point->F < mincostpoint->F) {
        mincostpoint = point;
      }
    }
    return mincostpoint;
  }
  return nullptr;
}
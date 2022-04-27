#include "polygon.h"
vector<Point> Polygon::points;  // 顶点坐标数组
vector<vector<bool>> Polygon::graph;  // 邻接矩阵，表示哪两个点之间相邻。
Polygon::Polygon() {}

Polygon::Polygon(const vector<int>& point_ids) : point_ids_(point_ids) {
  size = point_ids.size();
}

void Polygon::ComputeAttribute() {
  // 判断是否为简单多边形
  is_simple_ = ComputeIsSimple();
  if (!is_simple_) return;
  // 计算外包矩形
  for (int i = 0; i < size; i++) {
    if (point_bounds_[0] > points[point_ids_[i]].x_)
      point_bounds_[0] = points[point_ids_[i]].x_;
    if (point_bounds_[1] < points[point_ids_[i]].x_)
      point_bounds_[1] = points[point_ids_[i]].x_;
    if (point_bounds_[2] > points[point_ids_[i]].y_)
      point_bounds_[2] = points[point_ids_[i]].y_;
    if (point_bounds_[3] < points[point_ids_[i]].y_)
      point_bounds_[3] = points[point_ids_[i]].y_;
  }
  // 计算面积
  area_ = ComputeArea();
  // 计算周长
  length_ = ComputeLength();
  // 计算是否为凸多边形
  is_convex_ = ComputeIsConvex();
}

void Polygon::GenerateGraph(const vector<vector<Point>>& input) {
  points.clear();
  graph.clear();
  int point_max_size = 2 * input.size();  //最大可能的节点数
  vector<bool> temp(point_max_size, false);
  graph.resize(point_max_size, temp);  // 初始化邻接矩阵，全部设为 false
  for (unsigned long long i = 0; i < input.size(); i++) {
    int start_id, end_id;
    vector<Point>::iterator result;
    // 查找当前边的起点是否存在 points 表中
    result = find(points.begin(), points.end(), input[i][0]);
    if (result == points.end()) {
      //没有找到
      start_id = points.size();
      points.push_back(input[i][0]);

    } else {
      start_id = result - points.begin();
    }
    // 查找当前边的终点是否存在 points 表中
    result = find(points.begin(), points.end(), input[i][1]);
    if (result == points.end()) {
      //没有找到
      end_id = points.size();
      points.push_back(input[i][1]);

    } else {
      end_id = result - points.begin();
    }
    graph[start_id][end_id] = graph[end_id][start_id] = true;
  }
}

bool Polygon::CheckCrossLine(Point P1, Point P2, Point Q1, Point Q2) {
  double A = (P2 - P1) ^ (Q1 - P1);
  double B = (P2 - P1) ^ (Q2 - P1);
  double C = (Q2 - Q1) ^ (P1 - Q1);
  double D = (Q2 - Q1) ^ (P2 - Q1);
  // 全部异号说明规范相交
  if (A * B < 0 && C * D < 0) {
    return true;
  } else {
    return false;
  }
}

inline double Polygon::DistanceBetweenTwoPoint(Point A, Point B) {
  return sqrt((B.x_ - A.x_) * (B.x_ - A.x_) + (B.y_ - A.y_) * (B.y_ - A.y_));
}

bool Polygon::ComputeIsSimple() {
  for (int i = 0; i < size; i++) {
    for (int j = i + 2; j <= i - 2 + size; j++) {
      int i2 = (i == size - 1) ? 0 : i + 1;
      int j1 = (j >= size) ? (j - size) : j;
      int j2 = (j + 1 >= size) ? (j + 1 - size) : j + 1;
      if (CheckCrossLine(points[point_ids_[i]], points[point_ids_[i2]],
                         points[point_ids_[j1]], points[point_ids_[j2]])) {
        return false;
      }
    }
  }
  return true;
}

double Polygon::ComputeArea() {
  double ans = 0;
  for (int i = 0; i < size - 1; i++) {
    ans += points[point_ids_[i]] ^ points[point_ids_[i + 1]];
  }
  ans += points[point_ids_[size - 1]] ^ points[point_ids_[0]];
  return abs(ans / 2);
}

double Polygon::ComputeLength() {
  double ans = 0;
  for (int i = 0; i < size - 1; i++) {
    ans += DistanceBetweenTwoPoint(points[point_ids_[i]],
                                   points[point_ids_[i + 1]]);
  }
  ans += DistanceBetweenTwoPoint(points[point_ids_[size - 1]],
                                 points[point_ids_[0]]);
  return ans;
}

bool Polygon::ComputeIsConvex() {
  double temp = points[point_ids_[size - 1]] ^ points[point_ids_[0]];
  for (int i = 0; i < size; i++) {
    if (temp * (points[point_ids_[i]] ^ points[i + 1]) < 0) {
      return false;
    }
  }
  return true;
}

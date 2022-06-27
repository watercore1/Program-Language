#ifndef POLYGON_H
#define POLYGON_H
#include <algorithm>
#include <climits>
#include <cmath>
#include <vector>

#include "point.h"

/**
 * @brief 使用顶点的编号序列表示一个多边形
 */
class Polygon {
 public:
  // 构造函数
  Polygon();
  Polygon(const vector<int>& point_ids);
  // 计算多边形属性
  const vector<int>& GetPointIds() { return point_ids_; }
  void ComputeAttribute();
  bool IsSimple() { return is_simple_; };  // 是否为简单多边形
  const vector<double>& GetBound() { return mbr; };
  double GetArea() { return area_; };
  double GetLength() { return length_; };
  bool IsConvex() { return is_convex_; };

  // 由于所有多边形共用同一张无向图，所以把无向图作为静态成员
  static void GenerateGraph(
      const vector<vector<Point>>& input);  // 将输入转化为邻接矩阵
  static vector<Point> points;              // 顶点坐标数组
  static vector<vector<bool>> graph;  // 邻接矩阵，表示哪两个点之间相邻。
 private:
  vector<int> point_ids_;  // 顶点的编号序列
  int size = 0;
  bool is_simple_ = false;
  double area_, length_;  // 面积和周长
  vector<double> mbr = {
      INT_MAX, INT_MIN, INT_MAX,
      INT_MIN};  // 外接多边形，按顺序依次为x左，x右，y下，y上
  bool is_convex_;  // 是否为凸多边形
  bool CheckCrossLine(Point P1, Point P2, Point Q1,
                      Point Q2);  // 判断两条边是否相交
  double DistanceBetweenTwoPoint(Point A, Point B);  // 计算两点距离
  bool ComputeIsSimple();
  double ComputeArea();
  double ComputeLength();
  bool ComputeIsConvex();
};

#endif  // POLYGON_H

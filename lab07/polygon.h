#ifndef POLYGON_H_
#define POLYGON_H_

#include "ring.h"

// Polygon 与 ring 唯一的区别在于多了一个内环
class Polygon : public Ring {
 private:
  Ring inner_ring_;  //内环
  bool has_inner_;   //是否有内环
 public:
  //继承折线的构造函数
  Polygon() = default;
  Polygon(const string id, const vector<Point>& outer_points)
      : Ring(id_, outer_points) {}
  Polygon(const string id, istringstream& coordinates)
      : Ring(id, coordinates) {}
  //修改外环的方法已经继承，只需要实现修改内环的方法
  //设置新内环
  void SetInner(const vector<Point>& inner_points) {
    inner_ring_ = Ring("Inner Ring", inner_points);
    has_inner_ = true;
  }
  void SetInner(istringstream& coordinates) {
    inner_ring_ = Ring("Inner Ring", coordinates);
    has_inner_ = true;
  }
  //设置 inner_ring 的第i个点的坐标
  void SetInnerPoint(const size_t i, const double new_x, const double new_y) {
    inner_ring_.SetPoint(i, new_x, new_y);
  }
  void SetInnerPoint(const size_t i, istringstream& coordinates) {
    inner_ring_.SetPoint(i, coordinates);
  }
  //移动 inner_ring 的第i个点的坐标
  void MoveInnerPoint(const size_t i, const double bias_x,
                      const double bias_y) {
    inner_ring_.MovePoint(i, bias_x, bias_y);
  }
  void MoveInnerPoint(const size_t i, istringstream& coordinates) {
    inner_ring_.MovePoint(i, coordinates);
  }
  //删除 inner_ring 的第i个点
  void DelInnerPoint(const size_t i) { inner_ring_.DelPoint(i); }
  //重新定义：判断点 p 是否在多边形内部
  virtual bool CoverPoint(const Point& p) const;
  //和 ring 相比，输出到文件时唯一的差别就是几何要素对应的内容不一样，
  virtual string ToString() const;
  friend ofstream& operator<<(ofstream& ofs, const Polygon& p);
};

#endif  // POLYGON_H_
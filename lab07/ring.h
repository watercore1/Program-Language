#ifndef RING_H_
#define RING_H_
#include "polyline.h"

// ring 和 polyline 区别在于：points_ 的最后一个元素和第一个元素相连
class Ring : public Polyline {
 protected:
  string area_ = "Null";  //多一个面积属性
 public:
  Ring() = default;
  //继承折线的构造函数
  Ring(const string id, const vector<Point>& points) : Polyline(id, points) {}
  Ring(const string id, istringstream& coordinates) : Polyline(id, coordinates) {}
  //设计新面积
  void SetArea(const string area) { area_ = area; }
  //判断点p是否在环内
  virtual bool CoverPoint(const Point& p) const;
  virtual string ToString() const;
  friend ofstream& operator<<(ofstream& os, const Ring& p);
};

#endif  // RING_H_

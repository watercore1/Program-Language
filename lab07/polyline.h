#ifndef POLYLINE_H_
#define POLYLINE_H_

#include "point.h"

class Polyline : public Geometry {
 protected:
  vector<Point> points_;
  string length_ = "Null";

 public:
  Polyline() = default;
  Polyline(const string id, const vector<Point> &points)
      : Geometry(id), points_(points) {}
  //根据输入的字符串流，构造折线
  Polyline(const string id, istringstream &coordinates);
  //设置第i个点的坐标
  void SetPoint(const size_t i, const double new_x, const double new_y) {
    points_[i].SetXY(new_x, new_y);
  }
  void SetPoint(const size_t i, istringstream &coordinates) {
    points_[i].SetXY(coordinates);
  }
  //移动第i个点的坐标
  void MovePoint(const size_t i, const double bias_x, const double bias_y) {
    points_[i].MoveXY(bias_x, bias_y);
  }
  void MovePoint(const size_t i, istringstream &coordinates) {
    points_[i].MoveXY(coordinates);
  }
  //删除第i个点
  void DelPoint(const size_t i) { points_.erase(points_.begin() + i); }
  //设置长度
  void SetLength(const string length) { length_ = length; }
  //将几何数据转为字符串
  virtual string ToString() const;
  //输出到文件中
  friend ofstream &operator<<(ofstream &ofs, const Polyline &p);
};

#endif  // POLYLINE_H_
#ifndef POINT_H_
#define POINT_H_

#include "geometry.h"

class Point:public Geometry{
 private:
  double x_ = 0;
  double y_ = 0;

 public:
  Point() = default;
  Point(const string id, const double x, const double y)
      : Geometry(id), x_(x), y_(y) {}
  //根据输入的字符串流，构造点
  Point(const string id, istringstream &coordinates);
  //两个点坐标是否相等
  bool operator==(const Point& other) const {
    return IsDoubleEqual(x_, other.x_) && IsDoubleEqual(y_, other.y_);
  }
  //返回x坐标
  double GetX() const { return x_; }
  //返回y坐标
  double GetY() const { return y_; };
  //设置新坐标
  void SetXY(const double new_x, const double new_y);
  void SetXY(istringstream &coordinates);
  //移动一个偏移量
  void MoveXY(const double bias_x, const double bias_y);
  void MoveXY(istringstream &coordinates);
  //将几何数据转为字符串
  virtual string ToString() const;
  //输出到文件中的格式
  friend ofstream &operator<<(ofstream &ofs,const Point &p);
};

#endif  // POINT_H_
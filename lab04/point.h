#ifndef POINT_H
#define POINT_H

#include <string>
using namespace std;

/**
 * @brief 可用于表示一个点，也可用于表示一个向量
 */
class Point {
 public:
  double x_, y_;
  Point();
  Point(double x, double y);
  string Str();  // 打印该点的坐标
  bool operator==(const Point &other) const;
  // 矢量的运算
  Point operator-(const Point &other) const;   // 减法
  Point operator+(const Point &other) const;   // 加法
  double operator*(const Point &other) const;  // 点积
  double operator^(const Point &other) const;  // 叉积
 private:
  static const double eps;               // double 精度
  bool equal(double a, double b) const;  // 判断两个 double 类型的数是否相等
};

#endif  // POINT_H

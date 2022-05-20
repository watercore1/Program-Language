#include "point.h"

Point::Point() {}

Point::Point(double x, double y) {
  x_ = x;
  y_ = y;
}

Point::Point(string x, string y) {
  // string转换为小数
  x_ = atof(x.c_str());
  y_ = atof(y.c_str());
}

string Point::Str() const {
  string temp = "(" + to_string(x_) + " , " + to_string(y_) + ")";
  return temp;
}

double TwoPointDistance(Point a, Point b) {
  return sqrt((a.x_ - b.x_) * (a.x_ - b.x_) + (a.y_ - b.y_) * (a.y_ - b.y_));
}

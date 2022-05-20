#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <string>
using namespace std;

class Point {
 public:
  double x_, y_;
  Point();
  Point(double x, double y);
  Point(string x, string y);
  string Str() const;
};

double TwoPointDistance(Point a, Point b);

#endif  // POINT_H

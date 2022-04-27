#include "point.h"
const double Point::eps = 1e-8;
Point::Point() : x_(0), y_(0) {}

Point::Point(double x, double y) : x_(x), y_(y) {}

string Point::Str() {
  string temp = "(" + to_string(x_) + "," + to_string(y_) + ")";
  return temp;
}

bool Point::equal(double a, double b) const {
  if ((a - b) > -eps && (a - b) < eps)  // 防止误差
    return true;
  else
    return false;
}

bool Point::operator==(const Point &other) const {
  return (equal(this->x_, other.x_) && equal(this->y_, other.y_));
}

Point Point::operator-(const Point &other) const {
  Point temp(this->x_ - other.x_, this->y_ - other.y_);
  return temp;
}

Point Point::operator+(const Point &other) const {
  Point temp(this->x_ + other.x_, this->y_ + other.y_);
  return temp;
}

double Point::operator*(const Point &other) const {
  return this->x_ * other.x_ + this->y_ * other.y_;
}

double Point::operator^(const Point &other) const {
  return this->x_ * other.y_ - this->y_ * other.x_;
}

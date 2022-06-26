#include "point.h"

Point::Point(const string id, istringstream& coordinates) {
  id_ = id;
  string temp;
  coordinates >> temp;
  x_ = stod(temp);
  coordinates >> temp;
  y_ = stod(temp);
}

void Point::SetXY(const double new_x, const double new_y) {
  x_ = new_x;
  y_ = new_y;
}
void Point::SetXY(istringstream &coordinates){
  string temp;
  coordinates >> temp;
  x_ = stod(temp);
  coordinates >> temp;
  y_ = stod(temp);
}
void Point::MoveXY(const double bias_x, const double bias_y) {
  x_ += bias_x;
  y_ += bias_y;
}
void Point::MoveXY(istringstream &coordinates){
  string temp;
  coordinates >> temp;
  x_ += stod(temp);
  coordinates >> temp;
  y_ += stod(temp);
}
string Point::ToString() const {
  string temp = "[" + to_string(int(x_)) + "," + to_string(int(y_)) + "]";
  return temp;
}

ofstream& operator<<(ofstream& ofs, const Point& p) {
  ofs << "point " << p.id_ << " " << p.ToString() << ", name=" << p.name_
      << endl;
  return ofs;
}
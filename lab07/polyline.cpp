#include "polyline.h"

Polyline::Polyline(const string id, istringstream &coordinates) {
  id_ = id;
  string temp_x, temp_y;
  while (coordinates >> temp_x >> temp_y) {
    points_.push_back(Point(id, stod(temp_x), stod(temp_y)));
  }
}

string Polyline::ToString() const {
  string temp = "[";
  for (size_t i = 0; i < points_.size() ; i++) {
    temp += points_[i].ToString() + ", ";
  }
  if(!points_.empty()){
    temp.pop_back();
    temp.pop_back();
  }
  temp += "]";
  return temp;
}

ofstream &operator<<(ofstream &ofs, const Polyline &p) {
  ofs << "polyline " << p.id_ << " " << p.ToString() << ", name=" << p.name_
      << ", length=" << p.length_ << endl;
  return ofs;
}
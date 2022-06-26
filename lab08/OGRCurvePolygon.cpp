//
// Created by 小田小田 on 2020/6/8.
//

#include "OGRCurvePolygon.h"

void OGRCurvePolygon::GetMBR(double &XMin, double &YMin, double &XMax,
                             double &YMax) const {
  double x1, y1, x2, y2;
  if (list_.size() != 0) {
    list_[0].GetMBR(x1, y1, x2, y2);
    XMin = x1, YMin = y1, XMax = x2, YMax = y2;
    for (size_t i = 1; i < list_.size(); i++) {
      list_[i].GetMBR(x1, y1, x2, y2);
      if (x1 < XMin) XMin = x1;
      if (y1 < YMin) YMin = y1;
      if (x2 > XMax) XMax = x2;
      if (y2 > YMax) YMax = y2;
    }
  }
}
double OGRCurvePolygon::GetArea() const {
  double area = list_[0].GetArea();
  for (size_t i = 1; i < list_.size(); i++) {
    area -= list_[i].GetArea();
  }
  return area;
}

OGRCurvePolygon *OGRCurvePolygon::Clone() const {
  std::vector<OGRLinearRing> new_list(list_);
  return new OGRCurvePolygon(new_list);
}

void OGRCurvePolygon::Clone(OGRCurvePolygon &other) { list_ = other.list_; }

bool OGRCurvePolygon::Equals(const OGRCurvePolygon &other) const {
  bool flag = false;  //判断第i条边是否找到对应的相等边
  if (other.list_.size() == list_.size()) {
    for (size_t i = 0; i < list_.size(); i++) {
      for (size_t j = 0; j < other.list_.size(); j++) {
        if (list_[i].Equals(other.list_[j])) {
          flag = true;
        }
      }
      if (!flag) return false;
      flag = false;
    }
  } else {
    return false;
  }
  return true;
}

const std::vector<OGRLinearRing> &OGRCurvePolygon::GetList() { return list_; }

std::pair<OGRPoint, OGRPoint> OGRCurvePolygon::GetMBR() {
  double x1, y1, x2, y2;
  GetMBR(x1, y1, x2, y2);
  return std::pair<OGRPoint, OGRPoint>(OGRPoint(x1, y1), OGRPoint(x2, y2));
}

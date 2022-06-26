#include "OGRLineString.h"

double OGRLineString::GetLength() const {
  double length = 0.0;
  if (list_.empty()) return length;
  for (size_t i = 0; i < list_.size() - 1; i++) {
    length += list_[i].Distance(list_[i + 1]);
  }
  return length;
}

bool OGRLineString::Intersects(OGRLineString &other) {
  double x1, x2, y1, y2;
  double x3, x4, y3, y4;
  GetMBR(x1, y1, x2, y2);
  other.GetMBR(x3, y3, x4, y4);

  if (((x1 - x3) * (x2 - x4) > 0) && ((y1 - y3) * (y2 - y4) > 0))
    // 此时外包多边形不相交
    return false;
  else {
    for (size_t i = 0; i < list_.size() - 1; i++) {
      for (size_t j = 0; j < other.list_.size() - 1;
           j++) {  // 两两线段查看是否相交
        //如果两个线段相交，等价于如下条件
        //对于每条线段而言，它的延长线与另一条线段相交
        OGRPoint P = list_[i] - list_[i + 1];
        OGRPoint P1 = other.list_[j] - list_[i + 1];
        OGRPoint P2 = other.list_[j + 1] - list_[i + 1];

        OGRPoint Q = other.list_[j] - other.list_[j + 1];
        OGRPoint Q1 = list_[i] - other.list_[j + 1];
        OGRPoint Q2 = list_[i + 1] - other.list_[j + 1];

        if (Compare((P ^ P1) * (P ^ P2), 0) == -1 &&
            Compare((Q ^ Q1) * (Q ^ Q2), 0) == -1) {
          return true;
        }
      }
    }
  }
  return false;
}

void OGRLineString::Clone(OGRLineString &Sample) { list_ = Sample.list_; }

OGRLineString *OGRLineString::Clone() const { return new OGRLineString(list_); }
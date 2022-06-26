#include "OGRLinearRing.h"

double OGRLinearRing::GetArea() const {
  double area = 0;
  for (size_t i = 0, k = list_.size() - 1; i < list_.size(); k = i++) {
    area += list_[k].GetX() * list_[i].GetY();
    area -= list_[k].GetY() * list_[i].GetX();
  }
  return area / 2;
}

double OGRLinearRing::GetLength() const {
  double length = 0.0;
  if (list_.empty()) return length;
  for (size_t i = 0; i < list_.size() - 1; i++) {
    length += list_[i].Distance(list_[i + 1]);
  }
  //首尾点相连
  length += list_.back().Distance(list_[0]);
  return length;
}

//判断点Q是否在P1和P2的线段上
bool OGRLinearRing::OnSegment(OGRPoint P1, OGRPoint P2, OGRPoint Q) {
  //前一个判断点Q在P1P2直线上 后一个判断在P1P2范围上
  return Compare((P1 - Q) ^ (P2 - Q), 0) == 0 &&
         Compare((P1 - Q) * (P2 - Q), 0) <= 0;
}

bool OGRLinearRing::Contains(const OGRPoint &point) {
  bool flag = false;  // 相当于计数
  OGRPoint P1, P2;    // 多边形一条边的两个顶点
  double x1, y1, x2, y2;
  GetMBR(x1, y1, x2, y2);
  //遍历所有边，包括首尾相连的边
  for (size_t i = 0, j = list_.size() - 1; i < list_.size(); j = i++) {
    P1 = list_[i];
    P2 = list_[j];
    if (OnSegment(P1, P2, point)) return false;  //点在多边形一条边上
    //首先判断 min(P1.y,P2.y)<P.y<=max(P1.y,P2.y)
    //后一个判断 被测点 在 射线与边交点 的左边
    if (Compare((P1.GetY() - point.GetY()) * (P2.GetY() - point.GetY()), 0) <
            0 &&
        Compare(point.GetX(), P1.GetX() + (point.GetY() - P1.GetY()) *
                                              (P1.GetX() - P2.GetX()) /
                                              (P1.GetY() - P2.GetY())

                    ) < 0)
      flag = !flag;
  }
  return flag;
}

bool OGRLinearRing::Intersects(OGRLineString &line_string) {
  double x1, x2, y1, y2;
  double bx1, bx2, by1, by2;
  GetMBR(x1, y1, x2, y2);
  line_string.GetMBR(bx1, by1, bx2, by2);

  std::vector<OGRPoint> plist_ = line_string.GetList();

  for (size_t i = 0, k = list_.size() - 1; i < list_.size(); k = i++) {
    for (size_t j = 0; j < plist_.size() - 1; j++) {  // 两两线段查看是否相交
      OGRPoint P(plist_[j + 1].GetX() - plist_[j].GetX(),
                 plist_[j + 1].GetY() - plist_[j].GetY());
      OGRPoint P1(list_[i].GetX() - plist_[j].GetX(),
                  list_[i].GetY() - plist_[j].GetY());
      OGRPoint P2(list_[k].GetX() - plist_[j].GetX(),
                  list_[k].GetY() - plist_[j].GetY());

      OGRPoint Q(list_[k].GetX() - list_[i].GetX(),
                 list_[k].GetY() - list_[i].GetY());
      OGRPoint Q1(plist_[j + 1].GetX() - list_[i].GetX(),
                  plist_[j + 1].GetY() - list_[i].GetY());
      OGRPoint Q2(plist_[j].GetX() - list_[i].GetX(),
                  plist_[j].GetY() - list_[i].GetY());

      if (Compare((P ^ P1) * (P ^ P2), 0) < 0 &&
          Compare((Q ^ Q1) * (Q ^ Q2), 0) < 0)
        return true;
    }
  }
  return false;
}

bool OGRLinearRing::Intersects(OGRLinearRing &object) {
  double x1, x2, y1, y2;
  double bx1, bx2, by1, by2;
  GetMBR(x1, y1, x2, y2);
  object.GetMBR(bx1, by1, bx2, by2);

  std::vector<OGRPoint> plist_ = object.GetList();

  for (size_t i = 0, k = list_.size() - 1; i < list_.size(); k = i++) {
    for (size_t j = 0, l = plist_.size() - 1; j < plist_.size();
         l = j++) {  // 两两线段查看是否相交
      OGRPoint P(plist_[j].GetX() - plist_[l].GetX(),
                 plist_[j].GetY() - plist_[l].GetY());
      OGRPoint P1(list_[i].GetX() - plist_[l].GetX(),
                  list_[i].GetY() - plist_[l].GetY());
      OGRPoint P2(list_[k].GetX() - plist_[l].GetX(),
                  list_[k].GetY() - plist_[l].GetY());

      OGRPoint Q(list_[k].GetX() - list_[i].GetX(),
                 list_[k].GetY() - list_[i].GetY());
      OGRPoint Q1(plist_[j].GetX() - list_[i].GetX(),
                  plist_[j + 1].GetY() - list_[i].GetY());
      OGRPoint Q2(plist_[l].GetX() - list_[i].GetX(),
                  plist_[l].GetY() - list_[i].GetY());

      if (Compare((P ^ P1) * (P ^ P2), 0) < 0 &&
          Compare((Q ^ Q1) * (Q ^ Q2), 0) < 0)
        return true;
    }
  }
  return false;
}

void OGRLinearRing::Clone(OGRLinearRing &other) { list_ = other.list_; }

OGRLinearRing *OGRLinearRing::Clone() const { return new OGRLinearRing(list_); }

bool OGRLinearRing::On(const OGRPoint &object) {
  OGRPoint P1, P2;  //多边形一条边的两个顶点
  double x1, y1, x2, y2;
  GetMBR(x1, y1, x2, y2);
  //遍历所有边，包括首尾相连的边
  for (size_t i = 0, j = list_.size() - 1; i < list_.size(); j = i++) {
    P1 = list_[i];
    P2 = list_[j];
    if (OnSegment(P1, P2, object)) return true;  //点在多边形一条边上
  }
  return false;
}

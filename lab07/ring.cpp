#include "ring.h"

bool Ring::CoverPoint(const Point &p) const {
  bool isInside = false;
  int count = 0;

  double minX = 1e10;
  for (size_t i = 0; i < points_.size(); i++) {
    minX = min(minX, points_[i].GetX());
  }

  double px = p.GetX();
  double py = p.GetY();
  double linePoint1x = px;
  double linePoint1y = py;
  double linePoint2x = minX - 10;  //取最小的X值还小的值作为射线的终点
  double linePoint2y = py;

  //遍历每一条边
  for (size_t i = 0; i < points_.size() - 1; i++) {
    double cx1 = points_[i].GetX();
    double cy1 = points_[i].GetY();
    double cx2 = points_[i + 1].GetX();
    double cy2 = points_[i + 1].GetY();

    if (IsPointOnLine(px, py, cx1, cy1, cx2, cy2)) {
      return true;
    }
    //平行则不相交
    if (IsDoubleEqual(cy1, cy2)) {
      continue;
    }

    if (IsPointOnLine(cx1, cy1, linePoint1x, linePoint1y, linePoint2x,
                      linePoint2y)) {
      //只保证上端点+1
      if (cy1 > cy2) {
        count++;
      }
    } else if (IsPointOnLine(cx2, cy2, linePoint1x, linePoint1y, linePoint2x,
                             linePoint2y)) {
      //只保证上端点+1
      if (cy2 > cy1) {
        count++;
      }
    } else if (IsIntersect(cx1, cy1, cx2, cy2, linePoint1x, linePoint1y,
                           linePoint2x, linePoint2y)) {
      //已经排除平行的情况
      count++;
    }
  }

  if (count % 2 == 1) {
    isInside = true;
  }

  return isInside;
}

string Ring::ToString() const {
  //调用 Polyline 的字符串化方法
  string temp = Polyline::ToString();
  //增加一个点
  if(!points_.empty()){
    temp.pop_back();
    temp += ", " + points_[0].ToString() + "]";
  }
  
  return temp;
}

ofstream &operator<<(ofstream &ofs, const Ring &p) {
  ofs << "ring " << p.id_ << " " << p.ToString() << ", name=" << p.name_
      << ", length=" << p.length_ << ", area=" << p.area_ << endl;
  return ofs;
}
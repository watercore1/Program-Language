#include "OGRCurve.h"

bool OGRCurve::IsEmpty() const { return list_.empty(); }

void OGRCurve::GetMBR(double &XMin, double &YMin, double &XMax,
                      double &YMax) const {
  XMin = list_[0].GetX();
  XMax = list_[0].GetX();
  YMin = list_[0].GetY();
  YMax = list_[0].GetY();
  for (auto i : list_) {
    if (i.GetX() < XMin) XMin = i.GetX();
    if (i.GetX() > XMax) XMax = i.GetX();
    if (i.GetY() < YMin) YMin = i.GetY();
    if (i.GetY() > YMax) YMax = i.GetY();
  }
}

std::pair<OGRPoint, OGRPoint> OGRCurve::GetMBR() const {
  double x1, y1, x2, y2;
  GetMBR(x1, y1, x2, y2);
  return std::pair<OGRPoint, OGRPoint>(OGRPoint(x1, y1), OGRPoint(x2, y2));
}

void OGRCurve::Clone(OGRCurve &other) { list_ = other.list_; }

bool OGRCurve::Equals(const OGRGeometry &object) const {
  const OGRCurve *p = dynamic_cast<const OGRCurve *>(&object);

  if (this->list_.size() != (*p).list_.size())
    return false;
  else {
    for (size_t i = 0; i < list_.size(); i++) {
      if (!list_[i].Equals((*p).list_[i])) {
        return false;
      }
    }
  }
  return true;
}

OGRCurve::OGRCurve(double x1, double x2, double y1, double y2) {
  list_.push_back(OGRPoint(x1, y1));
  list_.push_back(OGRPoint(x2, y2));
}

std::string OGRCurve::ToString() const {
  std::string result = "(";
  result +=
      DoubleToString(list_[0].GetX()) + " " + DoubleToString(list_[0].GetY());
  for (size_t i = 1; i < list_.size(); i++) {
    result += ", " + DoubleToString(list_[i].GetX()) + " " + DoubleToString(list_[i].GetY());
  }
  result += ")";
  return result;
}

const std::vector<OGRPoint> &OGRCurve::GetList() { return list_; }

OGRCurve *OGRCurve::Clone() const { return new OGRCurve(list_); }
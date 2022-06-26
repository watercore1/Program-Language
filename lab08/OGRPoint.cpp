#include "OGRPoint.h"

void OGRPoint::ImportFromWkt(const char *filepath) {
  std::ifstream fin;
  fin.open(filepath);  // 读取文件
  std::string temp_line;
  std::getline(fin, temp_line);
  std::smatch result;
  std::regex pattern("Point \\((-?\\d+(\\.\\d+)?) (-?\\d+(\\.\\d+)?)\\)");

  if (std::regex_match(temp_line, result, pattern)) {
    x_ = std::atof(result[1].str().c_str());
    y_ = std::atof(result[3].str().c_str());
  }
}

void OGRPoint::ExportToWkt(const char *filepath) const {
  std::ofstream fout;
  fout.open(filepath);
  fout << "Point (" + DoubleToString(x_) + " " + DoubleToString(y_) + ")\n\r";
  fout.close();
}

bool OGRPoint::IsEmpty() const {
  return x_ == (std::numeric_limits<double>::max)() &&
         y_ == (std::numeric_limits<double>::max)();
}

void OGRPoint::GetMBR(double &x_min, double &y_min, double &x_max,
                      double &y_max) const {
  x_min = x_;
  y_min = y_;
  x_max = x_;
  y_max = y_;
}

void OGRPoint::Clone(const OGRPoint &other) {
  x_ = other.x_;
  y_ = other.y_;
}

OGRPoint *OGRPoint::Clone() const { return (new OGRPoint(x_, y_)); }

bool OGRPoint::Equals(const OGRGeometry &object) const {
  const auto *other = dynamic_cast<const OGRPoint *>(&object);
  return Compare(other->x_, x_) == 0 && Compare(other->y_, y_) == 0;
}

double OGRPoint::GetX() const { return x_; }

double OGRPoint::GetY() const { return y_; }

double OGRPoint::Distance(const OGRPoint &other) const {
  return sqrt((x_ - other.x_) * (x_ - other.x_) +
              (y_ - other.y_) * (y_ - other.y_));
}

std::string OGRPoint::ToString() const {
  return "(" + DoubleToString(x_) + " " + DoubleToString(y_) + ")";
}

OGRPoint OGRPoint::operator-(const OGRPoint &other) const {
  return OGRPoint(x_ - other.x_, y_ - other.y_);
}

double OGRPoint::operator^(const OGRPoint &other) const {
  return x_ * other.y_ - y_ * other.x_;
}

double OGRPoint::operator*(const OGRPoint &other) const {
  return x_ * other.x_ + y_ * other.y_;
}

std::pair<OGRPoint, OGRPoint> OGRPoint::GetMBR() const {
  return std::pair<OGRPoint, OGRPoint>(OGRPoint(x_, y_), OGRPoint(x_, y_));
}

bool OGRPoint::operator==(const OGRPoint &other) const {
  return Compare(other.x_, x_) == 0 && Compare(other.y_, y_) == 0;
}

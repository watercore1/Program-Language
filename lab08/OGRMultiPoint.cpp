#include "OGRMultiPoint.h"

void OGRMultiPoint::SetMBR() {
  OGRPoint *real_point = dynamic_cast<OGRPoint *>(list_[0]);
  x_min_ = real_point->GetX();
  x_max_ = real_point->GetX();
  y_min_ = real_point->GetY();
  y_max_ = real_point->GetY();

  for (size_t i = 0; i < list_.size(); i++) {
    OGRPoint *point = dynamic_cast<OGRPoint *>(list_[i]);
    if (point->GetX() < x_min_) x_min_ = point->GetX();
    if (point->GetX() > x_max_) x_max_ = point->GetX();
    if (point->GetY() < y_min_) y_min_ = point->GetY();
    if (point->GetY() > y_max_) y_max_ = point->GetY();
  }
}

void OGRMultiPoint::GetMBR(double &x_min, double &y_min, double &x_max,
                           double &y_max) const {
  x_min = this->x_min_;
  x_max = this->x_max_;
  y_min = this->y_min_;
  y_max = this->y_max_;
  return;
}

std::pair<OGRPoint, OGRPoint> OGRMultiPoint::GetMBR() const {
  if (this->IsEmpty())
    return std::pair<OGRPoint, OGRPoint>(OGRPoint(), OGRPoint());

  return std::pair<OGRPoint, OGRPoint>(OGRPoint(x_min_, y_min_),
                                       OGRPoint(x_max_, y_max_));
}

void OGRMultiPoint::ImportFromWkt(const char *filepath) {
  std::ifstream fin;
  try {
    fin.open(filepath);  // 读取文件
    std::string s;
    std::getline(fin, s);

    std::regex words_regex("-?\\d+(\\.\\d+)?");
    auto words_begin = std::sregex_iterator(s.begin(), s.end(), words_regex);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
      double x = std::atof((*i).str().c_str());
      ++i;
      double y = std::atof((*i).str().c_str());

      list_.push_back(new OGRPoint(x, y));
    }
  } catch (const char *e) {
    std::cerr << e << std::endl;
  }
  SetMBR();
}
void OGRMultiPoint::ExportToWkt(const char *filepath) const {
  std::ofstream fout;
  fout.open(filepath);
  fout << "MultiPoint (";
  for (size_t i = 0; i < list_.size(); i++) {
    if (i != 0) fout << ", ";
    fout << dynamic_cast<OGRPoint *>(list_[i])->ToString();
  }
  fout << ")";
  fout.close();
}

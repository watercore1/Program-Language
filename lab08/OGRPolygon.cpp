#include "OGRPolygon.h"

void OGRPolygon::ImportFromWkt(const char *filepath) {
  std::ifstream fin;

  fin.open(filepath);  // 读取文件
  std::string s, temp_string;
  std::getline(fin, s);
  std::regex words_regex("-?\\d+(\\.\\d+)?");  // 用于匹配一个小数

  for (size_t i = 0; i < s.length(); i++) {
    if (s[i] == '(') {  // 开启一个新temp_string
      temp_string = "";
    } else if (s[i] == ')') {
      if (temp_string.length() != 0) {
        // 此处开始读取坐标序列
        std::vector<OGRPoint> list;
        auto words_begin = std::sregex_iterator(temp_string.begin(),
                                                temp_string.end(), words_regex);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
          double x = std::atof((*i).str().c_str());
          ++i;
          double y = std::atof((*i).str().c_str());
          list.push_back(OGRPoint(x, y));
        }
        if (list.size()) {
          OGRLinearRing new_ring = OGRLinearRing(list);  // 新建一个ring
          this->list_.emplace_back(new_ring);            // 将ring加入list
        }
      }
      temp_string = "";
    } else {
      temp_string += s[i];
    }
  }
}

std::string OGRPolygon::ToString() const {
  std::string s;

  s += "(";
  s += list_[0].ToString();

  for (size_t i = 1; i < list_.size(); i++) {
    s += ", " + list_[i].ToString();
  }

  s += ")";

  return s;
}

void OGRPolygon::ExportToWkt(const char *filepath) const {
  std::ofstream fout(filepath);
  fout << "Polygon ";
  fout << ToString();
  fout.close();
}

double OGRPolygon::GetPerimeter() {
  double perimeter = 0;
  if (list_.empty()) return perimeter;
  for (auto &i : list_) {
    perimeter += i.GetLength();
  }
  return perimeter;
}

bool OGRPolygon::Contains(OGRPoint &other) {
  if (!list_[0].Contains(other)) return false;
  for (size_t i = 1; i < list_.size(); i++) {
    if (list_[i].Contains(other) ||
        list_[i].On(other))  // 如果在环内或环上 说明不在多边形内
      return false;
  }
  return true;
}

bool OGRPolygon::Contains(OGRLineString &other) {
  const std::vector<OGRPoint> &stringlist = other.GetList();
  for (auto i : stringlist) {
    if (Contains(i))
      continue;
    else
      return false;
  }
  return true;
}

bool OGRPolygon::Contains(OGRPolygon &other) {
  const std::vector<OGRLinearRing> &other_list = other.GetList();

  for (auto i : other_list) {
    //由于 ring 继承自 string ，所以使用 Contain 函数判断是否包含 ring
    if (Contains(i))
      continue;
    else
      return false;
  }
  return true;
}

bool OGRPolygon::Intersects(OGRPolygon &other) {
  std::vector<OGRLinearRing> other_list;

  for (size_t i = 0; i < list_.size(); i++) {
    for (size_t j = 0; j < other_list.size(); j++) {
      if (list_[i].Intersects(other_list[j])) return true;
    }
  }

  return false;
}

bool OGRPolygon::Intersects(OGRLineString &other) {
  for (size_t i = 0; i < list_.size(); i++) {
    if (list_[i].Intersects(other))  // 如果相交就返回相交
      return true;
  }

  return false;
}
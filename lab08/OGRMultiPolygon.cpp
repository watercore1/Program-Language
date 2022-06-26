#include "OGRMultiPolygon.h"

void OGRMultiPolygon::ImportFromWkt(const char *filepath) {
  std::ifstream fin;
  fin.open(filepath);  // 读取文件
  std::string s, temp_string;
  std::getline(fin, s);
  std::regex words_regex("-?\\d+(\\.\\d+)?");  // 用于匹配一个小数
  size_t i = 0;
  for (i = 0; i < s.length(); i++) {
    if (s[i] == '(') break;
  }  // 去除第一个括号
  for (i++; i < s.length(); i++) {
    // 一次匹配一个多边形

    std::string ring_string;
    if (s[i] == '(') {  // 发现一个多边形
      std::vector<OGRLinearRing> ring_list;

      while (true) {
        i++;              // 去掉多边形开头的括号
        if (s[i] == '(')  // 发现一个环
        {
          while (s[i] != ')') ring_string += s[i++];  // 将环内元素匹配出来
          std::vector<OGRPoint> list;  // 所有环内坐标放进去

          auto words_begin = std::sregex_iterator(
              ring_string.begin(), ring_string.end(), words_regex);
          auto words_end = std::sregex_iterator();

          for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            double x = std::atof((*i).str().c_str());
            ++i;
            double y = std::atof((*i).str().c_str());

            list.push_back(OGRPoint(x, y));
          }
          if (!list.empty()) {
            OGRLinearRing new_ring = OGRLinearRing(list);  // 新建一个ring
            ring_list.push_back(new_ring);
          }
          i++;  // 跳出环继续遍历
          ring_string = "";
        }

        if (s[i] == ')') {  // 多边形结束
          OGRPolygon polygon = OGRPolygon(ring_list);
          list.push_back(polygon);
          break;
        }
      }
    }
  }
}

void OGRMultiPolygon::ExportToWkt(const char *filepath) const {
  std::ofstream fout;
  fout.open(filepath);
  fout << "MultiPolygon (";
  fout << list[0].ToString();
  for (size_t i = 1; i < list.size(); i++) {
    fout << ", " << list[i].ToString();
  }
  fout << ")";

  fout.close();
}
double OGRMultiPolygon::GetArea() {
  double area = list[0].GetArea();
  for (size_t i = 1; i < list.size(); i++) {
    area += list[i].GetArea();
  }
  return area;
}

double OGRMultiPolygon::GetPerimeter() {
  double perimeter = 0;
  for (auto i : list) {
    perimeter += i.GetPerimeter();
  }
  return perimeter;
}

bool OGRMultiPolygon::Contains(OGRPoint &object) {
  for (auto i : list) {
    if (i.Contains(object)) return true;
  }
  return false;
}

bool OGRMultiPolygon::Contains(OGRLineString &object) {
  for (auto i : list) {
    if (i.Contains(object)) return true;
  }
  return false;
}

bool OGRMultiPolygon::Contains(OGRPolygon &object) {
  for (auto i : list) {
    if (i.Contains(object)) return true;
  }
  return false;
}

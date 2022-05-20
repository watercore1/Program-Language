#ifndef POLYLINE_H
#define POLYLINE_H

#include "point.h"
#include "util.h"

class Polyline {
 public:
  vector<Point> points_;       //折线点坐标
  vector<Point> mark_points_;  // 所有标记点
  Polyline();
  Polyline(vector<Point>& points, char mode, string mark_number);
  string MarkerStr();
  double xmin = 1e10;
  double ymin = 1e10;
  double xmax = -1e10;
  double ymax = -1e10;
  double xlength() const { return xmax - xmin; };
  double ylength() const { return ymax - ymin; };

 private:
  vector<Point> mark_rect_points_;  //所有标记点的标记矩形的左上角坐标
  vector<double> lengths_;          //第i点到第i+1点的距离
  double total_length_ = 0;         //总长度
  char mode_;                       //模式
  string mark_number_;              //标志点数/规定间隔
  void ProcessMarkerPosition();
  void GetTotalLength();
  void Polychotomy();
  Point Linechotomy(Point from, Point to,
                    double len);  // 给定两点，返回from到to方向上距离len的点坐标
  void EquiSpace();
};

#endif  // POLYLINE_H

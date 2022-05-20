#include "polyline.h"

Polyline::Polyline() {}

Polyline::Polyline(vector<Point> &points, char mode, string mark_number)
    : points_(points), mode_(mode), mark_number_(mark_number) {
  ProcessMarkerPosition();
}

string Polyline::MarkerStr() {
  string temp = std::to_string(mark_points_.size()) + "\n";
  for (size_t i = 0; i < this->mark_points_.size(); i++) {
    temp += ' ' + this->mark_points_[i].Str() + "\n";
  }
  return temp;
}

void Polyline::ProcessMarkerPosition() {
  GetTotalLength();
  if (mode_ == 'A') Polychotomy();
  if (mode_ == 'B') EquiSpace();
}

void Polyline::GetTotalLength() {
  for (size_t i = 0; i < points_.size() - 1; i++) {
    lengths_.push_back(TwoPointDistance(points_[i], points_[i + 1]));
    total_length_ += lengths_.back();
  }
  for (size_t i = 0; i < points_.size(); i++) {
    if (points_[i].x_ < xmin) xmin = points_[i].x_;
    if (points_[i].y_ < ymin) ymin = points_[i].y_;
    if (points_[i].x_ > xmax) xmax = points_[i].x_;
    if (points_[i].y_ > ymax) ymax = points_[i].y_;
  }
}

void Polyline::Polychotomy() {
  int n = atoi(mark_number_.c_str());
  double mark_interval = total_length_ / double(n + 1);
  //当在 i->i+1 这一条边上标记时，标记点到 i+1 点的剩余距离
  double remain_length = 0;

  for (size_t i = 0; i < points_.size() - 1; i++) {
    remain_length += lengths_[i];
    while (CompareDouble(remain_length, mark_interval) > 0) {
      remain_length -= mark_interval;
      mark_points_.push_back(
          Linechotomy(points_[i + 1], points_[i], remain_length));
    }
  }
}

Point Polyline::Linechotomy(Point from, Point to, double len) {
  return Point(from.x_ + (to.x_ - from.x_) * len / TwoPointDistance(from, to),
               from.y_ + (to.y_ - from.y_) * len / TwoPointDistance(from, to));
}

void Polyline::EquiSpace() {
  // 两个标注之间的间隔
  double mark_interval = atof(mark_number_.c_str());
  // 如果间隔大于总长度，则无法标注
  if (mark_interval > total_length_) {
    return;
  }
  // 两边应空出的距离
  double padding_length = fmod(total_length_, mark_interval) / 2;
  if (CompareDouble(padding_length, 0.0) == 0) {
    padding_length += mark_interval / 2;
  }
  // 找到第一个标记点所在的边的起始点 start
  size_t start = 0;
  double remain_length_start = lengths_[start];
  while (remain_length_start < padding_length) {
    start++;
    remain_length_start += lengths_[start];
  }
  remain_length_start -= padding_length;
  Point start_point =
      Linechotomy(points_[start + 1], points_[start], remain_length_start);
  //加入第一个标记点
  mark_points_.push_back(start_point);
  // 找到最后一个标记点所在的边的起始点 end
  size_t end = points_.size() - 2;
  double remain_length_end = lengths_[end];
  while (remain_length_end < padding_length) {
    end--;
    remain_length_end += lengths_[end];
  }
  remain_length_end -= padding_length;
  Point end_point =
      Linechotomy(points_[end], points_[end + 1], remain_length_end);
  // 开始遍历起点到终点的每一条边
  // 起点和终点在同一边的情况要特殊讨论
  if (start == end) {
    double remain_length =
        remain_length_start + remain_length_end - lengths_[start];
    while (CompareDouble(remain_length, mark_interval) > 0) {
      remain_length -= mark_interval;
      mark_points_.push_back(
          Linechotomy(end_point, start_point, remain_length));
    }
  }
  // 一般情况
  else {
    vector<double> temp_lengths = lengths_;
    temp_lengths[start] = remain_length_start;
    temp_lengths[end] = remain_length_end;
    vector<Point> temp_points = points_;
    temp_points[start] = start_point;
    temp_points[end + 1] = end_point;
    double remain_length = 0;
    for (size_t i = start; i <= end; i++) {
      remain_length += temp_lengths[i];
      while (CompareDouble(remain_length, mark_interval) > 0) {
        remain_length -= mark_interval;
        mark_points_.push_back(
            Linechotomy(temp_points[i + 1], temp_points[i], remain_length));
      }
    }
  }
  // 加入最后一个标记点
  mark_points_.push_back(end_point);
}

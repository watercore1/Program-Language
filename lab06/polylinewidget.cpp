#include "polylinewidget.h"

PolylineWidget::PolylineWidget(QWidget *parent) : QWidget{parent} { scale = 1; }

void PolylineWidget::GetPolyline(const Polyline &polyline_) {
  polyline = polyline_;
  // 确定比例尺
  double x_scale = width() / (polyline.xlength() + 40);
  double y_scale = height() / (polyline.ylength() + 40);
  scale = min(x_scale, y_scale);
  HasGetPolyline = true;
  update();
}

void PolylineWidget::PaintPoint(QPainter *painter, const Point &point) {
  painter->setPen(QColor("blue"));
  painter->drawEllipse(QPoint(scale * point.x_, scale * point.y_), 10, 10);
}

void PolylineWidget::PaintMarker(QPainter *painter, const Point &point) {
  painter->setPen(QColor("green"));
  painter->drawRect(scale * point.x_, scale * (point.y_ - 20), scale * 20,
                    scale * 20);
}

void PolylineWidget::PaintLine(QPainter *painter, const Point &point1,
                               const Point &point2) {
  painter->setPen(QColor("black"));
  QPoint p1(scale * point1.x_, scale * point1.y_);
  QPoint p2(scale * point2.x_, scale * point2.y_);
  painter->drawLine(p1, p2);
}

void PolylineWidget::paintEvent(QPaintEvent *) {
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
  if (!HasGetPolyline) return;
  p.setWindow(polyline.xmin * scale - 0.2 * width(),
              polyline.ymax * scale + 0.2 * height(), width(), -height());
  // 绘制折线
  size_t i = 0;
  for (; i < polyline.points_.size() - 1; i++) {
    PaintPoint(&p, polyline.points_[i]);
    PaintLine(&p, polyline.points_[i], polyline.points_[i + 1]);
  }
  PaintPoint(&p, polyline.points_[i]);
  //  绘制注记
  for (size_t j = 0; j < polyline.mark_points_.size(); j++) {
    PaintMarker(&p, polyline.mark_points_[j]);
  }
}

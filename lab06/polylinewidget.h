#ifndef POLYLINEWIDGET_H
#define POLYLINEWIDGET_H

#include <QPainter>
#include <QStyleOption>
#include <QWidget>

#include "point.h"
#include "polyline.h"

class PolylineWidget : public QWidget {
  Q_OBJECT
 public:
  explicit PolylineWidget(QWidget* parent = nullptr);
  void GetPolyline(const Polyline& polyline);
  void PaintPoint(QPainter* painter, const Point& point);
  void PaintMarker(QPainter* painter, const Point& point);
  void PaintLine(QPainter* painter, const Point& point1, const Point& point2);
  void PaintPolyLine(QPainter* painter, const Polyline& polyline);
 signals:
 private:
  double scale;       //比例尺
  Polyline polyline;  //准备画的折线
  bool HasGetPolyline;

 protected:
  void paintEvent(QPaintEvent*);
};

#endif  // POLYLINEWIDGET_H

#ifndef OGR_GEOMETRY_OGR_POINT_H
#define OGR_GEOMETRY_OGR_POINT_H

#include "OGRGeometry.h"

//简单点类
class OGRPoint : public OGRGeometry {
 protected:
  double x_;
  double y_;

 public:
  OGRPoint() {
    x_ = (std::numeric_limits<double>::max)();
    y_ = (std::numeric_limits<double>::max)();
  }
  OGRPoint(double x, double y) {
    x_ = x;
    y_ = y;
  }

  /*override 标识的子函数，表示必须覆盖父函数
  即子函数的参数列表必须与父函数相同*/
  OGRGeometryType GetGeometryType() const override {
    return OGRGeometryType::OGR_POINT;
  }

  bool IsEmpty() const;
  void GetMBR(double &x_min, double &y_min, double &x_max,
              double &y_max) const override;  // 将多边形边界赋值给四个参数
  void ImportFromWkt(const char *filepath) override;
  void ExportToWkt(const char *filepath) const override;
  OGRPoint *Clone() const override;
  std::string ToString() const override;  // 用于构造点的输出格式

  std::pair<OGRPoint, OGRPoint> GetMBR() const;  // 用std::pair实现返回外包矩形
  void Clone(const OGRPoint &other);
  bool Equals(const OGRGeometry &object) const override;
  double GetX() const;
  double GetY() const;
  double Distance(const OGRPoint &other) const;

  OGRPoint operator-(const OGRPoint &other) const;  // 坐标相减
  double operator*(const OGRPoint &other) const;    // 点乘
  double operator^(const OGRPoint &other) const;    // 叉乘
  bool operator==(const OGRPoint &other) const;     // 判断两个点相等
};

#endif  // OGR_GEOMETRY_OGR_POINT_H

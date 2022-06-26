#ifndef OGR_GEOMETRY_OGR_CURVE_H_
#define OGR_GEOMETRY_OGR_CURVE_H_
#include <utility>

#include "OGRGeometry.h"
#include "OGRPoint.h"

// 折线类
class OGRCurve : public OGRGeometry {
 protected:
  std::vector<OGRPoint> list_;

 public:
  OGRCurve() = default;
  // 直接移动 list 的内容到 list_ 处，而不是复制
  OGRCurve(std::vector<OGRPoint> list) : list_(std::move(list)) {}
  OGRCurve(double x1, double x2, double y1, double y2);

  virtual OGRGeometryType GetGeometryType() const override {
    return OGRGeometryType::OGR_CURVE;
  }

  bool IsEmpty() const override;

  void GetMBR(double &x_min, double &y_min, double &x_max,
              double &y_max) const override;
  virtual std::pair<OGRPoint, OGRPoint> GetMBR() const;

  void Clone(OGRCurve &other);
  OGRCurve *Clone() const override;
  //由于不使用 OGR_CURVE 对象，所以不实现 Wkt
  void ImportFromWkt(const char *filepath) override{};
  void ExportToWkt(const char *filepath) const override{};
  bool Equals(const OGRGeometry &object) const;

  std::string ToString() const override;
  const std::vector<OGRPoint> &GetList();
  virtual double GetLength() const { return 0; };
};

#endif  // OGR_GEOMETRY_OGR_CURVE_H_

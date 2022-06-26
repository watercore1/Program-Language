#ifndef OGR_GEOMETRY_OGR_CURVE_POLYGON_H
#define OGR_GEOMETRY_OGR_CURVE_POLYGON_H
#include <utility>

#include "OGRLinearRing.h"
#include "OGRSurface.h"

//环组成的多边形
//第一个环为外环，后面可能的环都是内环
class OGRCurvePolygon : public OGRSurface {
 protected:
  std::vector<OGRLinearRing> list_;

 public:
  OGRCurvePolygon() = default;
  explicit OGRCurvePolygon(std::vector<OGRLinearRing> list) {
    list_ = std::move(list);
  }

  OGRGeometryType GetGeometryType() const override {
    return OGRGeometryType::OGR_CURVE_POLYGON;
  }

  bool IsEmpty() const override { return list_.empty(); }

  void GetMBR(double &XMin, double &YMin, double &XMax,
              double &YMax) const override;
  virtual std::pair<OGRPoint, OGRPoint> GetMBR();

  OGRCurvePolygon *Clone() const override;
  void Clone(OGRCurvePolygon &other);
  double GetArea() const override;
  bool Equals(const OGRCurvePolygon &other) const;

  const std::vector<OGRLinearRing> &GetList();

  void ImportFromWkt(const char *filepath) override{};
  void ExportToWkt(const char *filepath) const override{};
  std::string ToString() const override { return ""; };
};

#endif  // OGR_GEOMETRY_OGR_CURVE_POLYGON_H

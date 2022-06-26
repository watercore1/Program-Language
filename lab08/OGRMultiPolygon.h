#ifndef OGR_GEOMETRY_OGR_MULTI_POLYGON_H_
#define OGR_GEOMETRY_OGR_MULTI_POLYGON_H_
#include "OGRMultiSurface.h"

class OGRMultiPolygon : public OGRMultiSurface {
 protected:
  std::vector<OGRPolygon> list;

 public:
  OGRGeometryType GetGeometryType() const override {
    return OGRGeometryType::OGR_MULTI_POLYGON;
  }

  void ImportFromWkt(const char *filepath) override;
  std::string ToString() const override { return ""; };
  void ExportToWkt(const char *filepath) const override;

  double GetArea();
  //获取总周长
  double GetPerimeter();

  bool Contains(OGRPoint &object);
  bool Contains(OGRLineString &object);
  bool Contains(OGRPolygon &object);
  virtual void GetMBR(double &x_min, double &y_min, double &x_max,
                      double &y_max) const {};
  OGRMultiPolygon *Clone() const { return new OGRMultiPolygon(); };
};

#endif  // OGR_GEOMETRY_OGR_MULTI_POLYGON_H_

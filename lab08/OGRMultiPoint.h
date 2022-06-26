#ifndef OGR_GEOMETRY_OGR_MULTI_POINT_H
#define OGR_GEOMETRY_OGR_MULTI_POINT_H
#include "OGRGeometryCollection.h"
#include "OGRPoint.h"

class OGRMultiPoint : public OGRGeometryCollection {
 protected:
 public:
  OGRMultiPoint() = default;

  OGRGeometryType GetGeometryType() const override {
    return OGRGeometryType::OGR_MULTI_POINT;
  }

  void SetMBR();
  std::pair<OGRPoint, OGRPoint> GetMBR() const;
  void GetMBR(double &XMin, double &YMin, double &XMax,
              double &YMax) const override;

  void ImportFromWkt(const char *filepath) override;
  std::string ToString() const override { return ""; };
  void ExportToWkt(const char *filepath) const override;
};

#endif  // OGR_GEOMETRY_OGR_MULTI_POINT_H

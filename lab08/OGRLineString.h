#ifndef OGR_GEOMETRY_OGR_LINE_STRING_H
#define OGR_GEOMETRY_OGR_LINE_STRING_H

#include <utility>

#include "OGRSimpleCurve.h"

class OGRLineString : public OGRSimpleCurve {
 public:
  OGRLineString() = default;
  OGRLineString(std::vector<OGRPoint> list) { list_ = std::move(list); }

  OGRGeometryType GetGeometryType() const override {
    return OGRGeometryType::OGR_LINE_STRING;
  }

  double GetLength() const override;

  virtual bool Intersects(OGRLineString &other);

  void Clone(OGRLineString &other);

  OGRLineString *Clone() const override;
};

#endif  // OGR_GEOMETRY_OGR_LINE_STRING_H

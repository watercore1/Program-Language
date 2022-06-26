#ifndef OGR_GEOMETRY_OGR_MULTI_CURVE_H_
#define OGR_GEOMETRY_OGR_MULTI_CURVE_H_
#include "OGRGeometryCollection.h"

class OGRMultiCurve : public OGRGeometryCollection {
 public:
  OGRGeometryType GetGeometryType() const override {
    return OGRGeometryType::OGR_MULTI_CURVE;
  }
};

#endif  // OGR_GEOMETRY_OGR_MULTI_CURVE_H

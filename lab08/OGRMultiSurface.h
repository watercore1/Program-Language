#ifndef OGR_GEOMETRY_OGR_MULTI_SURFACE_H_
#include "OGRGeometryCollection.h"

class OGRMultiSurface : public OGRGeometryCollection {
 public:
  OGRGeometryType GetGeometryType() const override {
    return OGRGeometryType::OGR_MULTI_SURFACE;
  }
};

#endif  // OGR_GEOMETRY_OGR_MULTI_SURFACE_H_

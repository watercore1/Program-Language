#ifndef OGR_GEOMETRY_OGR_MULTI_LINE_STRING_H_
#define OGR_GEOMETRY_OGR_MULTI_LINE_STRING_H_
#include "OGRMultiCurve.h"

class OGRMultiLineString : public OGRMultiCurve {
 public:
  OGRGeometryType GetGeometryType() const override {
    return OGRGeometryType::MULTI_LINE_STRING;
  }
  double GetLength() const;
};

#endif  // OGR_GEOMETRY_OGR_MULTI_LINE_STRING_H_

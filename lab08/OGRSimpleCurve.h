
#ifndef OGR_GEOMETRY_OGR_SIMPLE_CURVE_H
#define OGR_GEOMETRY_OGR_SIMPLE_CURVE_H

#include "OGRCurve.h"
//简单折线类
class OGRSimpleCurve : public OGRCurve{
public:
    virtual OGRGeometryType GetGeometryType() const override { return OGRGeometryType::OGR_SIMPLE_CURVE; }
};


#endif //OGR_GEOMETRY_OGR_SIMPLE_CURVE_H

#ifndef OGR_GEOMETRY_OGR_SURFACE_H
#define OGR_GEOMETRY_OGR_SURFACE_H
#include "OGRGeometry.h"
#include "OGRPoint.h"

//面要素的抽象基类
class OGRSurface : public OGRGeometry{
public:
    OGRGeometryType GetGeometryType() const override { return OGRGeometryType::OGR_SURFACE;}
    virtual double GetArea() const=0;
};


#endif //OGR_GEOMETRY_OGR_SURFACE_H
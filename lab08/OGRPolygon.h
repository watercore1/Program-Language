#ifndef OGR_GEOMETRY_OGR_POLYGON_H_
#define OGR_GEOMETRY_OGR_POLYGON_H_
#include <utility>

#include "OGRCurvePolygon.h"

class OGRPolygon : public OGRCurvePolygon{
protected:

public:
    OGRPolygon() = default;
    OGRPolygon(std::vector<OGRLinearRing> list) { list_ = std::move(list); }

    OGRGeometryType GetGeometryType() const override{ return OGRGeometryType::OGR_POLYGON; }
    
    void ImportFromWkt(const char * filepath)override;
    std::string ToString()const override;
    void ExportToWkt(const char * filepath)const override;

    double GetPerimeter();

    bool Contains(OGRPoint & object);
    bool Contains(OGRLineString & object);
    bool Contains(OGRPolygon & object);

    bool Intersects(OGRLineString &object);
    bool Intersects(OGRPolygon &object);

};


#endif //OGR_GEOMETRY_OGR_POLYGON_H_

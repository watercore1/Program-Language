#include "util.h"

#ifndef OGR_GEOMETRY_OGR_GEOMETRY_H
#define OGR_GEOMETRY_OGR_GEOMETRY_H

// Abstract class for all OGR class
class OGRGeometry
{
  protected:
    int id_; // 唯一值
  public:
    OGRGeometry()
    {
        id_ = GetId(); // 获得自己的ID
    }
    virtual ~OGRGeometry() = default;
    virtual const char *GetGeometryType() const
    {
        return "OGRGeometry";
    }
    virtual bool IsEmpty() const
    {
        return true;
    };

    virtual void GetMBR(double &x_min, double &y_min, double &x_max, double &y_max) const
    {
        return;
    };

    virtual void Clone(const OGRGeometry &object);
    virtual OGRGeometry Clone() const;

    virtual bool Equals(const OGRGeometry &object) const;

    int GetID() const
    {
        return id_;
    }

    virtual void ImportFromWkt(const char *filepath){};
    virtual void ExportToWkt(const char *filepath) const {};

    virtual double GetLength() const;

    bool operator==(const OGRGeometry &object) const
    {
        return id_ == object.id_;
    }
};

#endif // OGR_GEOMETRY_OGR_GEOMETRY_H

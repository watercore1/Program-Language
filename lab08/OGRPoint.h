#include "OGRGeometry.h"
#ifndef OGR_GEOMETRY_OGR_POINT_H
#define OGR_GEOMETRY_OGR_POINT_H

class OGRPoint : public OGRGeometry
{
  protected:
    double x_;
    double y_;

  public:
    OGRPoint() 
    {
        x_ = (std::numeric_limits<double>::max)();
        y_ = (std::numeric_limits<double>::max)(); 
    }
    OGRPoint(double x, double y)
    {
        x_ = x;
        y_ = y;
    }

    const char *GetGeometryType() const override
    {
        return "OGRPoint";
    }

    bool IsEmpty() const override;
    void GetMBR(double &x_min, double &y_min, double &x_max,
                double &y_max) const override; // 将多边形边界赋值给四个参数
    std::pair<OGRPoint, OGRPoint> GetMBR();    // 用std::pair实现返回外包矩形
    void Clone(OGRPoint &point2);
    OGRPoint Clone() const override;

    bool Equals(const OGRGeometry &object) const override;
    void ImportFromWkt(const char *filepath) override;
    void ExportToWkt(const char *filepath) const override;

    double GetX() const;
    double GetY() const;

    std::string ToString() const; // 用于构造点的输出格式

    OGRPoint operator-(const OGRPoint &point2) const; // 坐标相减
    double operator*(const OGRPoint &point2) const;   // 点乘
    double operator^(const OGRPoint &point2) const;   // 叉乘
    bool operator==(const OGRPoint &point2) const;    // 判断两个点相等
};

#endif // OGR_GEOMETRY_OGR_POINT_H

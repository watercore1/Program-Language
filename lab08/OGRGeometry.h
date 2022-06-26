#ifndef OGR_GEOMETRY_OGR_GEOMETRY_H
#define OGR_GEOMETRY_OGR_GEOMETRY_H

#include "util.h"

enum OGRGeometryType {
  OGR_GEOMETRY,
  OGR_POINT,
  OGR_CURVE,
  OGR_SIMPLE_CURVE,
  OGR_LINE_STRING,
  OGR_LINEAR_RING,
  OGR_SURFACE,
  OGR_CURVE_POLYGON,
  OGR_POLYGON,
  OGR_GEOMETRY_COLLECTION,
  OGR_MULTI_CURVE,
  MULTI_LINE_STRING,
  OGR_MULTI_POINT,
  OGR_MULTI_SURFACE,
  OGR_MULTI_POLYGON
};

//抽象基类
class OGRGeometry {
 protected:
  unsigned int id_;  // 唯一值
 public:
  /*构造函数*/
  OGRGeometry() { id_ = GenerateId(); }
  virtual ~OGRGeometry() = default;

  /*对于下面的虚函数，子类需要重新定义，
  但是子函数的参数列表与父函数不同，将会隐藏父函数版本，所以此处需要提供这些父函数的定义*/

  virtual bool Equals(const OGRGeometry &other) const;
  virtual void Clone(const OGRGeometry &other);
  virtual bool operator==(const OGRGeometry &other) const {
    return id_ == other.id_;
  }

  /*下面的函数为纯虚函数,子类需要重新定义，
  子函数的参数列表和父函数的参数列表一致，所以此处可以不提供定义*/

  virtual OGRGeometryType GetGeometryType() const {
    return OGRGeometryType::OGR_GEOMETRY;
  };
  virtual bool IsEmpty() const = 0;
  virtual void GetMBR(double &x_min, double &y_min, double &x_max,
                      double &y_max) const {};
  //返回一个本对象的副本的指针，由于协变机制，子函数的返回类型可以和父类不同
  virtual OGRGeometry *Clone() const = 0;
  virtual void ImportFromWkt(const char *filepath){};
  virtual void ExportToWkt(const char *filepath) const {};
  virtual std::string ToString() const { return ""; };

  /*下面的函数，子类不需要重新定义，直接继承就好*/
  int GetID() const { return id_; }
};

#endif  // OGR_GEOMETRY_OGR_GEOMETRY_H

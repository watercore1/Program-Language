#ifndef OGR_GEOMETRY_OGR_GEOMETRY_COLLECTION_H
#define OGR_GEOMETRY_OGR_GEOMETRY_COLLECTION_H
#include "OGRGeometry.h"
#include "OGRLineString.h"
#include "OGRPoint.h"
#include "OGRPolygon.h"

//抽象要素集合
class OGRGeometryCollection : public OGRGeometry {
 protected:
  //只能是以下四类要素
  // Point,line string,linear ring,polygon
  std::vector<OGRGeometry *> list_;
  double x_min_, y_min_, x_max_, y_max_;
  std::vector<OGRGeometry *> GetList() { return list_; }

 public:
  OGRGeometryCollection() = default;
  OGRGeometryCollection(std::vector<OGRGeometry *> list) { this->list_ = list; }
  ~OGRGeometryCollection() = default;
  OGRGeometryType GetGeometryType() const override {
    return OGRGeometryType::OGR_GEOMETRY_COLLECTION;
  }

  virtual void AddGeometry(OGRGeometry &other);
  virtual void RemoveGeometry(int index);
  virtual OGRGeometry *GetGeometry(int index);
  virtual void UpdateGeometry(int index, OGRGeometry &other);
  virtual int GetNumGeometries();

  bool Equals(const OGRGeometry &other);

  void Clone(OGRGeometryCollection &other);
  OGRGeometryCollection *Clone() const override;
  bool IsEmpty() const override;
};

#endif  // OGR_GEOMETRY_OGR_GEOMETRY_COLLECTION_H_

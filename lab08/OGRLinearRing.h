#ifndef OGR_GEOMETRY_OGR_LINEAR_RING_H
#define OGR_GEOMETRY_OGR_LINEAR_RING_H

#include <utility>

#include "OGRLineString.h"

// ring 和 line string 的区别是 list 第一个元素和最后一个元素相连相同
class OGRLinearRing : public OGRLineString {
 private:
  //判断点是否在边 P1-P2 上
  bool OnSegment(OGRPoint P1, OGRPoint P2, OGRPoint Q);

 public:
  OGRGeometryType GetGeometryType() const override {
    return OGRGeometryType::OGR_LINEAR_RING;
  }
  OGRLinearRing() = default;
  OGRLinearRing(std::vector<OGRPoint> list) { list_ = std::move(list); }

  double GetArea() const;
  double GetLength() const override;

  //判断点是否在Ring内部
  bool Contains(const OGRPoint &other);
  //判断点是否在Ring边上
  bool On(const OGRPoint &other);

  bool Intersects(OGRLinearRing &other);
  bool Intersects(OGRLineString &other) override;

  void Clone(OGRLinearRing &other);
  OGRLinearRing *Clone() const override;
};

#endif  // OGR_GEOMETRY_OGR_LINEAR_RING_H

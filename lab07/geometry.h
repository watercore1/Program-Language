#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "util.h"
//抽象基类
class Geometry {
 protected:
  string id_ = "";
  string name_ = "";

 public:
  Geometry() = default;
  Geometry(string id) : id_(id) {}
  string GetID() const { return id_; }
  string GetName() const { return name_; }
  void SetID(const string id) { id_ = id; }
  void SetName(const string name) { name_ = name; }
  virtual string ToString() const = 0;
};

#endif  // GEOMETRY_H_
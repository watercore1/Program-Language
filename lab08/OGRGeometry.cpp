#include "OGRGeometry.h"

bool OGRGeometry::Equals(const OGRGeometry &object) const {
  std::cerr << "Abstract class can't equal!" << std::endl;
  return false;
}

void OGRGeometry::Clone(const OGRGeometry &object) {
  std::cerr << "Abstract class can't clone!" << std::endl;
  return;
}
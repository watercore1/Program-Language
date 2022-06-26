#include "OGRMultiLineString.h"

double OGRMultiLineString::GetLength() const {
  double length = 0.0;
  if (list_.empty()) return length;
  for (auto i : list_) length += dynamic_cast<OGRLineString *>(i)->GetLength();
  return length;
}
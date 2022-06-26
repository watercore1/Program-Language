#include "OGRGeometryCollection.h"

void OGRGeometryCollection::AddGeometry(OGRGeometry &other) {
  OGRGeometry *p = &other;
  if (other.GetGeometryType() == OGR_POINT) {
    list_.push_back((OGRPoint *)p);
  } else if (p->GetGeometryType() == OGR_POLYGON) {
    list_.push_back((OGRPolygon *)p);
  } else if (p->GetGeometryType() == OGR_LINE_STRING) {
    list_.push_back((OGRLineString *)p);
  } else if (p->GetGeometryType() == OGR_LINEAR_RING) {
    list_.push_back((OGRLinearRing *)p);
  }
}

void OGRGeometryCollection::RemoveGeometry(const int index) {
  if (size_t(index) >= list_.size()) {
    std::cerr << "Wrong Index !" << std::endl;
    return;
  }
  //此时只移除指针，并没有释放内存
  list_.erase(list_.begin() + index);
}

OGRGeometry *OGRGeometryCollection::GetGeometry(const int index) {
  return list_[index];
}

void OGRGeometryCollection::UpdateGeometry(const int index,
                                           OGRGeometry &other) {
  list_[index] = &other;
}

int OGRGeometryCollection::GetNumGeometries() { return list_.size(); }

void OGRGeometryCollection::Clone(OGRGeometryCollection &other) {
  std::vector<OGRGeometry *> &other_list = other.list_;
  list_.reserve(other_list.size());
  for (auto i : other_list) {
    if (i->GetGeometryType() == OGR_POINT)  // multipoint
      list_.push_back((((OGRPoint *)i)->Clone()));
    else if (i->GetGeometryType() == OGR_POLYGON)
      list_.push_back((((OGRPolygon *)i)->Clone()));
    else if (i->GetGeometryType() == OGR_LINE_STRING)
      list_.push_back((((OGRLineString *)i)->Clone()));
    else if (i->GetGeometryType() == OGR_LINEAR_RING)
      list_.push_back((((OGRLinearRing *)i)->Clone()));
  }
}

bool OGRGeometryCollection::IsEmpty() const { return list_.empty(); }

bool OGRGeometryCollection::Equals(const OGRGeometry &Sample) {
  auto *other = dynamic_cast<const OGRGeometryCollection *>(&Sample);
  if (list_.size() != other->list_.size()) return false;
  std::vector<bool> map(list_.size(), 0);  //判断 other 中的每一项是否已匹配到
  for (size_t i = 0; i < list_.size(); i++) {  // 遍历每一个点
    for (size_t j = 0; j < other->list_.size(); j++) {
      if (map[j]) continue;
      if (list_[i]->GetGeometryType() != other->list_[j]->GetGeometryType())
        return false;
      else {
        if (other->list_[j]->GetGeometryType() == OGR_POINT) {
          auto *q = dynamic_cast<OGRPoint *>(other->list_[j]);
          if (list_[i]->Equals(*q) && map[j] == 0) {
            map[j] = 1;
            goto a;
          }
        } else if (other->list_[j]->GetGeometryType() == OGR_POLYGON) {
          auto *q = dynamic_cast<OGRPolygon *>(other->list_[j]);
          if (list_[i]->Equals(*q) && map[j] == 0) {
            map[j] = 1;
            goto a;
          }
        } else if (other->list_[j]->GetGeometryType() == OGR_LINE_STRING) {
          auto *q = dynamic_cast<OGRLineString *>(other->list_[j]);
          if (list_[i]->Equals(*q) && map[j] == 0) {
            map[j] = 1;
            goto a;
          }
        } else if (other->list_[j]->GetGeometryType() == OGR_LINEAR_RING) {
          auto *q = dynamic_cast<OGRLinearRing *>(other->list_[j]);
          if (list_[i]->Equals(*q) && map[j] == 0) {
            map[j] = 1;
            goto a;
          }
        } else
          assert(false);
      }
    }
    return false;
  a:
    continue;
  }
  return true;
}

OGRGeometryCollection *OGRGeometryCollection::Clone() const {
  std::vector<OGRGeometry *> new_list;
  new_list.reserve(list_.size());
  for (size_t i = 0; i < list_.size(); i++) {
    new_list.push_back(list_[i]->Clone());
  }

  return new OGRGeometryCollection(new_list);
}
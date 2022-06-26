#include "layers.h"

void Layers::ProcessCommand(const string& command, ofstream& ofs) {
  
  // cout << command << endl;
  //将命令按空格分开
  istringstream command_stream(command);
  //初始化前三个字段
  InitialThreeField(command_stream);

  //首先判断不同的要素类型
  switch (op_type_) {
    case OpType::ADD:
      AddGeoFeature(command_stream);
      break;
    case OpType::DEL:
      DelGeoFeature();
      break;
    case OpType::SET:
      SetGeoFeature(command_stream);
      break;
    case OpType::JUDGE:
      JudgeGeoFeature(command_stream, ofs);
      break;
  }
}

void Layers::InitialThreeField(istringstream& command_stream) {
  //对于所有命令，前三项都是一致的
  string op_type;
  string geo_type;
  command_stream >> op_type >> geo_type >> id_;
  // cout << op_type << "\t" << geo_type << "\t" << id_ << endl;
  //修改当前命令的对应属性
  if (op_type.compare("add") == 0)
    op_type_ = OpType::ADD;
  else if (op_type.compare("del") == 0)
    op_type_ = OpType::DEL;
  else if (op_type.compare("set") == 0)
    op_type_ = OpType::SET;
  else if (op_type.compare("judge") == 0)
    op_type_ = OpType::JUDGE;
  else
    throw(CommandError::INVALID_OPERATOR_TYPE);

  if (geo_type.compare("point") == 0)
    geo_type_ = GeoType::POINT;
  else if (geo_type.compare("polyline") == 0)
    geo_type_ = GeoType::POLYLINE;
  else if (geo_type.compare("ring") == 0)
    geo_type_ = GeoType::RING;
  else if (geo_type.compare("polygon") == 0)
    geo_type_ = GeoType::POLYGON;
  else
    throw(CommandError::INVALID_GEO_TYPE);
}

void Layers::AddGeoFeature(istringstream& sub_command) {
  //由逗号分隔的坐标
  string coordinates_with_comma;
  //如果是多边形，要把 outer 去掉
  if (geo_type_ == GeoType::POLYGON) sub_command >> coordinates_with_comma;
  sub_command >> coordinates_with_comma;
  //由空格分割的坐标
  istringstream coordinates = CommaToSpaceInString(coordinates_with_comma);

  switch (geo_type_) {
    case GeoType::POINT:
      points_.push_back(Point(id_, coordinates));
      break;
    case GeoType::POLYLINE:
      polylines_.push_back(Polyline(id_, coordinates));
      break;
    case GeoType::RING:
      rings_.push_back(Ring(id_, coordinates));
      break;
    case GeoType::POLYGON:
      polygons_.push_back(Polygon(id_, coordinates));
      break;
  }
}

void Layers::DelGeoFeature() {
  switch (geo_type_) {
    case GeoType::POINT: {
      auto itr = find_if(points_.begin(), points_.end(), Compare(id_));
      points_.erase(itr);
      break;
    }

    case GeoType::POLYLINE: {
      auto itr = find_if(polylines_.begin(), polylines_.end(), Compare(id_));
      polylines_.erase(itr);
      break;
    }

    case GeoType::RING: {
      auto itr = find_if(rings_.begin(), rings_.end(), Compare(id_));
      rings_.erase(itr);
      break;
    }

    case GeoType::POLYGON: {
      auto itr = find_if(polygons_.begin(), polygons_.end(), Compare(id_));
      polygons_.erase(itr);
      break;
    }
  }
}
void Layers::SetGeoFeature(istringstream& sub_command) {
  switch (geo_type_) {
    case GeoType::POINT: {
      auto itr = find_if(points_.begin(), points_.end(), Compare(id_));
      SetPointFeature(itr, sub_command);
      break;
    }

    case GeoType::POLYLINE: {
      auto itr = find_if(polylines_.begin(), polylines_.end(), Compare(id_));
      SetPolylineFeature(itr, sub_command);
      break;
    }

    case GeoType::RING: {
      auto itr = find_if(rings_.begin(), rings_.end(), Compare(id_));
      SetRingFeature(itr, sub_command);
      break;
    }

    case GeoType::POLYGON: {
      auto itr = find_if(polygons_.begin(), polygons_.end(), Compare(id_));
      SetPolygonFeature(itr, sub_command);
      break;
    }
  }
}

void Layers::SetPointFeature(vector<Point>::iterator& itr,
                             istringstream& sub_command) {
  string set_type;
  sub_command >> set_type;
  if (set_type.compare("set") == 0) {
    //转换坐标
    string coordinates_with_comma;
    sub_command >> coordinates_with_comma;
    //由空格分割的坐标
    istringstream coordinates = CommaToSpaceInString(coordinates_with_comma);
    itr->SetXY(coordinates);
  } else if (set_type.compare("move") == 0) {
    //转换坐标
    string coordinates_with_comma;
    sub_command >> coordinates_with_comma;
    //由空格分割的坐标
    istringstream coordinates = CommaToSpaceInString(coordinates_with_comma);
    itr->MoveXY(coordinates);
  } else if (set_type.compare("name") == 0) {
    string name;
    sub_command >> name;
    itr->SetName(name);
  } else
    throw(CommandError::INVALID_SUB_SET_TYPE);
}
void Layers::SetPolylineFeature(vector<Polyline>::iterator& itr,
                                istringstream& sub_command) {
  string set_type;
  sub_command >> set_type;
  if (set_type.compare("set") == 0) {
    size_t index;  //要修改的点的索引
    sub_command >> index;
    //转换坐标
    string coordinates_with_comma;
    sub_command >> coordinates_with_comma;
    //由空格分割的坐标
    istringstream coordinates = CommaToSpaceInString(coordinates_with_comma);
    itr->SetPoint(index, coordinates);
  } else if (set_type.compare("move") == 0) {
    size_t index;  //要修改的点的索引
    sub_command >> index;
    //转换坐标
    string coordinates_with_comma;
    sub_command >> coordinates_with_comma;
    //由空格分割的坐标
    istringstream coordinates = CommaToSpaceInString(coordinates_with_comma);
    itr->MovePoint(index, coordinates);
  } else if (set_type.compare("del") == 0) {
    size_t index;  //要修改的点的索引
    sub_command >> index;
    itr->DelPoint(index);
  } else if (set_type.compare("set_length") == 0) {
    string length;
    sub_command >> length;
    itr->SetLength(length);
  } else if (set_type.compare("name") == 0) {
    string name;
    sub_command >> name;
    itr->SetName(name);
  } else
    throw(CommandError::INVALID_SUB_SET_TYPE);
}
void Layers::SetRingFeature(vector<Ring>::iterator& itr,
                            istringstream& sub_command) {
  string set_type;
  sub_command >> set_type;
  if (set_type.compare("set") == 0) {
    size_t index;  //要修改的点的索引
    sub_command >> index;
    //转换坐标
    string coordinates_with_comma;
    sub_command >> coordinates_with_comma;
    //由空格分割的坐标
    istringstream coordinates = CommaToSpaceInString(coordinates_with_comma);
    itr->SetPoint(index, coordinates);
  } else if (set_type.compare("move") == 0) {
    size_t index;  //要修改的点的索引
    sub_command >> index;
    //转换坐标
    string coordinates_with_comma;
    sub_command >> coordinates_with_comma;
    //由空格分割的坐标
    istringstream coordinates = CommaToSpaceInString(coordinates_with_comma);
    itr->MovePoint(index, coordinates);
  } else if (set_type.compare("del") == 0) {
    size_t index;  //要修改的点的索引
    sub_command >> index;
    itr->DelPoint(index);
  } else if (set_type.compare("set_length") == 0) {
    string length;
    sub_command >> length;
    itr->SetLength(length);
  } else if (set_type.compare("set_area") == 0) {
    string area;
    sub_command >> area;
    itr->SetArea(area);
  } else if (set_type.compare("name") == 0) {
    string name;
    sub_command >> name;
    itr->SetName(name);
  } else
    throw(CommandError::INVALID_SUB_SET_TYPE);
}
void Layers::SetPolygonFeature(vector<Polygon>::iterator& itr,
                               istringstream& sub_command) {
  string set_type;
  sub_command >> set_type;
  if (set_type.compare("inner") == 0) {
    //转换坐标
    string coordinates_with_comma;
    sub_command >> coordinates_with_comma;
    //由空格分割的坐标
    istringstream coordinates = CommaToSpaceInString(coordinates_with_comma);
    itr->SetInner(coordinates);
  } else if (set_type.compare("set") == 0) {
    size_t index;  //要修改的点的索引
    sub_command >> index;
    //转换坐标
    string coordinates_with_comma;
    sub_command >> coordinates_with_comma;
    //由空格分割的坐标
    istringstream coordinates = CommaToSpaceInString(coordinates_with_comma);
    string outer_or_inner;
    sub_command >> outer_or_inner;
    if (outer_or_inner.compare("outer") == 0) {
      itr->SetPoint(index, coordinates);
    } else if (outer_or_inner.compare("inner") == 0) {
      itr->SetInnerPoint(index, coordinates);
    } else
      throw(CommandError::INVALID_SUB_SET_TYPE);
  } else if (set_type.compare("move") == 0) {
    size_t index;  //要修改的点的索引
    sub_command >> index;
    //转换坐标
    string coordinates_with_comma;
    sub_command >> coordinates_with_comma;
    //由空格分割的坐标
    istringstream coordinates = CommaToSpaceInString(coordinates_with_comma);
    string outer_or_inner;
    sub_command >> outer_or_inner;
    if (outer_or_inner.compare("outer") == 0) {
      itr->MovePoint(index, coordinates);
    } else if (outer_or_inner.compare("inner") == 0) {
      itr->MoveInnerPoint(index, coordinates);
    } else
      throw(CommandError::INVALID_SUB_SET_TYPE);
  } else if (set_type.compare("del") == 0) {
    size_t index;  //要修改的点的索引
    sub_command >> index;
    string outer_or_inner;
    sub_command >> outer_or_inner;
    if (outer_or_inner.compare("outer") == 0) {
      itr->DelPoint(index);
    } else if (outer_or_inner.compare("inner") == 0) {
      itr->DelInnerPoint(index);
    } else
      throw(CommandError::INVALID_SUB_SET_TYPE);
  } else if (set_type.compare("set_length") == 0) {
    string length;
    sub_command >> length;
    itr->SetLength(length);
  } else if (set_type.compare("set_area") == 0) {
    string area;
    sub_command >> area;
    itr->SetArea(area);
  } else if (set_type.compare("name") == 0) {
    string name;
    sub_command >> name;
    itr->SetName(name);
  } else
    throw(CommandError::INVALID_SUB_SET_TYPE);
}

void Layers::JudgeGeoFeature(istringstream& sub_command, ofstream& ofs) {
  switch (geo_type_) {
    case GeoType::POINT: {
      string id2;
      sub_command >> id2 >> id2;
      auto itr1 = find_if(points_.begin(), points_.end(), Compare(id_));
      auto itr2 = find_if(points_.begin(), points_.end(), Compare(id2));
      if (*itr1 == *itr2)
        ofs << "True" << endl;
      else
        ofs << "False" << endl;
      break;
    }

    case GeoType::POLYLINE: {
      throw(CommandError::INVALID_JUDGE_TYPE);
      break;
    }

    case GeoType::RING: {
      string id2;
      sub_command >> id2 >> id2;
      auto itr1 = find_if(rings_.begin(), rings_.end(), Compare(id_));
      auto itr2 = find_if(points_.begin(), points_.end(), Compare(id2));
      if (itr1->CoverPoint(*itr2))
        ofs << "True" << endl;
      else
        ofs << "False" << endl;
      break;
    }

    case GeoType::POLYGON: {
      string id2;
      sub_command >> id2 >> id2;
      auto itr1 = find_if(polygons_.begin(), polygons_.end(), Compare(id_));
      auto itr2 = find_if(points_.begin(), points_.end(), Compare(id2));
      if (itr1->CoverPoint(*itr2))
        ofs << "True" << endl;
      else
        ofs << "False" << endl;
      break;
    }
  }
}

void Layers::PrintToFile(ofstream& ofs) const {
  for (size_t i = 0; i < points_.size(); i++) {
    ofs << points_[i];
  }
  for (size_t i = 0; i < polylines_.size(); i++) {
    ofs << polylines_[i];
  }
  for (size_t i = 0; i < rings_.size(); i++) {
    ofs << rings_[i];
  }
  for (size_t i = 0; i < polygons_.size(); i++) {
    ofs << polygons_[i];
  }
}
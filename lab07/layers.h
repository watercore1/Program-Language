#ifndef LAYERS_H_
#define LAYERS_H_

#include "polygon.h"

enum GeoType { POINT, POLYLINE, RING, POLYGON };
enum OpType { ADD, DEL, SET, JUDGE };
enum CommandError {
  INVALID_OPERATOR_TYPE,
  INVALID_GEO_TYPE,
  INVALID_SUB_SET_TYPE,
  INVALID_JUDGE_TYPE
};

class Layers {
 private:
  vector<Point> points_;
  vector<Polyline> polylines_;
  vector<Ring> rings_;
  vector<Polygon> polygons_;

  //所有命令中的前三个字段都相同

  OpType op_type_;    //当前命令的操作类型
  GeoType geo_type_;  //当前命令的要素类型
  string id_;         //当前命令的 id
  //初始化上面三个字段
  void InitialThreeField(istringstream& command);
  
  //接着解析剩下的命令

  //加入要素
  void AddGeoFeature(istringstream& sub_command);
  //删除要素
  void DelGeoFeature();
  //设置要素
  void SetGeoFeature(istringstream& sub_command);
  //判断要素
  void JudgeGeoFeature(istringstream& sub_command, ofstream& ofs);

  //设置要素函数太复杂了，再分为这几个辅助函数
  //这几个辅助函数中存在大量的代码冗余，怎么修改比较好呢？。。

  //设置点要素
  void SetPointFeature(vector<Point>::iterator& itr,
                       istringstream& sub_command);
  //设置折线要素
  void SetPolylineFeature(vector<Polyline>::iterator& itr,
                          istringstream& sub_command);
                        //设置环要素
  void SetRingFeature(vector<Ring>::iterator& itr, istringstream& sub_command);
  //设置多边形要素
  void SetPolygonFeature(vector<Polygon>::iterator& itr,
                         istringstream& sub_command);

 public:
  Layers() = default;
  //处理一行命令，并输出判断值到文件中
  void ProcessCommand(const string& command, ofstream& ofs);
  //输出所有要素到文件中
  void PrintToFile(ofstream& ofs) const;
};

//函数对象，
class Compare {
 private:
  string id_;

 public:
  Compare(string id = "") : id_(id) {}
  //重载()，进行判断
  //基类指针可以指向派生类对象
  bool operator()(const Geometry& g) { return id_.compare(g.GetID()) == 0; }
};

#endif  // LAYERS_H_H
#include "layers.h"

int main() {
  //打开输入文件
  ifstream ifs;
  ofstream ofs;
  OpenFile(ifs, ofs);
  //新建图层
  Layers layers;
  //逐行读取文件
  string command;
  while (!ifs.eof()) {
    getline(ifs, command);
    layers.ProcessCommand(command, ofs);
  }
  ifs.close();
  layers.PrintToFile(ofs);  //输出所有要素
  ofs.close();
  return 0;
}

#ifndef UTIL_H_
#define UTIL_H_
//一些通用工具

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

//判断两个 double 数是否相等
bool IsDoubleEqual(double a, double b);

//判断点 (x0,y0) 是否在线段上
bool IsPointOnLine(double x0, double y0, double x1, double y1, double x2, double y2);

//判断两条线段是否相交
bool IsIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);

//提示用户键入 输入文件 和 输出文件 的名字直到成功打开
void OpenFile(ifstream& ifs,ofstream& ofs);

//将 string 中的逗号转为空格
istringstream CommaToSpaceInString(const string& s);

#endif // UTIL_H_

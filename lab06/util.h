#ifndef UTIL_H
#define UTIL_H

#include <io.h>

#include <string>
#include <vector>
using namespace std;
/**
 * @brief 给定路径，返回当前路径下的所有同类型文件（不包括子文件夹）
 * @param 路径
 * @param 文件列表
 * @param 后缀格式
 */
void GetAllFormatFiles(string path, vector<string>& files, string format);

/**
 * @brief 比较两个double类型的大小，a大返回1，b大返回-1，相等返回0；
 * @param a
 * @param b
 * @return
 */
int CompareDouble(double a, double b);

#endif  // UTIL_H

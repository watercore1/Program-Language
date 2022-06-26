#ifndef OGR_GEOMETRY_UTIL_H
#define OGR_GEOMETRY_UTIL_H

#include <assert.h>
#include <algorithm>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <stack>
#include <vector>

//生成唯一值 id
int GenerateId();

/**
 * @brief Compare the size of two double number
 * @return int
 * if a>b return 1;
 * if a==b return 0;
 * if a<b return -1;
 */
int Compare(double a, double b);

//保留两位小数
std::string DoubleToString(const double n);

#endif  // OGR_GEOMETRY_UTIL_H

#ifndef OGR_GEOMETRY_UTIL_H
#define OGR_GEOMETRY_UTIL_H

#include <algorithm>
#include <assert.h>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <stack>
#include <vector>

/**
 * @description: 获取唯一值id
 * @return {int} 唯一值id
 */
int GetId();

/**
 * @description: 比较两个 double 值的大小
 * @param a
 * @param b=0
 * @return a大于b返回1,b大于a返回-1,相等返回0
 */
int Compare(double a, double b = 0.);

#endif // OGR_GEOMETRY_UTIL_H

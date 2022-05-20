#include <vector>

#include "bignumber.h"
using std::vector;

// 矩阵乘法
vector<vector<BigNumber>> multiply(vector<vector<BigNumber>> &a,
                                   vector<vector<BigNumber>> &b) {
  vector<vector<BigNumber>> c(2, vector<BigNumber>(2));
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j];
    }
  }
  return c;
}

// 矩阵快速幂
vector<vector<BigNumber>> matrixPow(vector<vector<BigNumber>> a, int n) {
  vector<vector<BigNumber>> ret = {{1, 0}, {0, 1}}; //矩阵的 0 次方，单位矩阵
  while (n > 0) {
    if ((n & 1) == 1) { // n%2 == 1
      ret = multiply(ret, a);
    }
    n >>= 1; // n = n/2
    a = multiply(a, a);
  }
  return ret;
}

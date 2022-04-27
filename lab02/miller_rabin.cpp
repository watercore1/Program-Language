typedef long double ld;
typedef unsigned long long ull;

ull qmul(ull a, ull b, ull mod)  //快速乘
{
  ull c = (ld)a / mod * b;
  ull res = a * b - c * mod;
  return (res + mod) % mod;
}
ull qpow(ull a, ull n, ull mod)  //快速幂
{
  ull res = 1;
  while (n) {
    if (n & 1) res = qmul(res, a, mod);
    a = qmul(a, a, mod);
    n >>= 1;
  }
  return res;
}
bool MRtest(ull n)  // Miuller Rabin Test
{
  if (n < 3 || n % 2 == 0) return n == 2;  //特判
  ull u = n - 1, t = 0;
  while (u % 2 == 0) u /= 2, ++t;
  ull ud[] = {2, 7, 61};
  for (ull a : ud) {
    ull v = qpow(a, u, n);
    if (v == 1 || v == n - 1 || v == 0) continue;
    for (ull j = 1; j <= t; j++) {
      v = qmul(v, v, n);
      if (v == n - 1 && j != t) {
        v = 1;
        break;
      }                      //出现一个n-1，后面都是1，直接跳出
      if (v == 1) return 0;  //这里代表前面没有出现n-1这个解，二次检验失败
    }
    if (v != 1) return 0;  // Fermat检验
  }
  return 1;
}

#include "util.h"

const double eps = 1e-8;  // double precision

void GetAllFormatFiles(string path, vector<string>& files, string format) {
  //文件句柄
  long long hFile = 0;
  //文件信息
  struct _finddata_t fileinfo;
  string p;
  if ((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(),
                          &fileinfo)) != -1)  // 找到第一个*.format结尾的文件
  {
    do {
      if ((fileinfo.attrib & _A_SUBDIR)) {
        continue;  // 跳过子目录
      }

      else {
        files.push_back(fileinfo.name);
      }
    } while (_findnext(hFile, &fileinfo) == 0);  // 遍历所有文件

    _findclose(hFile);
  }
}

int CompareDouble(double a, double b) {
  // a 比 b 大返回 1
  if ((a - b) - eps > 0)  // 如果减去eps还比0大那才是真的大
    return 1;
  // b 比 a 大返回 -1
  if ((b - a) - eps > 0)  // 同上
    return -1;
  // 相等返回 0
  return 0;
}

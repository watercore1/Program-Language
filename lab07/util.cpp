#include "util.h"

const double eps = 1e-10;  // double 精度为 1e-15

bool IsDoubleEqual(double a, double b) {
  if (abs(a - b) < eps)
    return true;
  else
    return false;
}

bool IsPointOnLine(double x0, double y0, double x1, double y1, double x2,
                   double y2) {
  bool flag = false;
  double d1 = (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);  //交叉相乘
  if ((abs(d1) < eps) && ((x0 - x1) * (x0 - x2) <= 0) &&
      ((y0 - y1) * (y0 - y2) <= 0)) {
    flag = true;
  }
  return flag;
}

bool IsIntersect(double x1, double y1, double x2, double y2, double x3,
                 double y3, double x4, double y4) {
  bool flag = false;
  double d = (x2 - x1) * (y4 - y3) - (y2 - y1) * (x4 - x3);
  //如果两条线段不共线
  if (d != 0) {
    //两条线段相交表示互相跨立
    double r = ((y1 - y3) * (x4 - x3) - (x1 - x3) * (y4 - y3)) / d;
    double s = ((y1 - y3) * (x2 - x1) - (x1 - x3) * (y2 - y1)) / d;
    if ((r >= 0) && (r <= 1) && (s >= 0) && (s <= 1)) {
      flag = true;
    }
  }
  return flag;
}

void OpenFile(ifstream& ifs, ofstream& ofs) {
  //打开输入文件
  cout << "please enter the input file name:";
  string input_filename;
  cin >> input_filename;
  ifs.open(input_filename);
  while (!ifs.is_open()) {
    cerr << "Can't Open file" << input_filename << endl;
    cout << "please enter the input file name:";
    cin >> input_filename;
    ifs.open(input_filename);
  }

  //打开输出文件
  cout << "please enter the output file name:";
  string output_filename;
  cin >> output_filename;
  ofs.open(output_filename);
  while (!ifs.is_open()) {
    cerr << "Can't Open file" << output_filename << endl;
    cout << "please enter the output file name:";
    cin >> output_filename;
    ofs.open(output_filename);
  }
  return;
}

istringstream CommaToSpaceInString(const string& s) {
  string temp = s;
  for (size_t i = 0; i < s.size(); i++) {
    if (temp[i] == ',') {
      temp[i] = ' ';
    }
  }
  return istringstream(temp);
}
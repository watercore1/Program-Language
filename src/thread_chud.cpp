#include "thread_chud.h"

ThreadChud::ThreadChud(QObject *parent) : QThread{parent} {}

void ThreadChud::SetNumItems(int n) {
  num_items = n;
  precision = 15 * n;
}

void ThreadChud::run() {
  BigFloat sqrt_const(
      "42698670."
      "666333395817712889160659608273320884002509082800838007178852605157457594"
      "216301799911455668601345737167494080411392292736181266728193136882170582"
      "563460066798766483460795735983552333985484854583276247377491250754585032"
      "578219745675991212400392015323321276835446296485837355697306012123458758"
      "0491");
  sqrt_const.SetPrecision(precision);
  const BigFloat down_const(640320LL * 640320LL * 640320LL);

  // 第0次迭代
  BigFloat up_ff = 1LL;
  long long up_c = 13591409LL;
  BigFloat down_fe = 1LL;
  BigFloat down_ee = 1LL;
  BigFloat ans = BigFloat::PrecDiv(up_ff * BigFloat(up_c),
                                   BigFloat(down_fe) * down_ee, precision);

  for (int i = 1; i < num_items; ++i) {
    emit SendProgress(i * 100 / num_items);
    up_ff = FactorialFraction(i);
    up_c += 545140134LL;
    down_fe = down_fe * i * i * i;
    down_ee = down_ee * down_const;

    if (i % 2 == 0) {
      ans = ans + BigFloat::PrecDiv(up_ff * BigFloat(up_c), down_fe * down_ee,
                                    2 * precision);
    } else {
      ans = ans - BigFloat::PrecDiv(up_ff * BigFloat(up_c), down_fe * down_ee,
                                    2 * precision);
    }
    ans.LeadTrim();
  }

  BigFloat pi = BigFloat::PrecDiv(sqrt_const, ans, precision);
  emit SendProgress(100);
  emit SendPi(AddSpaceInQString(QString::fromStdString(pi.ToString())));
}

BigFloat ThreadChud::FactorialFraction(int i) {
  BigFloat ans(1);

  for (int j = 3 * i + 1; j <= 6 * i; ++j) {
    ans = ans * j;
  }

  return ans;
}

QString ThreadChud::AddSpaceInQString(QString str) {
  int n = str.length() - 2;
  n = n / 5 * 5 - 3;
  while (n > 3) {
    str.insert(n, " ");
    n -= 5;
  }
  return str;
}

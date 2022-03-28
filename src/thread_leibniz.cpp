#include "thread_leibniz.h"

ThreadLeibniz::ThreadLeibniz(QObject *parent) : QThread{parent} {}

void ThreadLeibniz::SetNumItems(long long n) { num_items = n; }

void ThreadLeibniz::run() {
  // PI/4 = 1/1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11
  double pi = 1;
  double stage_process = num_items / 100.0;
  for (long long i = 1, j = 0; i < num_items; ++i, ++j) {
    // 每完成百分之一都发送进度
    if (j >= stage_process) {
      emit SendProgress(i / stage_process);
      j = 0;
    }
    if (i % 2 == 0) {
      pi += 1.0 / (2 * i + 1);
    } else {
      pi -= 1.0 / (2 * i + 1);
    }
  }
  pi *= 4;
  emit SendProgress(100);
  emit SendPi(pi);
}

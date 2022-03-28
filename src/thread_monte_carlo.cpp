#include "thread_monte_carlo.h"

ThreadMonteCarlo::ThreadMonteCarlo(QObject *parent) : QThread{parent} {}

void ThreadMonteCarlo::SetNumPoints(long long n) { num_points = n; }

void ThreadMonteCarlo::run() {
  std::mt19937 generator(time(0));
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  long long numIn = 0;
  double stage_process = num_points / 100.0;
  for (long long i = 0, j = 0; i < num_points; ++i, ++j) {
    // 每完成百分之一都发送进度
    if (j >= stage_process) {
      emit SendProgress(i / stage_process + 1);
      j = 0;
    }
    double x = distribution(generator);
    double y = distribution(generator);
    if (x * x + y * y <= 1.0) numIn++;
  }
  double pi =
      4.0 * (static_cast<double>(numIn) / static_cast<double>(num_points));
  emit SendPi(pi);
}

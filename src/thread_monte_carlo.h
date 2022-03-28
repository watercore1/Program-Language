#ifndef THREAD_MONTE_CARLO_H
#define THREAD_MONTE_CARLO_H

#include <QObject>
#include <QThread>
#include <random>

class ThreadMonteCarlo : public QThread {
  Q_OBJECT
 public:
  explicit ThreadMonteCarlo(QObject *parent = nullptr);
  void SetNumPoints(long long n);
 signals:
  void SendProgress(int p);
  void SendPi(double pi);

 protected:
  void run() override;

 private:
  long long num_points;  // 投掷石子数量
};

#endif  // THREAD_MONTE_CARLO_H

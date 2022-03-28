#ifndef THREADLEIBNIZ_H
#define THREADLEIBNIZ_H

#include <QObject>
#include <QThread>

class ThreadLeibniz : public QThread {
  Q_OBJECT
 public:
  explicit ThreadLeibniz(QObject *parent = nullptr);
  void SetNumItems(long long n);
 signals:
  void SendProgress(int p);
  void SendPi(double pi);

 protected:
  void run() override;

 private:
  long long num_items;  // 项数
};

#endif  // THREADLEIBNIZ_H

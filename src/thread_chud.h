#ifndef THREADCHUD_H
#define THREADCHUD_H

#include <QObject>
#include <QThread>
#include <cmath>

#include "big_float.h"

class ThreadChud : public QThread {
  Q_OBJECT
 public:
  explicit ThreadChud(QObject *parent = nullptr);
  void SetNumItems(int n);
 signals:
  void SendProgress(int p);
  void SendPi(QString pi);

 protected:
  void run() override;

 private:
  int num_items;
  int precision;
  BigFloat FactorialFraction(int i);
  QString AddSpaceInQString(QString str);
};

#endif  // THREADCHUD_H

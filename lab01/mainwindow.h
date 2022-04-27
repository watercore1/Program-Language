#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>

#include "thread_chud.h"
#include "thread_leibniz.h"
#include "thread_monte_carlo.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_monteCarlo_calculate_clicked();
  void UpdateMonteCarloTime();
  void UpdateMonteCarloProgress(int p);
  void PrintMonteCarloPi(double pi);

  void on_pushButton_leibnize_calculate_clicked();
  void UpdataLeibnizTime();
  void UpdataLeibnizProgress(int p);
  void PrintLeibnizPi(double pi);

  void on_pushButton_chud_calculate_clicked();
  void UpdataChudTime();
  void UpdataChudProgress(int p);
  void PrintChudPi(QString pi);

 private:
  Ui::MainWindow *ui;

  ThreadMonteCarlo *thread_monte_carlo;
  QTimer *timer_monte_carlo;
  QTime base_time_monte_carlo;

  ThreadLeibniz *thread_leibniz;
  QTimer *timer_leibniz;
  QTime base_time_leibniz;

  ThreadChud *thread_chud;
  QTimer *timer_chud;
  QTime base_time_chud;
};
#endif  // MAINWINDOW_H

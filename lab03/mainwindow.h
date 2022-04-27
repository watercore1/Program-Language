#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QStringList>

#include "bignumber.h"

using std::vector;

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
  void on_pushButton_openfile_clicked();

  void on_pushButton_recursion_clicked();

  void on_pushButton_matrix_clicked();

 private:
  Ui::MainWindow *ui;
  // 递归方法
  static const uint RECURSION_MAX = 3000;  // 能承受的最大项数
  uint item_max = 0;                       // 当前输入中的最大项数
  vector<BigNumber> recursion_memory;  // 记忆化数组，大小为 item_max+1
  BigNumber FibonacciRecursion(uint n);  // 使用递归方法更新记忆化数组
                                         //快速矩阵幂方法
  static const uint MATRIX_MAX = 6000;  //能承受的最大项数
  BigNumber FibonacciMatrix(uint n);    // 矩阵快速幂
};
#endif  // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFile>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMainWindow>
#include <iostream>

#include "polygon.h"

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
  void on_pushButton_open_clicked();

  void on_pushButton_compute_clicked();

  void on_listWidget_itemClicked(QListWidgetItem *item);

 private:
  Ui::MainWindow *ui;
  /**
   * @brief dfsVisit DFS 遍历找出所有的环
   * @param graph 邻接矩阵
   * @param node 当前遍历节点的编号
   * @param visit 访问数组，有 0，1，2 三个取值
   * @param father 遍历的父节点数组
   */
  void dfsVisit(const vector<vector<bool> > &graph, int node,
                vector<int> &visit, vector<int> &father);
  vector<Polygon> polygons;
};
#endif  // MAINWINDOW_H

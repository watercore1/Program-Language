#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <fstream>
#include <iostream>
#include <regex>

#include "point.h"
#include "polyline.h"
#include "util.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_readFile_clicked();

  void on_treeWidget_filePolyline_itemClicked(QTreeWidgetItem* item,
                                              int column);

 private:
  Ui::MainWindow* ui;
  vector<string> filenames;
  vector<vector<Polyline>> allfile_polylines;
  /**
   * @brief 从一个文件中读取所有多边形
   * @param 文件名
   * @param 多边形数组
   */
  void ReadPolylineFromFile(string filename, vector<Polyline>& polylines);
  void PrintPolylineToFile(string filename, vector<Polyline>& polylines);
  void DrawTreeWidget();
};
#endif  // MAINWINDOW_H

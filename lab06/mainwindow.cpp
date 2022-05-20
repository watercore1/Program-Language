#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_readFile_clicked() {
  // 获取所有.txt后缀的文件名
  char buff[1000];
  _getcwd(buff, 1000);
  cout << buff << endl;
  string filepath = buff;
  string format = ".txt";
  GetAllFormatFiles(filepath, filenames, format);
  allfile_polylines.clear();
  allfile_polylines.resize(filenames.size());
  //遍历每一个文件
  for (size_t i = 0; i < filenames.size(); i++) {
    //读取其中的折线
    ReadPolylineFromFile(filenames[i], allfile_polylines[i]);
    string outfilename = "Result\\" + filenames[i];
    //存储标注点结果
    PrintPolylineToFile(outfilename, allfile_polylines[i]);
    // 绘制树形控件
    QTreeWidgetItem* top_item =
        new QTreeWidgetItem(ui->treeWidget_filePolyline);
    top_item->setText(0, QString::fromStdString(filenames[i]));
    for (size_t j = 0; j < allfile_polylines[i].size(); j++) {
      QTreeWidgetItem* child_item = new QTreeWidgetItem(top_item);
      child_item->setText(0, QString("%1--%2").arg(i + 1).arg(j + 1));
    }
  }
}

void MainWindow::ReadPolylineFromFile(string filename,
                                      vector<Polyline>& polylines) {
  ifstream fin;  //读取文件流

  string temp;         //临时储存输入
  int line_num = 0;    //折线数量
  char mode = 0;       //注记模式
  int point_num = 0;   //每条折线的点数量
  string mark_number;  //标志点数/规定间隔

  polylines.clear();
  fin.open(filename);
  //如果打开成功
  if (!fin.is_open()) {
    cout << "open failed: " << filename << endl;
    return;
  }
  smatch result;
  regex pattern("(A|B)\\s*");                    // 匹配注记模式
  regex counter("(\\d+)\\s*");                   // 匹配折线数量
  regex catalog("(\\d+)\\s(\\d+\\.?\\d*)\\s*");  // 匹配折线开头的两个数字
  regex data("(-?\\d+\\.?\\d*)\\s*(-?\\d+\\.?\\d*)\\s*");  // 匹配点的坐标
  // 开始尝试匹配
  try {
    //首先读一行，匹配注记模式
    getline(fin, temp);
    if (regex_match(temp, result, pattern)) {
      cout << "mode:" << result[1] << endl;
      mode = result[1].str()[0];
      // 再读一行，匹配折线数量
      getline(fin, temp);
      if (regex_match(temp, result, counter)) {
        line_num = atoi(result[1].str().c_str());
        cout << line_num << endl;
        // 依次读入每一条折线
        for (int i = 0; i < line_num; i++) {
          // 对于每条折线，先读开头的两个数字
          getline(fin, temp);
          if (regex_match(temp, result, catalog)) {
            point_num = atoi(result[1].str().c_str());
            mark_number = result[2].str();
            cout << point_num << "\t" << mark_number << endl;
            vector<Point> points;
            // 依次读入一条折线的每一个点
            for (int i = 0; i < point_num; i++) {
              // 读入一行，匹配坐标
              getline(fin, temp);
              if (regex_match(temp, result, data)) {
                points.push_back(Point(result[1], result[2]));
              }
            }
            // 生成标注好的折线
            polylines.push_back(Polyline(points, mode, mark_number));
          }
        }
      }
    }
  } catch (const char* msg) {
    cerr << msg << endl;
  }
}

void MainWindow::PrintPolylineToFile(string filename,
                                     vector<Polyline>& polylines) {
  ofstream fout;  //打印文件
  fout.open(filename);
  if (!fout.is_open()) {
    cout << "open failed: " << filename << endl;
    return;
  }
  for (size_t i = 0; i < polylines.size(); i++) {
    fout << "Polyline" << i + 1 << " : \n" << polylines[i].MarkerStr() << endl;
  }
  fout << flush;
  fout.close();
}

void MainWindow::DrawTreeWidget() {
  for (size_t i = 0; i < filenames.size(); i++) {
  }
}

void MainWindow::on_treeWidget_filePolyline_itemClicked(QTreeWidgetItem* item,
                                                        int column) {
  QStringList list = item->text(0).split("--");
  if (list.size() == 2) {
    int i = list[0].toInt();
    int j = list[1].toInt();
    ui->widget->GetPolyline(allfile_polylines[i - 1][j - 1]);
  }
}

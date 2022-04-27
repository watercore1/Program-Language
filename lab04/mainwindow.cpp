#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_open_clicked() {
  // 选中文件，得到文件名
  QString file_name = QFileDialog::getOpenFileName(
      this, tr("Open File"), QDir::currentPath(), tr("Text (*.txt)"));
  QFile file(file_name);
  // 打开文件
  if (!file.open(QIODevice::ReadOnly)) {
    cout << "Can't open file";
    return;
  }
  // 展示文件内容
  ui->textEdit_input->setPlainText(file.readAll());
  file.close();
}

void MainWindow::on_pushButton_compute_clicked() {
  vector<vector<Point>> input;
  QStringList list_input = ui->textEdit_input->toPlainText().split("\n");
  bool ok;
  double one_line[4];  // 一行内的输入为四个 double 数字
  foreach (QString s, list_input) {
    QStringList list_double_input = s.split(QRegExp("[\\s]+"));
    if (list_double_input.size() != 4) {
      ui->textEdit_output->clear();
      ui->textEdit_output->append("Not 2 point in one line");
      return;
    }
    for (int i = 0; i < 4; i++) {
      one_line[i] = list_double_input[i].toDouble(&ok);
      if (!ok) {
        ui->textEdit_output->clear();
        ui->textEdit_output->append("Not Double Input");
        return;
      }
    }
    vector<Point> temp = {Point(one_line[0], one_line[1]),
                          Point(one_line[2], one_line[3])};
    input.push_back(temp);
  }
  Polygon::GenerateGraph(input);
  int point_num = Polygon::points.size();
  vector<int> visit(point_num, 0);
  vector<int> father(point_num, -1);
  for (int i = 0; i < point_num; i++) {
    if (visit[i] == 0) dfsVisit(Polygon::graph, i, visit, father);
  }
  for (unsigned long long i = 0; i < polygons.size(); i++) {
    polygons[i].ComputeAttribute();
    ui->listWidget->addItem(QString("Polygon %1").arg(i + 1));
  }
}

void MainWindow::dfsVisit(const vector<vector<bool>> &graph, int node,
                          vector<int> &visit, vector<int> &father) {
  int n = graph.size();
  visit[node] = 1;
  for (int i = 0; i < n; i++)
    if (i != node && graph[node][i] == true) {
      if (visit[i] == 1 && i != father[node]) {
        //找到一个环
        vector<int> point_ids;
        int tmp = node;
        while (tmp != i) {
          point_ids.push_back(tmp);
          tmp = father[tmp];
        }
        point_ids.push_back(i);
        polygons.push_back(Polygon(point_ids));
      } else if (visit[i] == 0) {
        father[i] = node;
        dfsVisit(graph, i, visit, father);
      }
    }
  visit[node] = 2;
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item) {
  ui->textEdit_output->clear();
  int n = ui->listWidget->currentRow();
  //输出坐标序列
  ui->textEdit_output->append("This Polygon is consist of:");
  QString points;
  vector<int> point_ids = polygons[n].GetPointIds();
  for (unsigned long long i = 0; i < point_ids.size(); i++) {
    points += QString::fromStdString(Polygon::points[point_ids[i]].Str());
    points += " ";
  }
  ui->textEdit_output->append(points);
  //输出是否为简单多边形
  if (!polygons[n].IsSimple()) {
    ui->textEdit_output->append("This PolyGon is Complex.\n");
    return;
  } else {
    ui->textEdit_output->append("This PolyGon is Simple.\n");
  }
  //输出属性
  ui->textEdit_output->append("MBR is:");
  vector<double> bound = polygons[n].GetBound();
  ui->textEdit_output->append(QString("xL:%1 xR:%2 yd:%3 yu:%4")
                                  .arg(bound[0])
                                  .arg(bound[1])
                                  .arg(bound[2])
                                  .arg(bound[3]));
  ui->textEdit_output->append(QString("Area is:%1").arg(polygons[n].GetArea()));
  ui->textEdit_output->append(
      QString("Length is:%1").arg(polygons[n].GetLength()));
  if (polygons[n].IsConvex())
    ui->textEdit_output->append("This Polygon is Convex");
  else
    ui->textEdit_output->append("This Polygon is Concave");
}

#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_openfile_clicked() {
  // 选中文件，得到文件名
  QString file_name = QFileDialog::getOpenFileName(
      this, tr("Open File"), QDir::currentPath(), tr("Text (*.txt)"));
  QFile file(file_name);
  // 打开文件
  if (!file.open(QIODevice::ReadOnly)) {
    std::cout << "Can't open file";
    return;
  }
  // 展示文件内容
  ui->textEdit->setPlainText(file.readAll());
  file.close();
}

void MainWindow::on_pushButton_recursion_clicked() {
  ui->textBrowser_recursion->clear();
  QStringList list_input = ui->textEdit->toPlainText().split("\n");
  bool ok;
  bool need_update_memory = false;
  uint item_number = 0;

  //遍历输入，找到最大项，判断是否要扩充记忆化数组
  foreach (QString s, list_input) {
    item_number = s.toUInt(&ok);
    //如果输入的最大项大于记忆化数组的大小，则扩充记忆化数组
    if (ok && item_number > item_max && item_number <= RECURSION_MAX) {
      item_max = item_number;
      need_update_memory = true;
    }
  }
  if (need_update_memory) {
    recursion_memory.resize(item_max + 1);
    FibonacciRecursion(item_max);
  }
  //扩充完记忆化数组后，对于每一行，只需要返回对应的项即可
  foreach (QString s, list_input) {
    item_number = s.toUInt(&ok);
    if (!ok) {
      ui->textBrowser_recursion->append("Not Positive Integer.");
    } else if (item_number > RECURSION_MAX) {
      ui->textBrowser_recursion->append(
          QString("Should Less Than %1").arg(RECURSION_MAX));
    } else {
      ui->textBrowser_recursion->append(
          QString::fromStdString(recursion_memory[item_number].getString()));
    }
  }
}

void MainWindow::on_pushButton_matrix_clicked() {
  ui->textBrowser_matrix->clear();
  QStringList list_input = ui->textEdit->toPlainText().split("\n");
  bool ok;
  uint item_number = 0;
  foreach (QString s, list_input) {
    item_number = s.toUInt(&ok);
    if (!ok) {
      ui->textBrowser_matrix->append("Not Positive Integer.");
    } else if (item_number > MATRIX_MAX) {
      ui->textBrowser_matrix->append(
          QString("Should Less Than %1").arg(MATRIX_MAX));
    } else {
      ui->textBrowser_matrix->append(
          QString::fromStdString(FibonacciMatrix(item_number).getString()));
    }
  }
}

BigNumber MainWindow::FibonacciRecursion(uint n) {
  if (n <= 2) {
    return recursion_memory[n] = BigNumber(n);
  }
  BigNumber first, second;
  //等于 0 说明仍然是初始值，没有计算过这一项
  if (recursion_memory[n - 1] == 0) {
    first = FibonacciRecursion(n - 1);
  } else {
    first = recursion_memory[n - 1];
  }
  if (recursion_memory[n - 2] == 0) {
    second = FibonacciRecursion(n - 2);
  } else {
    second = recursion_memory[n - 2];
  }
  return recursion_memory[n] = first + second;
}
//声明矩阵幂算法，定义放在 matrxi.cpp 文件
vector<vector<BigNumber>> matrixPow(vector<vector<BigNumber>> a, int n);
BigNumber MainWindow::FibonacciMatrix(uint n) {
  vector<vector<BigNumber>> ret = {{1, 1}, {1, 0}};
  vector<vector<BigNumber>> res = matrixPow(ret, n);
  return res[0][0];
}

#include "mainwindow.h"

#include <primesieve.hpp>

#include "ui_mainwindow.h"

using namespace primesieve;

std::vector<uint> primes;
bool MRtest(unsigned long long n);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  generate_primes(INT32_MAX, &primes);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {
  ui->textBrowser->clear();
  if (!InputIsRight()) return;
  uint prime_first = primes[0];
  for (int i = 0; prime_first <= test / 2; i++) {
    if (MRtest(test - prime_first)) {
      ui->textBrowser->append(QString("%1=%2+%3")
                                  .arg(test)
                                  .arg(prime_first)
                                  .arg(test - prime_first));
      if (!ui->checkBox->isChecked()) return;
    }
    prime_first = primes[i + 1];
  }
}

bool MainWindow::InputIsRight() {
  bool ok;
  test = ui->lineEdit->text().toUInt(&ok);
  if (!ok) {
    ui->textBrowser->setText("Input is not legal,Please input uint type");
    return false;
  }
  if (ui->checkBox->isChecked() && test > 1000000) {
    ui->textBrowser->setText(
        "if print all combination,input should le 1000000");
    return false;
  }
  if (test <= 2) {
    ui->textBrowser->setText(QString::number(test) +
                             " le 2, can not verify GoldBach Conjecture");
    return false;
  }
  if (test % 2 == 1) {
    ui->textBrowser->setText(QString::number(test) +
                             " is not odd, can not verify GoldBach Conjecture");
    return false;
  }
  return true;
}

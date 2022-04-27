#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  // MonteCarlo
  timer_monte_carlo = new QTimer();
  connect(timer_monte_carlo, &QTimer::timeout, this,
          &MainWindow::UpdateMonteCarloTime);
  thread_monte_carlo = new ThreadMonteCarlo();
  connect(thread_monte_carlo, &ThreadMonteCarlo::SendProgress, this,
          &MainWindow::UpdateMonteCarloProgress);
  connect(thread_monte_carlo, &ThreadMonteCarlo::SendPi, this,
          &MainWindow::PrintMonteCarloPi);
  // Leibniz
  timer_leibniz = new QTimer();
  connect(timer_leibniz, &QTimer::timeout, this,
          &MainWindow::UpdataLeibnizTime);
  thread_leibniz = new ThreadLeibniz();
  connect(thread_leibniz, &ThreadLeibniz::SendProgress, this,
          &MainWindow::UpdataLeibnizProgress);
  connect(thread_leibniz, &ThreadLeibniz::SendPi, this,
          &MainWindow::PrintLeibnizPi);
  // Chud
  timer_chud = new QTimer();
  connect(timer_chud, &QTimer::timeout, this, &MainWindow::UpdataChudTime);
  thread_chud = new ThreadChud();
  connect(thread_chud, &ThreadChud::SendProgress, this,
          &MainWindow::UpdataChudProgress);
  connect(thread_chud, &ThreadChud::SendPi, this, &MainWindow::PrintChudPi);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_monteCarlo_calculate_clicked() {
  // 如果该进程还没结束，则不开启新进程
  if (thread_monte_carlo->isRunning()) return;
  ui->progressBar_monteCarlo->setValue(0);
  timer_monte_carlo->start(1);
  base_time_monte_carlo = QTime::currentTime();
  long long numPoints = ui->lineEdit_monteCarlo_number->text().toLongLong();
  thread_monte_carlo->SetNumPoints(numPoints);
  thread_monte_carlo->start();
}

void MainWindow::UpdateMonteCarloTime() {
  int msecs = base_time_monte_carlo.msecsTo(QTime::currentTime());
  ui->lcdNumber_monteCarlo->display(msecs);
}

void MainWindow::UpdateMonteCarloProgress(int p) {
  ui->progressBar_monteCarlo->setValue(p);
}

void MainWindow::PrintMonteCarloPi(double pi) {
  ui->lineEdit_monteCarlo_pi->setText(QString::number(pi, 'g', 15));
  timer_monte_carlo->stop();
}

void MainWindow::on_pushButton_leibnize_calculate_clicked() {
  // 如果该进程还没结束，则不开启新进程
  if (thread_leibniz->isRunning()) return;
  ui->progressBar_leibniz->setValue(0);
  timer_leibniz->start(1);
  base_time_leibniz = QTime::currentTime();
  long long numItems = ui->lineEdit_leibniz_number->text().toLongLong();
  thread_leibniz->SetNumItems(numItems);
  thread_leibniz->start();
}

void MainWindow::UpdataLeibnizTime() {
  int msecs = base_time_leibniz.msecsTo(QTime::currentTime());
  ui->lcdNumber_leibniz->display(msecs);
}

void MainWindow::UpdataLeibnizProgress(int p) {
  ui->progressBar_leibniz->setValue(p);
}

void MainWindow::PrintLeibnizPi(double pi) {
  ui->lineEdit_leibniz_pi->setText(QString::number(pi, 'g', 15));
  timer_leibniz->stop();
}

void MainWindow::on_pushButton_chud_calculate_clicked() {
  // 如果该进程还没结束，则不开启新进程
  if (thread_chud->isRunning()) return;
  ui->progressBar_chud->setValue(0);
  timer_chud->start(1);
  base_time_chud = QTime::currentTime();
  long long numItems = ui->lineEdit_chud_number->text().toLongLong();
  thread_chud->SetNumItems(numItems);
  thread_chud->start();
}

void MainWindow::UpdataChudTime() {
  int msecs = base_time_chud.msecsTo(QTime::currentTime());
  ui->lcdNumber_chud->display(msecs);
}

void MainWindow::UpdataChudProgress(int p) {
  ui->progressBar_chud->setValue(p);
}

void MainWindow::PrintChudPi(QString pi) {
  ui->lineEdit_chud_pi->setText(pi);
  timer_chud->stop();
}

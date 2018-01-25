#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include <algorithm>
#include <vector>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
//  double countCombination(double a, double n, int k);
  QVector <double> countPk(double a, double n, int k);
  double countPv(double a, double n, int k);

private slots:
  void on_pushButton_clicked();
  void on_label_7_linkActivated(const QString &link);
  void on_a_valueChanged(double arg1);
  void on_v_valueChanged(int arg1);
  void on_n_valueChanged(int arg1);
  void on_m_valueChanged(int arg1);
  void changeStyle(int n);
  void refreshGraph();

  void on_comboBox_currentIndexChanged(int index);

private:
  Ui::MainWindow *ui;
  Dialog *d;
  int style = 0;
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <windows.h>
#include "calc.h"
#include <QThread>

int nod(int a, int b) {

    while (a != b && a != 0) {
        if (a > b) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        b = b - a;
    }
    if (a == 0) return 1;
    return a;
}

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

//  QStringList titles;
//  titles << "Pk";
  ui->tableWidget->setColumnCount(0);
//  ui->tableWidget->setHorizontalHeaderLabels(titles);

  QPalette Pal(palette());
  Pal.setColor(QPalette::Background, Qt::white);
  Pal.setColor(QPalette::Light, Qt::gray);
  QPalette Pal2(palette());
  Pal2.setColor(QPalette::Background, Qt::gray);
  this->setPalette(Pal);

  QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
  effect->setOffset(-1, -1);
  effect->setColor(Qt::black);
  ui->label_7->setGraphicsEffect(effect);
  ui->frame_9->setFrameStyle(QFrame::Panel | QFrame::Plain);
  ui->frame_9->setLineWidth(1);
  ui->frame_6->setFrameStyle(QFrame::Panel | QFrame::Plain);
  ui->frame_6->setLineWidth(1);
//  ui->superFrame->setFrameStyle(QFrame::Panel | QFrame::Plain);
//  ui->superFrame->setLineWidth(1);
  ui->verticalFrame->setFrameStyle(QFrame::Panel | QFrame::Plain);
  ui->verticalFrame->setLineWidth(1);
  ui->verticalFrame2->setFrameStyle(QFrame::Panel | QFrame::Plain);
  ui->verticalFrame2->setLineWidth(1);
//  ui->pushButton->setVisible(false);

  ui->comboBox->addItem("Серебряный");
  ui->comboBox->addItem("Тёмный");
  ui->comboBox->addItem("Классический");
  ui->comboBox->addItem("Бонч");
  ui->comboBox->addItem("Умиротворяющий");
}

MainWindow::~MainWindow() {
  delete ui;
}

QVector <double> MainWindow::countPk(double a, double n, int v) {
  double denumerator = 0;
  double combination = 1;
  double fraction = 1;

  QVector <double> pk;

  for(int i = 0; i <= v; i++)
  {
    denumerator+=combination*fraction;
    combination*=((double)n-i)/(i+1);
    fraction*=a/(1-a);
  }

  combination = 1;
  fraction = 1;

  for(int i = 0; i <= v; i++) {
      pk.push_back((combination*fraction)/denumerator);
      combination*=((double)n-i)/(i+1);
      fraction*=a/(1-a);
  }
  return pk;
}

double MainWindow::countPv(double a, double n, int v) {
  int denumerator = 0;
  int combination = 1;
  int fraction = 1;

  for(int i = 0; i <= v; i++) {
    denumerator+=combination*fraction;
    combination*=((double)(n-1) - (double)i)/(i+1);
    fraction *= a/(1-a);
  }

  combination = 1;
  fraction = 1;

  for(int i = 0; i <= v; i++) {
    combination *= ((double)(n-1)-(double)i)/(i+1);
    fraction *= a/(1-a);
  }

  return combination*fraction/denumerator;
}

void MainWindow::changeStyle(int num) {
  style = num;
  switch (num) {
    case 1 : {
      ui->customPlot->xAxis->setBasePen(QPen(Qt::white, 1));
      ui->customPlot->yAxis->setBasePen(QPen(Qt::white, 1));
      ui->customPlot->xAxis->setTickPen(QPen(Qt::white, 1));
      ui->customPlot->yAxis->setTickPen(QPen(Qt::white, 1));
      ui->customPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
      ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
      ui->customPlot->xAxis->setTickLabelColor(Qt::white);
      ui->customPlot->yAxis->setTickLabelColor(Qt::white);
      ui->customPlot->xAxis->setLabelColor(Qt::white);
      ui->customPlot->yAxis->setLabelColor(Qt::white);

      QLinearGradient plotGradient;
      plotGradient.setStart(0, 0);
      plotGradient.setFinalStop(0, 350);
      plotGradient.setColorAt(0, QColor(80, 80, 80));
      plotGradient.setColorAt(1, QColor(50, 50, 50));
      ui->customPlot->setBackground(plotGradient);

/*      QLinearGradient axisRectGradient;
      axisRectGradient.setStart(0, 0);
      axisRectGradient.setFinalStop(0, 350);
      axisRectGradient.setColorAt(0, QColor(80, 80, 80));
      axisRectGradient.setColorAt(1, QColor(30, 30, 30));*/
      ui->customPlot->axisRect()->setBackground(plotGradient);

/*      QLinearGradient bgGradient;
      bgGradient.setStart(0, 0);
      bgGradient.setFinalStop(0, 350);
      bgGradient.setColorAt(0, QColor(80, 80, 80));
      plotGradient.setColorAt(1, QColor(50, 50, 50));*/
      QPalette Pal(palette());
      Pal.setBrush(QPalette::Background, plotGradient);
      Pal.setBrush(QPalette::Button, plotGradient);
      Pal.setBrush(QPalette::WindowText, Qt::white);
//      Pal.setBrush(QPalette::ButtonText, Qt::white);
      ui->label_7->setPalette(Pal);
      this->setPalette(Pal);

      QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
      effect->setOffset(-2, -2);
      effect->setColor(Qt::black);
      effect->setBlurRadius(2.0);
      ui->label_6->setGraphicsEffect(effect);
      QGraphicsDropShadowEffect* effect2 = new QGraphicsDropShadowEffect(this);
      effect2->setOffset(-2, -2);
      effect2->setColor(Qt::black);
      effect2->setBlurRadius(1.0);
      ui->label_5->setGraphicsEffect(effect2);

      ui->comboBox->setStyleSheet("QComboBox { background-color: gray; }"); //rgb(80, 80, 80)
      ui->pushButton->setStyleSheet("QPushButton { background-color: gray; }");
      ui->a->setStyleSheet("QDoubleSpinBox { background-color: gray; }");
      ui->v->setStyleSheet("QSpinBox { background-color: gray; }");
      ui->n->setStyleSheet("QSpinBox { background-color: gray; }");
      ui->m->setStyleSheet("QSpinBox { background-color: gray; }");
//      ui->tableWidget->setStyleSheet("QTableView { background-color: rgb(160, 160, 160); } QTableCornerButton::section { background-color: rgb(160, 160, 160); }");
//      ui->comboBox->setPalette(Pal);
      break;
    }
    case 2 : {
      ui->customPlot->setBackground(Qt::white);
      ui->customPlot->axisRect()->setBackground(Qt::white);
      ui->customPlot->xAxis->setBasePen(QPen(Qt::black, 1));
      ui->customPlot->yAxis->setBasePen(QPen(Qt::black, 1));
      ui->customPlot->xAxis->setTickPen(QPen(Qt::black, 1));
      ui->customPlot->yAxis->setTickPen(QPen(Qt::black, 1));
      ui->customPlot->xAxis->setSubTickPen(QPen(Qt::black, 1));
      ui->customPlot->yAxis->setSubTickPen(QPen(Qt::black, 1));
      ui->customPlot->xAxis->setTickLabelColor(Qt::black);
      ui->customPlot->yAxis->setTickLabelColor(Qt::black);
      ui->customPlot->xAxis->setLabelColor(Qt::black);
      ui->customPlot->yAxis->setLabelColor(Qt::black);
      ui->comboBox->setStyleSheet("QComboBox { background-color: white; }"); //rgb(80, 80, 80)
      ui->pushButton->setStyleSheet("QPushButton { background-color: white; }");
      ui->a->setStyleSheet("QDoubleSpinBox { background-color: white; }");
      ui->v->setStyleSheet("QSpinBox { background-color: white; }");
      ui->n->setStyleSheet("QSpinBox { background-color: white; }");
      ui->m->setStyleSheet("QSpinBox { background-color: white; }");

      QPalette Pal(palette());
      Pal.setColor(QPalette::Background, Qt::white);
      Pal.setBrush(QPalette::WindowText, QColor(27, 20, 112));
      ui->label_7->setPalette(Pal);
      this->setPalette(Pal);

      QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
      effect->setOffset(-1, -1);
      effect->setColor(Qt::white);
      ui->label_6->setGraphicsEffect(effect);
      QGraphicsDropShadowEffect* effect2 = new QGraphicsDropShadowEffect(this);
      effect2->setOffset(-1, -1);
      effect2->setColor(Qt::white);
      ui->label_5->setGraphicsEffect(effect2);

      break;
    }
    case 3 : {
        auto color = QColor(200, 70, 0);
        ui->customPlot->xAxis->setBasePen(QPen(color, 1));
        ui->customPlot->yAxis->setBasePen(QPen(color, 1));
        ui->customPlot->xAxis->setTickPen(QPen(color, 1));
        ui->customPlot->yAxis->setTickPen(QPen(color, 1));
        ui->customPlot->xAxis->setSubTickPen(QPen(color, 1));
        ui->customPlot->yAxis->setSubTickPen(QPen(color, 1));
        ui->customPlot->xAxis->setTickLabelColor(color);
        ui->customPlot->yAxis->setTickLabelColor(color);
        ui->customPlot->xAxis->setLabelColor(color);
        ui->customPlot->yAxis->setLabelColor(color);

        QLinearGradient plotGradient;
        plotGradient.setStart(0, 0);
        plotGradient.setFinalStop(0, 350);
        plotGradient.setColorAt(0, QColor(220, 220, 220));
        plotGradient.setColorAt(1, QColor(200, 200, 200));
        ui->customPlot->setBackground(plotGradient);

        ui->customPlot->axisRect()->setBackground(plotGradient);

        QPalette Pal(palette());
        Pal.setBrush(QPalette::Background, plotGradient);
        Pal.setBrush(QPalette::WindowText, QColor(220, 80, 0));
        ui->label_7->setPalette(Pal);
        this->setPalette(Pal);

        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
        effect->setOffset(-1, -1);
        effect->setColor(Qt::black);
        ui->label_6->setGraphicsEffect(effect);
        QGraphicsDropShadowEffect* effect2 = new QGraphicsDropShadowEffect(this);
        effect2->setOffset(-1, -1);
        effect2->setColor(Qt::black);
        ui->label_5->setGraphicsEffect(effect2);

        QPalette Pal2(palette());
        Pal2.setBrush(QPalette::WindowText, QColor(250, 140, 10));
        ui->label_7->setPalette(Pal2);

        ui->comboBox->setStyleSheet("QComboBox { background-color: rgb(255, 160, 30); }");
        ui->pushButton->setStyleSheet("QPushButton { background-color: rgb(255, 160, 30); }");
        ui->a->setStyleSheet("QDoubleSpinBox { background-color: rgb(255, 160, 30); }");
        ui->v->setStyleSheet("QSpinBox { background-color: rgb(255, 160, 30); }");
        ui->n->setStyleSheet("QSpinBox { background-color: rgb(255, 160, 30); }");
        ui->m->setStyleSheet("QSpinBox { background-color: rgb(255, 160, 30); }");
        break;
    }
    case 4 : {
//        auto color = QColor(100, 40, 20);
        auto color = QColor(25, 75, 25);
        ui->customPlot->xAxis->setBasePen(QPen(color, 1));
        ui->customPlot->yAxis->setBasePen(QPen(color, 1));
        ui->customPlot->xAxis->setTickPen(QPen(color, 1));
        ui->customPlot->yAxis->setTickPen(QPen(color, 1));
        ui->customPlot->xAxis->setSubTickPen(QPen(color, 1));
        ui->customPlot->yAxis->setSubTickPen(QPen(color, 1));
        ui->customPlot->xAxis->setTickLabelColor(color);
        ui->customPlot->yAxis->setTickLabelColor(color);
        ui->customPlot->xAxis->setLabelColor(color);
        ui->customPlot->yAxis->setLabelColor(color);

        QLinearGradient plotGradient;
        plotGradient.setStart(0, 0);
        plotGradient.setFinalStop(0, 350);
//        plotGradient.setColorAt(0, QColor(230, 255, 230));
//        plotGradient.setColorAt(1, QColor(210, 245, 210));
//        plotGradient.setColorAt(0, QColor(240, 240, 240));
//        plotGradient.setColorAt(1, QColor(220, 220, 220));
        plotGradient.setColorAt(0, QColor(255, 255, 255));
        plotGradient.setColorAt(1, QColor(235, 235, 235));
        ui->customPlot->setBackground(plotGradient);

        ui->customPlot->axisRect()->setBackground(plotGradient);

        QPalette Pal(palette());
        Pal.setBrush(QPalette::Background, plotGradient);
        Pal.setBrush(QPalette::WindowText, QColor(25, 75, 25));
//        Pal.setBrush(QPalette::WindowText, QColor(100, 40, 20));
        QPalette Pal2(palette());
        Pal2.setBrush(QPalette::WindowText, QColor(60, 150, 60));
        ui->label_7->setPalette(Pal);
        this->setPalette(Pal);

        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
        effect->setOffset(-1, -1);
        effect->setColor(Qt::black);
        ui->label_6->setGraphicsEffect(effect);
        QGraphicsDropShadowEffect* effect2 = new QGraphicsDropShadowEffect(this);
        effect2->setOffset(-1, -1);
        effect2->setColor(Qt::black);
        ui->label_5->setGraphicsEffect(effect2);

        ui->comboBox->setStyleSheet("QComboBox { background-color: white; }"); //rgb(80, 80, 80)
        ui->pushButton->setStyleSheet("QPushButton { background-color: white; }");
        ui->a->setStyleSheet("QDoubleSpinBox { background-color: white; }");
        ui->v->setStyleSheet("QSpinBox { background-color: white; }");
        ui->n->setStyleSheet("QSpinBox { background-color: white; }");
        ui->m->setStyleSheet("QSpinBox { background-color: white; }");
        break;
    }
    default : {
      auto color = QColor(25, 25, 75);
      ui->customPlot->xAxis->setBasePen(QPen(color, 1));
      ui->customPlot->yAxis->setBasePen(QPen(color, 1));
      ui->customPlot->xAxis->setTickPen(QPen(color, 1));
      ui->customPlot->yAxis->setTickPen(QPen(color, 1));
      ui->customPlot->xAxis->setSubTickPen(QPen(color, 1));
      ui->customPlot->yAxis->setSubTickPen(QPen(color, 1));
      ui->customPlot->xAxis->setTickLabelColor(color);
      ui->customPlot->yAxis->setTickLabelColor(color);
      ui->customPlot->xAxis->setLabelColor(color);
      ui->customPlot->yAxis->setLabelColor(color);

      QLinearGradient plotGradient;
      plotGradient.setStart(0, 0);
      plotGradient.setFinalStop(0, 350);
      plotGradient.setColorAt(0, QColor(240, 240, 240));
      plotGradient.setColorAt(1, QColor(220, 220, 220));
      ui->customPlot->setBackground(plotGradient);

      ui->customPlot->axisRect()->setBackground(plotGradient);

      QPalette Pal(palette());
      Pal.setBrush(QPalette::Background, plotGradient);
      Pal.setBrush(QPalette::WindowText, QColor(25, 25, 75));
      ui->label_7->setPalette(Pal);
      this->setPalette(Pal);

      QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
      effect->setOffset(-1, -1);
      effect->setColor(Qt::black);
      ui->label_6->setGraphicsEffect(effect);
      QGraphicsDropShadowEffect* effect2 = new QGraphicsDropShadowEffect(this);
      effect2->setOffset(-1, -1);
      effect2->setColor(Qt::black);
      ui->label_5->setGraphicsEffect(effect2);

      ui->comboBox->setStyleSheet("QComboBox { background-color: white; }"); //rgb(80, 80, 80)
      ui->pushButton->setStyleSheet("QPushButton { background-color: white; }");
      ui->a->setStyleSheet("QDoubleSpinBox { background-color: white; }");
      ui->v->setStyleSheet("QSpinBox { background-color: white; }");
      ui->n->setStyleSheet("QSpinBox { background-color: white; }");
      ui->m->setStyleSheet("QSpinBox { background-color: white; }");
      break;
    }
  }
  double m = ui->m->value(), a = ui->a->value(), n = ui->n->value(), v = ui->v->value() - 1;
  double alpha = m*a/(1 - a);
  if (a != 0.0 && m != 0 && n != 0 && v != 0 && v < n && ((alpha/m) * (((n - v)/v))) <= 1)
//    refreshGraph();
    on_pushButton_clicked();
}

void MainWindow::refreshGraph() {
  double bottom = 0, pk, top, pt, pv, nk;
  double m = ui->m->value(), a = ui->a->value(), n = ui->n->value(), v = ui->v->value() - 1;
  double alpha = m*a/(1 - a);

  QVector <double> pkArr = countPk(a, n, v);
  QVector <double> x; // initialize with entries 0..100
  QStringList list;
  ui->tableWidget->insertRow(ui->tableWidget->rowCount());
  for (int k = 0; k <= v; k++) {
    x.push_back(k);
    ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, k,
                           new QTableWidgetItem(QString("%1").arg(pkArr[k], 0, 'f', 5)));
//    list.push_back();
  }
  ui->tableWidget->resizeColumnsToContents();
  // create graph and assign data to it:
  auto graph = ui->customPlot->addGraph();
  graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::white), 5));
  if (style == 0) {
    graph->setPen(QPen(QColor(0, 0, 120), 2));
    graph->setBrush(QColor(150, 150, 200, 40));
  }
  if (style == 1) {
    graph->setPen(QPen(QColor(60, 150, 60), 2));
    graph->setBrush(QColor(60, 150, 60, 40));
  }
  if (style == 2) {
    graph->setPen(QPen(QColor(0, 0, 120), 2));
    graph->setBrush(QColor(0, 0, 120, 0));
  }
  if (style == 4) {
//    graph->setPen(QPen(QColor(100, 40, 20), 2));
//    graph->setBrush(QColor(100, 40, 20, 40));
    graph->setPen(QPen(QColor(60, 150, 60), 2));
    graph->setBrush(QColor(60, 150, 60, 40));
  }
  if (style == 3) {
    graph->setPen(QPen(QColor(230, 100, 0), 2));
    graph->setBrush(QColor(230, 100, 0, 40));
    ui->label_7->setText("M/M/V/V/N)))");
  }
  else
    ui->label_7->setText("M/M/V/V/N");

  ui->customPlot->graph(0)->setData(x, pkArr);
  // give the axes some labels:
  ui->customPlot->xAxis->setLabel("k");
  ui->customPlot->yAxis->setLabel("Pk");
  // set axes ranges, so we see all data:
  ui->customPlot->xAxis->setRange(0, v);
  ui->customPlot->yAxis->setRange(0, 1);
  ui->customPlot->replot();

  pt = pkArr[v];
  ui->pt->setText("Pt = " + QString("%1").arg(pt, 0, 'f', 5));
  pv = countPv(a, n, v);
  ui->pv->setText("Pv = " + QString("%1").arg(pv, 0, 'f', 5));
  for (int k = 0; k <= v; k++) {
    nk += pkArr[k]*k;
  }
  ui->nk->setText("k̄ = " + QString("%1").arg(nk, 0, 'f', 5));
  m = ui->m->value();
  ui->nt->setText("t̄ = " + QString("%1").arg(nk/m, 0, 'f', 5));
}

void MainWindow::on_pushButton_clicked() {
  if (ui->m->value() == 99) {
    d = new Dialog();
    d->show();
    return;
  }
  if (ui->a->value() == 0.0 || ui->m->value() == 0 || ui->n->value() == 0 || ui->v->value() == 0) {
    auto msg = QMessageBox::critical(this, "ERROR!", "Все поля должны быть заполнены",
        QMessageBox::Ok);
    return;
  }

  double m = ui->m->value(), a = ui->a->value(), n = ui->n->value(), v = ui->v->value();
  double alpha = m*a/(1 - a);
  if ((m == 0.0) || ((alpha/m) * (((n - v)/v))) >= 1) {
    auto msg = QMessageBox::critical(this, "ERROR!", "Не соблюдены начальные условия \n(alpha/m) * (((n - v)/v))) >= 1",
        QMessageBox::Ok);
    return;
  }
  ui->customPlot->clearMask();
  ui->customPlot->clearItems();
  ui->customPlot->clearGraphs();
  ui->tableWidget->clear();
  ui->tableWidget->setRowCount(0);
  ui->tableWidget->setColumnCount(0);
  if (a >= 1) {
    auto msg = QMessageBox::critical(this, "ERROR!", "'a' can't be more than 1",
        QMessageBox::Ok);
    return;
  }
  if (v > n) {
    auto msg = QMessageBox::critical(this, "ERROR!", "'v' не может быть больше 'n'",
        QMessageBox::Ok);
    return;
  }
  refreshGraph();
}

void MainWindow::on_label_7_linkActivated(const QString &link) {
//  d = new Dialog();
//  d->show();
}

void MainWindow::on_a_valueChanged(double arg1) {
  if (ui->a->value() == 0.0 || ui->m->value() == 0 || ui->n->value() == 0 || ui->v->value() == 0)
    return;
  on_pushButton_clicked();
}

void MainWindow::on_v_valueChanged(int arg1) {
  if (ui->a->value() == 0.0 || ui->m->value() == 0 || ui->n->value() == 0 || ui->v->value() == 0)
    return;
  on_pushButton_clicked();
}

void MainWindow::on_n_valueChanged(int arg1) {
  if (ui->a->value() == 0.0 || ui->m->value() == 0 || ui->n->value() == 0 || ui->v->value() == 0)
    return;
  on_pushButton_clicked();
}

void MainWindow::on_m_valueChanged(int arg1) {
  if (ui->a->value() == 0.0 || ui->m->value() == 0 || ui->n->value() == 0 || ui->v->value() == 0)
    return;
  on_pushButton_clicked();
}

void MainWindow::on_comboBox_currentIndexChanged(int index) {
  changeStyle(index);
}

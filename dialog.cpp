#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog)
{
  ui->setupUi(this);
  QPixmap* kotik = new QPixmap("kotik.jpg");
  ui->label->setPixmap(*kotik);
}

Dialog::~Dialog()
{
  delete ui;
}

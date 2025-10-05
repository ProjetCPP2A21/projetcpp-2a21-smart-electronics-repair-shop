#include "nstock.h"
#include "ui_nstock.h"

Nstock::Nstock(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Nstock)
{
    ui->setupUi(this);
}

Nstock::~Nstock()
{
    delete ui;
}

#include "nstock.h"
#include "ui_nstock.h"

nstock::nstock(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::nstock)
{
    ui->setupUi(this);
}

nstock::~nstock()
{
    delete ui;
}

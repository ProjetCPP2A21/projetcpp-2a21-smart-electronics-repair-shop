#include "sclient.h"
#include "ui_sclient.h"

Sclient::Sclient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Sclient)
{
    ui->setupUi(this);
}

Sclient::~Sclient()
{
    delete ui;
}

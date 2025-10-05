#include "gemployer.h"
#include "ui_gemployer.h"

Gemployer::Gemployer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gemployer)
{
    ui->setupUi(this);
}

Gemployer::~Gemployer()
{
    delete ui;
}

void Gemployer::on_pushButton_5_clicked()
{

}


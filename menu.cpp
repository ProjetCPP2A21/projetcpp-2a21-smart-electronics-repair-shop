#include "menu.h"
#include "ui_menu.h"

MENU::MENU(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MENU)
{
    ui->setupUi(this);
}

MENU::~MENU()
{
    delete ui;
}

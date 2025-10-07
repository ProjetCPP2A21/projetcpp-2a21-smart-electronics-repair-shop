#include "menu_employer.h"
#include "ui_menu_employer.h"
#include <QPushButton>

menu_employer::menu_employer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::menu_employer)
{
    ui->setupUi(this);


    ui->stackedWidget->setCurrentWidget(ui->page);
    connect(ui->employer, &QPushButton::clicked, [this]() {
        goToPage(ui->page_2);
    });
    connect(ui->retour_4, &QPushButton::clicked, this, [this]() { goToPage(ui->page); });
}

menu_employer::~menu_employer()
{
    delete ui;
}

void menu_employer::goToPage(QWidget *page)
{
    ui->stackedWidget->setCurrentWidget(page);
}

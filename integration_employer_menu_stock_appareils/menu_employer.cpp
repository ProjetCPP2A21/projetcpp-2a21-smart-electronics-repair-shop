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
    connect(ui->retour_8, &QPushButton::clicked, this, [this]() { goToPage(ui->page); });
     connect(ui->client, &QPushButton::clicked, this, [this]() { goToPage(ui->page_2); });
    connect(ui->stock, &QPushButton::clicked, this, [this]() { goToPage(ui->page_6); });
    connect(ui->retour_5, &QPushButton::clicked, this, [this]() { goToPage(ui->page); });
    connect(ui->appareils, &QPushButton::clicked, this, [this]() { goToPage(ui->page_15); });
    connect(ui->retour_10, &QPushButton::clicked, this, [this]() { goToPage(ui->page); });
}

menu_employer::~menu_employer()
{
    delete ui;
}

void menu_employer::goToPage(QWidget *page)
{
    ui->stackedWidget->setCurrentWidget(page);
}

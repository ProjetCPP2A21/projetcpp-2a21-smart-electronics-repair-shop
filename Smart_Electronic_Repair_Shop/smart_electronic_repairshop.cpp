#include "smart_electronic_repairshop.h"
#include "ui_smart_electronic_repairshop.h"
#include <QPushButton>

menu_employer::menu_employer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::menu_employer)
{
    ui->setupUi(this);


    ui->stackedWidget->setCurrentWidget(ui->menu_principale);
    connect(ui->employer, &QPushButton::clicked, [this]() {
        goToPage(ui->menu_employe);
    });
    connect(ui->retour_4, &QPushButton::clicked, this, [this]() { goToPage(ui->menu_principale); });
    connect(ui->retour_8, &QPushButton::clicked, this, [this]() { goToPage(ui->menu_principale); });
     connect(ui->client, &QPushButton::clicked, this, [this]() { goToPage(ui->menu_client); });
    connect(ui->stock, &QPushButton::clicked, this, [this]() { goToPage(ui->menu_stock); });
    connect(ui->retour_5, &QPushButton::clicked, this, [this]() { goToPage(ui->menu_principale); });
    connect(ui->appareils, &QPushButton::clicked, this, [this]() { goToPage(ui->menu_appareil); });
    connect(ui->retour_10, &QPushButton::clicked, this, [this]() { goToPage(ui->menu_principale); });
    connect(ui->fournisseur, &QPushButton::clicked, this, [this]() { goToPage(ui->menu_fournisseur); });
    connect(ui->retour_11, &QPushButton::clicked, this, [this]() { goToPage(ui->menu_principale); });
    setWindowTitle("ONAS Smart Electronic Repair Shop"); //Window Name (-r)
}

menu_employer::~menu_employer()
{
    delete ui;
}

void menu_employer::goToPage(QWidget *page)
{
    ui->stackedWidget->setCurrentWidget(page);
}

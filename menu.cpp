#include "menu.h"

MENU::MENU(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MENU)
{
    ui->setupUi(this);

    // Connect the 'clicked' signal of the btCL button to the slot 'onBtCLClicked'
    connect(ui->btCL, &QPushButton::clicked, this, &MENU::onBtCLClicked);

    // Connect the 'clicked' signal of the retourC (Return) button to the slot 'onReturnButtonClicked'
    connect(ui->retourC, &QPushButton::clicked, this, &MENU::onretourCClicked);
}

MENU::~MENU()
{
    delete ui;
}

// Navigate to the pClient page
void MENU::onBtCLClicked()
{
    ui->stackedWidgetM->setCurrentIndex(1);  // Switch to the pClient page
}

// Navigate back to the pMenu page
void MENU::onretourCClicked()
{
    ui->stackedWidgetM->setCurrentIndex(0);  // Switch to the pMenu page
}


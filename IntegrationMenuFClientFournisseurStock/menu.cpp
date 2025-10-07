#include "menu.h"
#include "client.h"
#include "fournisseur.h"
#include "ui_menu.h"
#include <QMessageBox>

MENU::MENU(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MENU)
{
    ui->setupUi(this);

    // Initialize managers
    clientGestionnaire = new Client(this);
    fournisseurGestionnaire = new Fournisseur(this);

    // Connect buttons to slots
    connect(ui->btCL, &QPushButton::clicked, this, &MENU::on_btCL_clicked);
    connect(ui->btFO, &QPushButton::clicked, this, &MENU::on_btFO_clicked);
    connect(ui->retourC, &QPushButton::clicked, this, &MENU::on_retourC_clicked);
    connect(ui->retourF, &QPushButton::clicked, this, &MENU::on_retourF_clicked);
    connect(ui->ajouterC, &QPushButton::clicked, this, &MENU::on_ajouterC_clicked);
    connect(ui->ModifierC, &QPushButton::clicked, this, &MENU::on_ModifierC_clicked);
    connect(ui->SupprimerC, &QPushButton::clicked, this, &MENU::on_SupprimerC_clicked);
    connect(ui->rechercheC, &QPushButton::clicked, this, &MENU::on_rechercheC_clicked);
    connect(ui->triC, &QPushButton::clicked, this, &MENU::on_triC_clicked);
    connect(ui->btnAjouter, &QPushButton::clicked, this, &MENU::on_btnAjouter_clicked);
    connect(ui->btnModifier, &QPushButton::clicked, this, &MENU::on_btnModifier_clicked);
    connect(ui->btnSupprimer, &QPushButton::clicked, this, &MENU::on_btnSupprimer_clicked);
    connect(ui->rechercheF, &QPushButton::clicked, this, &MENU::on_rechercheF_clicked);
    connect(ui->triF, &QPushButton::clicked, this, &MENU::on_triF_clicked);
}

MENU::~MENU()
{
    delete clientGestionnaire;
    delete fournisseurGestionnaire;
    delete ui;
}

void MENU::on_btCL_clicked()
{
    ui->stackedWidgetM->setCurrentIndex(1); // Switch to client page
}

void MENU::on_btFO_clicked()
{
    ui->stackedWidgetM->setCurrentIndex(2); // Switch to supplier page
}

void MENU::on_retourC_clicked()
{
    ui->stackedWidgetM->setCurrentIndex(0); // Return to main menu
}

void MENU::on_retourF_clicked()
{
    ui->stackedWidgetM->setCurrentIndex(0); // Return to main menu
}

void MENU::on_ajouterC_clicked()
{
    clientGestionnaire->ajouterClient();
}

void MENU::on_ModifierC_clicked()
{
    clientGestionnaire->modifierClient();
}

void MENU::on_SupprimerC_clicked()
{
    clientGestionnaire->supprimerClient();
}

void MENU::on_rechercheC_clicked()
{
    QMessageBox::information(this, "Recherche", "Rechercher client - À implémenter");
}

void MENU::on_triC_clicked()
{
    QMessageBox::information(this, "Trier", "Trier client - À implémenter");
}

void MENU::on_btnAjouter_clicked()
{
    fournisseurGestionnaire->ajouterFournisseur();
}

void MENU::on_btnModifier_clicked()
{
    fournisseurGestionnaire->modifierFournisseur();
}

void MENU::on_btnSupprimer_clicked()
{
    fournisseurGestionnaire->supprimerFournisseur();
}

void MENU::on_rechercheF_clicked()
{
    QMessageBox::information(this, "Recherche", "Rechercher fournisseur - À implémenter");
}

void MENU::on_triF_clicked()
{
    QMessageBox::information(this, "Trier", "Trier fournisseur - À implémenter");
}

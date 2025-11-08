#include "smart_electronics_repairshop.h"
#include "ui_smart_electronics_repairshop.h"
#include <QPushButton>
#include "fournisseur.h"

menu_employer::menu_employer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::menu_employer)
{
    ui->setupUi(this);
    fournisseur *gestionFournisseurs = new fournisseur(ui->menu_fournisseur, this);
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
    setWindowTitle("OSANA Smart Electronics Repair Shop"); //Window Name (-r)    
    //connexions fournisseurs:
    connect(ui->menu_fournisseur->findChild<QPushButton*>("btnAjouter_2"), &QPushButton::clicked,
            gestionFournisseurs, &fournisseur::ajouterFournisseur);
    connect(ui->menu_fournisseur->findChild<QPushButton*>("rechercher_2"), &QPushButton::clicked,
            gestionFournisseurs, &fournisseur::rechercherFournisseurParId);
    connect(ui->menu_fournisseur->findChild<QPushButton*>("Modifier_2"), &QPushButton::clicked,
            gestionFournisseurs, &fournisseur::modifierFournisseur);
    connect(ui->menu_fournisseur->findChild<QPushButton*>("btnSupprimer_2"), &QPushButton::clicked,
            gestionFournisseurs, &fournisseur::supprimerFournisseur);
    connect(ui->menu_fournisseur->findChild<QPushButton*>("maj_2"), &QPushButton::clicked,
            gestionFournisseurs, &fournisseur::rafraichirListeFournisseurs);
    connect(ui->menu_fournisseur->findChild<QPushButton*>("tri_3"), &QPushButton::clicked,
            gestionFournisseurs, &fournisseur::trierParNomEntreprise);
}

menu_employer::~menu_employer()
{
    delete ui;
}

void menu_employer::goToPage(QWidget *page)
{
    ui->stackedWidget->setCurrentWidget(page);
}

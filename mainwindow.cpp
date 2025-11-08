// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QRegularExpressionValidator>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableViewClients->setModel(C.afficher());

    // -------------------------------------------------
    // VALIDATEURS D'ENTRÉE – bloquent les mauvais caractères
    // -------------------------------------------------

    // ID : entier positif
    ui->id->setValidator(new QIntValidator(1, 999999999, this));

    // NOM & PRÉNOM : lettres + espaces uniquement
    QRegularExpression nameRx("[A-Za-zÀ-ÿ ]+");  // support accents
    ui->nom->setValidator(new QRegularExpressionValidator(nameRx, this));
    ui->prenom->setValidator(new QRegularExpressionValidator(nameRx, this));

    // TÉLÉPHONE : chiffres uniquement
    ui->telephone->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]+"), this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ==================== AJOUTER ====================
void MainWindow::on_Ajouter_clicked()
{
    int id = ui->id->text().toInt();
    QString nom = ui->nom->text().trimmed();
    QString prenom = ui->prenom->text().trimmed();
    QString telephone = ui->telephone->text().trimmed();
    QDate dateNaiss = ui->dn->date();
    QDate dateInscr = ui->di->date();

    QString dn = dateNaiss.toString("dd/MM/yyyy");
    QString di = dateInscr.toString("dd/MM/yyyy");

    // --- Vérifications simples (champs vides, longueur nom, ID) ---
    if (id <= 0 || nom.isEmpty() || prenom.isEmpty() || telephone.isEmpty() || nom.length() < 3) {
        QMessageBox::warning(this, "Erreur",
                             "Remplissez tous les champs correctement ! Nom doit avoir au moins 3 caractères.");
        return;
    }

    // --- Contraintes sur les dates ---
    if (dateNaiss >= dateInscr) {
        QMessageBox::warning(this, "Erreur",
                             "La date de naissance doit être antérieure à la date d'inscription.");
        return;
    }

    QDate today = QDate::currentDate();
    if (dateNaiss.addYears(18) > today) {
        QMessageBox::warning(this, "Erreur",
                             "Le client doit avoir au moins 18 ans.");
        return;
    }

    // --- Tout est OK → ajout ---
    CLIENT client(id, nom, prenom, telephone, dn, di);
    bool ok = client.ajouter();
    if (ok) {
        QMessageBox::information(nullptr, tr("OK"),
                                 tr("Ajout effectué\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        ui->tableViewClients->setModel(C.afficher());
    } else {
        QMessageBox::critical(nullptr, tr("Erreur"),
                              tr("Échec de l'ajout.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
}

// ==================== SUPPRIMER ====================
void MainWindow::on_Supprimer_clicked()
{
    int id = ui->id->text().toInt();
    if (id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID invalide !");
        return;
    }

    bool ok = C.supprimer(id);
    if (ok) {
        QMessageBox::information(nullptr, tr("OK"),
                                 tr("Suppression effectuée\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        ui->tableViewClients->setModel(C.afficher());
    } else {
        QMessageBox::critical(nullptr, tr("Erreur"),
                              tr("Échec de la suppression.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
}

// ==================== MODIFIER ====================
void MainWindow::on_Modifier_clicked()
{
    int id = ui->id->text().toInt();
    QString nom = ui->nom->text().trimmed();
    QString prenom = ui->prenom->text().trimmed();
    QString telephone = ui->telephone->text().trimmed();
    QDate dateNaiss = ui->dn->date();
    QDate dateInscr = ui->di->date();

    QString dn = dateNaiss.toString("dd/MM/yyyy");
    QString di = dateInscr.toString("dd/MM/yyyy");

    if (id <= 0 || nom.isEmpty() || prenom.isEmpty() || telephone.isEmpty() || nom.length() < 3) {
        QMessageBox::warning(this, "Erreur",
                             "Remplissez tous les champs correctement ! Nom doit avoir au moins 3 caractères.");
        return;
    }

    if (dateNaiss >= dateInscr) {
        QMessageBox::warning(this, "Erreur",
                             "La date de naissance doit être antérieure à la date d'inscription.");
        return;
    }

    if (dateNaiss.addYears(18) > QDate::currentDate()) {
        QMessageBox::warning(this, "Erreur",
                             "Le client doit avoir au moins 18 ans.");
        return;
    }

    CLIENT client(id, nom, prenom, telephone, dn, di);
    bool ok = client.modifier();
    if (ok) {
        QMessageBox::information(nullptr, tr("OK"),
                                 tr("Modification effectuée\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        ui->tableViewClients->setModel(C.afficher());
    } else {
        QMessageBox::critical(nullptr, tr("Erreur"),
                              tr("Échec de la modification.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
}

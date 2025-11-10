#include "smart_electronic_repairshop.h"
#include "ui_smart_electronic_repairshop.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QRegularExpressionValidator>
#include <QDate>

menu_employer::menu_employer(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::menu_employer)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->menu_principale);

    if (!conn.createconnect()) {
        QMessageBox::critical(this, "Erreur", "Impossible de se connecter à la base !");
        return;
    }

    // Navigation
    connect(ui->client, &QPushButton::clicked, [this]() {
        goToPage(ui->menu_client);
        refreshClientTable();
    });
    connect(ui->retourC, &QPushButton::clicked, this, &menu_employer::on_retourC_clicked);

    // Boutons CRUD
    connect(ui->Ajouter, &QPushButton::clicked, this, &menu_employer::on_Ajouter_clicked);
    connect(ui->Supprimer, &QPushButton::clicked, this, &menu_employer::on_Supprimer_clicked);
    connect(ui->Modifier, &QPushButton::clicked, this, &menu_employer::on_Modifier_clicked);

    // Sélection tableau
    connect(ui->tableViewClients->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, [this]() {
                auto idx = ui->tableViewClients->currentIndex();
                if (!idx.isValid()) return;
                ui->id->setText(idx.siblingAtColumn(0).data().toString());
                ui->nom->setText(idx.siblingAtColumn(1).data().toString());
                ui->prenom->setText(idx.siblingAtColumn(2).data().toString());
                ui->telephone->setText(idx.siblingAtColumn(3).data().toString());
                ui->dn->setDate(QDate::fromString(idx.siblingAtColumn(4).data().toString(), "dd/MM/yyyy"));
                ui->di->setDate(QDate::fromString(idx.siblingAtColumn(5).data().toString(), "dd/MM/yyyy"));
            });

    setupClientValidators();
    refreshClientTable();
}

menu_employer::~menu_employer()
{
    conn.closeconnect();
    delete ui;
}

void menu_employer::goToPage(QWidget *page) { ui->stackedWidget->setCurrentWidget(page); }
void menu_employer::on_retourC_clicked() { goToPage(ui->menu_principale); }

void menu_employer::setupClientValidators()
{
    ui->id->setValidator(new QIntValidator(1, 999999999, this));
    QRegularExpression rx("[A-Za-zÀ-ÿ ]+");
    ui->nom->setValidator(new QRegularExpressionValidator(rx, this));
    ui->prenom->setValidator(new QRegularExpressionValidator(rx, this));
    ui->telephone->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]+"), this));
}

void menu_employer::refreshClientTable()
{
    ui->tableViewClients->setModel(CLIENT::afficher());
    ui->tableViewClients->resizeColumnsToContents();
}

void menu_employer::clearClientFields()
{
    ui->id->clear(); ui->nom->clear(); ui->prenom->clear(); ui->telephone->clear();
    ui->dn->setDate(QDate::currentDate().addYears(-18));
    ui->di->setDate(QDate::currentDate());
}

// === AJOUTER ===
void menu_employer::on_Ajouter_clicked()
{
    int id = ui->id->text().toInt();
    QString nom = ui->nom->text().trimmed();
    QString prenom = ui->prenom->text().trimmed();
    QString tel = ui->telephone->text().trimmed();
    QString dn = ui->dn->date().toString("dd/MM/yyyy");
    QString di = ui->di->date().toString("dd/MM/yyyy");

    if (id <= 0 || nom.isEmpty() || prenom.isEmpty() || tel.isEmpty() || nom.length() < 3) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs correctement.");
        return;
    }
    if (ui->dn->date() >= ui->di->date()) {
        QMessageBox::warning(this, "Erreur", "Date de naissance invalide.");
        return;
    }
    if (ui->dn->date().addYears(18) > QDate::currentDate()) {
        QMessageBox::warning(this, "Erreur", "Le client doit avoir au moins 18 ans.");
        return;
    }

    CLIENT c(id, nom, prenom, tel, dn, di);
    if (c.ajouter()) {
        QMessageBox::information(this, "Succès", "Client ajouté !");
        refreshClientTable();
        clearClientFields();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout (ID existe ?).");
    }
}

// === SUPPRIMER ===
void menu_employer::on_Supprimer_clicked()
{
    int id = ui->id->text().toInt();
    if (id <= 0) {
        QMessageBox::warning(this, "Erreur", "Sélectionnez un client !");
        return;
    }
    if (QMessageBox::question(this, "Confirmer", "Supprimer ce client ?") == QMessageBox::Yes) {
        if (CLIENT::supprimer(id)) {
            QMessageBox::information(this, "Succès", "Client supprimé !");
            refreshClientTable();
            clearClientFields();
        }
    }
}

// === MODIFIER ===
void menu_employer::on_Modifier_clicked()
{
    int id = ui->id->text().toInt();
    if (id <= 0) return;

    CLIENT c(id, ui->nom->text().trimmed(), ui->prenom->text().trimmed(),
             ui->telephone->text().trimmed(),
             ui->dn->date().toString("dd/MM/yyyy"),
             ui->di->date().toString("dd/MM/yyyy"));

    if (c.modifier()) {
        QMessageBox::information(this, "Succès", "Client modifié !");
        refreshClientTable();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification.");
    }
}

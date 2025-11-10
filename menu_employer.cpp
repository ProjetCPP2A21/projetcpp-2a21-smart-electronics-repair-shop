#include "menu_employer.h"
#include "ui_menu_employer.h"

// --- INCLUDES POUR LA VALIDATION ---
#include <QRegularExpressionValidator> // Pour ID, Email, Tel
#include <QRegularExpression>          // Pour ID, Email, Tel
#include <QDoubleValidator>            // <-- AJOUTÉ POUR LE SALAIRE
// ------------------------------------

#include <QPushButton>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDate>

menu_employer::menu_employer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::menu_employer)
{
    ui->setupUi(this);

    // --- MISE EN PLACE DES VALIDATEURS DE SAISIE ---

    // 1. Validation de l'ID: Accepte uniquement des chiffres
    ui->lineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]+"), this));

    // 2. Validation du Téléphone: Accepte de 0 à 8 chiffres
    ui->lineEdit_tel->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,8}"), this));

    // 3. Validation de l'Email:
    QRegularExpression emailRegex(R"(^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}$)");
    emailRegex.setPatternOptions(QRegularExpression::CaseInsensitiveOption); // Ignore maj/min
    ui->lineEdit_email->setValidator(new QRegularExpressionValidator(emailRegex, this));

    // 4. Validation du Salaire: (FLOTTANT / DOUBLE) <-- NOUVEL AJOUT
    // Autorise un nombre flottant (ex: 1500.50)
    // Ici, de 0.00 à 99,999,999.00 avec 2 décimales.
    ui->salaire->setValidator(new QDoubleValidator(0.0, 99999999.0, 2, this));

    // --- FIN DES VALIDATEURS ---


    // Configuration initiale des pages
    ui->stackedWidget->setCurrentWidget(ui->page_2);

    // Connexions pour la navigation
    connect(ui->employer, &QPushButton::clicked, this, [this]() { goToPage(ui->page); });
    connect(ui->retour_4, &QPushButton::clicked, this, [this]() { goToPage(ui->page_2); });

    // Configuration de la vue (Tableau)
    rafraichir();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSortingEnabled(true);
}

menu_employer::~menu_employer()
{
    delete ui;
}

// Navigue vers la page spécifiée
void menu_employer::goToPage(QWidget *page)
{
    ui->stackedWidget->setCurrentWidget(page);
}

// Met à jour l'affichage du QTableView
void menu_employer::rafraichir()
{
    QSqlQueryModel* model = emp.afficher();
    if (model) ui->tableView->setModel(model);
}

// Vide tous les champs du formulaire
void menu_employer::viderFormulaire()
{
    ui->lineEdit->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_email->clear();
    ui->lineEdit_tel->clear();
    ui->lineEdit_date->setDate(QDate::currentDate());
    ui->dateEdit_recrutement->setDate(QDate::currentDate());
    ui->poste->clear();
    ui->salaire->clear();
}

/**
 * @brief Vérifie que les champs requis (ID, Nom, Prénom) ne sont pas vides.
 * @return true si les champs requis sont remplis, sinon false.
 */
bool menu_employer::validerChampsRequis()
{
    if (ui->lineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Champ Requis", "L'ID ne peut pas être vide.");
        ui->lineEdit->setFocus();
        return false;
    }
    if (ui->lineEdit_3->text().isEmpty()) {
        QMessageBox::warning(this, "Champ Requis", "Le Nom ne peut pas être vide.");
        ui->lineEdit_3->setFocus();
        return false;
    }
    if (ui->lineEdit_6->text().isEmpty()) {
        QMessageBox::warning(this, "Champ Requis", "Le Prénom ne peut pas être vide.");
        ui->lineEdit_6->setFocus();
        return false;
    }

    // Vérifie si l'email, s'il n'est pas vide, est dans un format acceptable
    if (!ui->lineEdit_email->hasAcceptableInput() && !ui->lineEdit_email->text().isEmpty()) {
        QMessageBox::warning(this, "Format Invalide", "Le format de l'email est incorrect.");
        ui->lineEdit_email->setFocus();
        return false;
    }

    return true; // Tous les champs requis sont valides
}

// --- SLOTS ---

// Bouton AJOUTER
void menu_employer::on_pushButton_5_clicked()
{
    // 1. Vérifier si les champs obligatoires sont remplis
    if (!validerChampsRequis()) {
        return; // Arrête l'ajout si la validation échoue
    }

    // 2. Récupérer les données
    emp.setId(ui->lineEdit->text());
    emp.setNom(ui->lineEdit_3->text());
    emp.setPrenom(ui->lineEdit_6->text());
    emp.setEmail(ui->lineEdit_email->text());
    emp.setTelephone(ui->lineEdit_tel->text().toInt());
    emp.setDateNaissance(ui->lineEdit_date->date());
    emp.setDateRecrutement(ui->dateEdit_recrutement->date());
    emp.setPoste(ui->poste->text());
    emp.setSalaire(ui->salaire->text().toDouble()); // Convertit le texte en double

    // 3. Exécuter l'ajout
    if (emp.ajouter()) {
        rafraichir();
        QMessageBox::information(this, "Succès", "Employé ajouté !");
        viderFormulaire();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec ajout (L'ID existe déjà ?)");
    }
}

// Bouton SUPPRIMER
void menu_employer::on_btnSupprimer_clicked()
{
    QString id = ui->lineEdit->text();

    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir ou sélectionner un ID à supprimer.");
        return;
    }

    if (emp.supprimer(id)) {
        rafraichir();
        QMessageBox::information(this, "Succès", "Supprimé !");
        viderFormulaire();
    } else {
        QMessageBox::warning(this, "Erreur", "ID introuvable.");
    }
}

// Bouton MODIFIER
void menu_employer::on_btnModifier_clicked()
{
    // 1. Vérifier si les champs obligatoires sont remplis
    if (!validerChampsRequis()) {
        return; // Arrête la modification si la validation échoue
    }

    // 2. Récupérer les données
    emp.setId(ui->lineEdit->text());
    emp.setNom(ui->lineEdit_3->text());
    emp.setPrenom(ui->lineEdit_6->text());
    emp.setEmail(ui->lineEdit_email->text());
    emp.setTelephone(ui->lineEdit_tel->text().toInt());
    emp.setDateNaissance(ui->lineEdit_date->date());
    emp.setDateRecrutement(ui->dateEdit_recrutement->date());
    emp.setPoste(ui->poste->text());
    emp.setSalaire(ui->salaire->text().toDouble()); // Convertit le texte en double

    // 3. Exécuter la modification
    if (emp.modifier()) {
        rafraichir();
        QMessageBox::information(this, "Succès", "Modifié !");
        viderFormulaire();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec modification (ID introuvable ?).");
    }
}

// Champ de RECHERCHE
void menu_employer::on_lineEdit_recherche_textChanged(const QString &text)
{
    if (text.isEmpty()) {
        rafraichir();
    } else {
        ui->tableView->setModel(emp.rechercher(text));
    }
}

// Clic sur le TABLEAU (pour pré-remplir le formulaire)
void menu_employer::on_tableView_clicked(const QModelIndex &index)
{
    // Récupère l'ID de la première colonne (colonne 0) de la ligne cliquée
    QString id = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toString();
    chargerFormulaire(id); // Charge les données de cet ID dans le formulaire
}

// Charge les données d'un employé (par ID) dans le formulaire
void menu_employer::chargerFormulaire(const QString& id)
{
    QSqlQuery q;
    q.prepare("SELECT * FROM EMPLOYES WHERE ID_EMPLOYE = :id");
    q.bindValue(":id", id);
    if (q.exec() && q.next()) {
        ui->lineEdit->setText(q.value("ID_EMPLOYE").toString());
        ui->lineEdit_3->setText(q.value("NOMEMPLOYE").toString());
        ui->lineEdit_6->setText(q.value("PRENOM").toString());
        ui->lineEdit_email->setText(q.value("EMAIL").toString());
        ui->lineEdit_tel->setText(q.value("TELEPHONE").toString());
        ui->lineEdit_date->setDate(q.value("DATENAISSANCE").toDate());
        ui->dateEdit_recrutement->setDate(q.value("DATERECRUTEMENT").toDate());
        ui->poste->setText(q.value("POST").toString());
        ui->salaire->setText(q.value("SALAIRE").toString()); // Charge le salaire
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDate>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QSqlError>
#include "appareil.h"

// Constructeur
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // --- CORRECTION : 10 colonnes ---
    ui->tablewidget_Appareils->setColumnCount(10);

    // --- CORRECTION : En-têtes sans ID Client et ID Employé ---
    QStringList headers = {"ID", "Type", "Marque", "Modèle", "Défaut",
                           "Date Entrée", "Statut", "Remarques", "Prix Estimé",
                           "Date Estimée"};
    ui->tablewidget_Appareils->setHorizontalHeaderLabels(headers);

    // Assurez-vous d'avoir ajouté ces items dans Qt Designer pour la ComboBox
    // ui->comboBox_Statut->addItems({"en cours", "en attente", "reparer"});

    chargerTable();
}

// Destructeur
MainWindow::~MainWindow()
{
    delete ui;
}


/**
 * @brief Remplit le QTableWidget avec les données de la BDD.
 */
void MainWindow::chargerTable()
{
    // Vide le tableau avant de le remplir
    ui->tablewidget_Appareils->setRowCount(0);

    QSqlQuery query;

    // --- CORRECTION : Nom de table APPAREILS (avec S) et sans schéma ---
    if (!query.exec("SELECT * FROM APPAREILS"))
    {
        QMessageBox::critical(this, "Erreur", "Impossible de charger les données: " + query.lastError().text());
        return;
    }

    int row = 0;
    while(query.next())
    {
        ui->tablewidget_Appareils->insertRow(row);
        ui->tablewidget_Appareils->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // ID_APP
        ui->tablewidget_Appareils->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // TYPE
        ui->tablewidget_Appareils->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // MARQUE
        ui->tablewidget_Appareils->setItem(row, 3, new QTableWidgetItem(query.value(3).toString())); // MODELE
        ui->tablewidget_Appareils->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // DEFAULTDECLARE
        ui->tablewidget_Appareils->setItem(row, 5, new QTableWidgetItem(query.value(5).toDate().toString("dd/MM/yyyy"))); // DATEENTREE
        ui->tablewidget_Appareils->setItem(row, 6, new QTableWidgetItem(query.value(6).toString())); // STATUT
        ui->tablewidget_Appareils->setItem(row, 7, new QTableWidgetItem(query.value(7).toString())); // REMARQUES
        ui->tablewidget_Appareils->setItem(row, 8, new QTableWidgetItem(query.value(8).toString())); // PRIXESTIME
        ui->tablewidget_Appareils->setItem(row, 9, new QTableWidgetItem(query.value(9).toDate().toString("dd/MM/yyyy"))); // DATEESTIME
        row++;
    }
}


/**
 * @brief Slot automatique pour le clic sur "pushButton_Ajouter"
 */
void MainWindow::on_pushButton_Ajouter_clicked()
{
    // 1. Récupérer les données depuis l'interface
    QString id = ui->lineEdit_ID->text();
    QString type = ui->lineEdit_Type->text();
    QString marque = ui->lineEdit_Marque->text();
    QString modele = ui->lineEdit_Modele->text();
    QString defaut = ui->lineEdit_Defaut->text();
    QDate dateEntree = ui->dateEdit_Entree->date();
    QString statut = ui->comboBox_Statut->currentText(); // Utilisation de la ComboBox
    QString remarques = ui->lineEdit_Remarques->text();
    QString prixTexte = ui->lineEdit_Prix->text();
    QDate dateEstime = ui->dateEdit_Estime->date();

    // -------------------------------------------------------------
    // --- DÉBUT DES CONTRÔLES DE SAISIE ---
    // -------------------------------------------------------------

    // === Validation de l'ID ===
    if (id.isEmpty())
    {
        QMessageBox::warning(this, "Champ manquant", "L'identifiant (ID) ne peut pas être vide.");
        ui->lineEdit_ID->setFocus();
        return;
    }

    bool idEstEntier;
    id.toInt(&idEstEntier);
    if (!idEstEntier)
    {
        QMessageBox::warning(this, "Format invalide", "L'identifiant (ID) doit être un nombre entier (ex: 123).");
        ui->lineEdit_ID->setFocus();
        return;
    }

    // === Validation des autres champs ===
    if (type.isEmpty())
    {
        QMessageBox::warning(this, "Champ manquant", "Le champ 'Type' ne peut pas être vide.");
        ui->lineEdit_Type->setFocus();
        return;
    }
    if (marque.isEmpty())
    {
        QMessageBox::warning(this, "Champ manquant", "Le champ 'Marque' ne peut pas être vide.");
        ui->lineEdit_Marque->setFocus();
        return;
    }
    if (modele.isEmpty())
    {
        QMessageBox::warning(this, "Champ manquant", "Le champ 'Modèle' ne peut pas être vide.");
        ui->lineEdit_Modele->setFocus();
        return;
    }

    // === Validation du prix ===
    bool prixEstValide;
    float prix = prixTexte.toFloat(&prixEstValide);

    if (!prixEstValide || prix < 0)
    {
        QMessageBox::warning(this, "Format invalide", "Le prix estimé doit être un nombre positif (ex: 150.50).");
        ui->lineEdit_Prix->setFocus();
        return;
    }

    // === Validation des dates ===
    if (dateEstime < dateEntree)
    {
        QMessageBox::warning(this, "Date invalide", "La date estimée ne peut pas être antérieure à la date d'entrée.");
        ui->dateEdit_Estime->setFocus();
        return;
    }

    // -------------------------------------------------------------
    // --- FIN DES CONTRÔLES DE SAISIE ---
    // -------------------------------------------------------------

    // 2. Créer l'objet Appareil
    Appareil A_new;
    A_new.setID(id);
    A_new.setType(type);
    A_new.setMarque(marque);
    A_new.setModele(modele);
    A_new.setDefaultDeclare(defaut);
    A_new.setDateEntree(dateEntree);
    A_new.setStatut(statut);
    A_new.setRemarques(remarques);
    A_new.setPrixEstime(prix);
    A_new.setDateEstime(dateEstime);

    // 3. Appeler la fonction d'ajout
    bool success = A_new.ajouter();

    // 4. Donner un feedback
    if(success)
    {
        QMessageBox::information(this, "Succès", "Appareil ajouté avec succès.");
        chargerTable(); // Mettre à jour le tableau
    }
    else
    {
        QMessageBox::critical(this, "Échec", "L'ajout de l'appareil a échoué.\n\nVérifiez que cet ID n'est pas déjà utilisé.");
    }
}

/**
 * @brief Slot automatique pour le clic sur "pushButton_Supprimer"
 */
/**
 * @brief Slot automatique pour le clic sur "pushButton_Modifier"
 */
void MainWindow::on_pushButton_Modifier_clicked()
{
    // 1. Récupérer les données depuis l'interface
    QString id = ui->lineEdit_ID->text();
    QString type = ui->lineEdit_Type->text();
    QString marque = ui->lineEdit_Marque->text();
    QString modele = ui->lineEdit_Modele->text();
    QString defaut = ui->lineEdit_Defaut->text();
    QDate dateEntree = ui->dateEdit_Entree->date();
    QString statut = ui->comboBox_Statut->currentText(); // Utilisation de la ComboBox
    QString remarques = ui->lineEdit_Remarques->text();
    QString prixTexte = ui->lineEdit_Prix->text();
    QDate dateEstime = ui->dateEdit_Estime->date();

    // -------------------------------------------------------------
    // --- CONTRÔLES DE SAISIE (identiques à l'ajout) ---
    // -------------------------------------------------------------

    // === Validation de l'ID ===
    if (id.isEmpty())
    {
        QMessageBox::warning(this, "Champ manquant", "Veuillez sélectionner un appareil. L'ID ne peut pas être vide.");
        ui->lineEdit_ID->setFocus();
        return;
    }

    bool idEstEntier;
    id.toInt(&idEstEntier);
    if (!idEstEntier)
    {
        QMessageBox::warning(this, "Format invalide", "L'identifiant (ID) doit être un nombre entier.");
        ui->lineEdit_ID->setFocus();
        return;
    }

    // === Validation des autres champs ===
    if (type.isEmpty())
    {
        QMessageBox::warning(this, "Champ manquant", "Le champ 'Type' ne peut pas être vide.");
        ui->lineEdit_Type->setFocus();
        return;
    }
    if (marque.isEmpty())
    {
        QMessageBox::warning(this, "Champ manquant", "Le champ 'Marque' ne peut pas être vide.");
        ui->lineEdit_Marque->setFocus();
        return;
    }
    if (modele.isEmpty())
    {
        QMessageBox::warning(this, "Champ manquant", "Le champ 'Modèle' ne peut pas être vide.");
        ui->lineEdit_Modele->setFocus();
        return;
    }

    // === Validation du prix ===
    bool prixEstValide;
    float prix = prixTexte.toFloat(&prixEstValide);

    if (!prixEstValide || prix < 0)
    {
        QMessageBox::warning(this, "Format invalide", "Le prix estimé doit être un nombre positif (ex: 150.50).");
        ui->lineEdit_Prix->setFocus();
        return;
    }

    // === Validation des dates ===
    if (dateEstime < dateEntree)
    {
        QMessageBox::warning(this, "Date invalide", "La date estimée ne peut pas être antérieure à la date d'entrée.");
        ui->dateEdit_Estime->setFocus();
        return;
    }

    // -------------------------------------------------------------
    // --- FIN DES CONTRÔLES DE SAISIE ---
    // -------------------------------------------------------------

    // 2. Créer l'objet Appareil
    Appareil A_mod; // A_mod pour "modifier"
    A_mod.setID(id);
    A_mod.setType(type);
    A_mod.setMarque(marque);
    A_mod.setModele(modele);
    A_mod.setDefaultDeclare(defaut);
    A_mod.setDateEntree(dateEntree);
    A_mod.setStatut(statut);
    A_mod.setRemarques(remarques);
    A_mod.setPrixEstime(prix);
    A_mod.setDateEstime(dateEstime);

    // 3. Appeler la fonction de modification
    bool success = A_mod.modifier();

    // 4. Donner un feedback
    if(success)
    {
        QMessageBox::information(this, "Succès", "Appareil modifié avec succès.");
        chargerTable(); // Mettre à jour le tableau
    }
    else
    {
        QMessageBox::critical(this, "Échec", "La modification de l'appareil a échoué.\n\nVérifiez que l'ID existe bien.");
    }
}

void MainWindow::on_pushButton_Supprimer_clicked()
{
    // 1. Récupérer l'ID à supprimer
    QString id = ui->lineEdit_ID->text();

    // 2. Vérifier si l'ID n'est pas vide
    if(id.isEmpty())
    {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un appareil ou saisir un ID à supprimer.");
        return;
    }

    // 3. Confirmer la suppression
    QMessageBox::StandardButton reponse;
    reponse = QMessageBox::question(this, "Confirmer", "Êtes-vous sûr de vouloir supprimer cet appareil ?",
                                    QMessageBox::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes)
    {
        // 4. Tenter la suppression
        Appareil A_temp;
        bool success = A_temp.supprimer(id);

        // 5. Donner un feedback
        if(success)
        {
            QMessageBox::information(this, "Succès", "Appareil supprimé.");
            chargerTable();
        }
        else
        {
            QMessageBox::critical(this, "Échec", "La suppression a échoué.\nVérifiez que l'ID existe.");
        }
    }
}


/**
 * @brief Se déclenche quand l'utilisateur clique sur une cellule du tableau.
 * Remplit les champs de formulaire avec les données de la ligne cliquée.
 */
void MainWindow::on_tablewidget_Appareils_cellClicked(int row, int column)
{
    // 'column' n'est pas utilisé ici, nous ignorons sa valeur
    (void)column;

    // 1. Récupérer les données de la ligne cliquée
    QString id = ui->tablewidget_Appareils->item(row, 0)->text();
    QString type = ui->tablewidget_Appareils->item(row, 1)->text();
    QString marque = ui->tablewidget_Appareils->item(row, 2)->text();
    QString modele = ui->tablewidget_Appareils->item(row, 3)->text();
    QString defaut = ui->tablewidget_Appareils->item(row, 4)->text();
    QString dateEntreeStr = ui->tablewidget_Appareils->item(row, 5)->text();
    QString statut = ui->tablewidget_Appareils->item(row, 6)->text();
    QString remarques = ui->tablewidget_Appareils->item(row, 7)->text();
    QString prix = ui->tablewidget_Appareils->item(row, 8)->text();
    QString dateEstimeStr = ui->tablewidget_Appareils->item(row, 9)->text();

    // 2. Convertir les dates
    QDate dateEntree = QDate::fromString(dateEntreeStr, "dd/MM/yyyy");
    QDate dateEstime = QDate::fromString(dateEstimeStr, "dd/MM/yyyy");

    // 3. Mettre les données dans les champs de l'interface
    ui->lineEdit_ID->setText(id);
    ui->lineEdit_Type->setText(type);
    ui->lineEdit_Marque->setText(marque);
    ui->lineEdit_Modele->setText(modele);
    ui->lineEdit_Defaut->setText(defaut);
    ui->dateEdit_Entree->setDate(dateEntree);
    ui->comboBox_Statut->setCurrentText(statut); // Utilisation de la ComboBox
    ui->lineEdit_Remarques->setText(remarques);
    ui->lineEdit_Prix->setText(prix);
    ui->dateEdit_Estime->setDate(dateEstime);
}

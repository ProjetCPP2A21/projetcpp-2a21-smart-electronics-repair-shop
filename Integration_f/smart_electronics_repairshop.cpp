#include "smart_electronics_repairshop.h"
#include "ui_smart_electronics_repairshop.h"
#include <QPushButton>
#include "fournisseur.h"
#include "client.h"
#include "employe.h"
#include <QRegularExpressionValidator> // Pour ID, Email, Tel
#include <QRegularExpression>          // Pour ID, Email, Tel
#include <QDoubleValidator>
#include "stock.h"
osana_dashboard::osana_dashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::osana_dashboard)
{

    ui->setupUi(this);
    fournisseur *gestionFournisseurs = new fournisseur(ui->menu_fournisseur, this); //fournisseur
    client *gestionClients = new client(ui->menu_client, this); //client
    ui->stackedWidget->setCurrentWidget(ui->menu_principale);
    connect(ui->employe, &QPushButton::clicked, [this]() {
        goToPage(ui->menu_employe);
    });
    //connexions widgets:
    connect(ui->retour_6, &QPushButton::clicked, this, [this]() { goToPage(ui->menu_principale); });
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
    connect(ui->menu_fournisseur->findChild<QPushButton*>("btnAjouter_4"), &QPushButton::clicked,
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
    connect(ui->menu_fournisseur->findChild<QPushButton*>("btnStatistiques_2"),&QPushButton::clicked,
            gestionFournisseurs, &fournisseur::afficherStatistiques);
    connect(ui->menu_fournisseur->findChild<QPushButton*>("PDF_2"),&QPushButton::clicked,
            gestionFournisseurs, &fournisseur::exporterPDF);
    /*connect(ui->menu_fournisseur->findChild<QPushButton*>("mai_f"),&QPushButton::clicked,
            gestionFournisseurs, &fournisseur::afficherTopEntreprise);
    */
    connect(ui->menu_fournisseur->findChild<QPushButton*>("mai_1"),&QPushButton::clicked,
            gestionFournisseurs, &fournisseur::afficherScoreFournisseurMA1);
    connect(ui->menu_fournisseur->findChild<QPushButton*>("mai_2"),&QPushButton::clicked,
            gestionFournisseurs, &fournisseur::afficherFournisseursPrioritairesMA2);

    //connexions client:
    connect(ui->menu_client->findChild<QPushButton*>("btnAjouterClient"), &QPushButton::clicked,
            gestionClients, &client::ajouterClient);
    connect(ui->menu_client->findChild<QPushButton*>("btnRechercherClient"), &QPushButton::clicked,
            gestionClients, &client::rechercherClientParId);
    connect(ui->menu_client->findChild<QPushButton*>("btnModifierClient"), &QPushButton::clicked,
            gestionClients, &client::modifierClient);
    connect(ui->menu_client->findChild<QPushButton*>("btnSupprimerClient"), &QPushButton::clicked,
            gestionClients, &client::supprimerClient);
    connect(ui->menu_client->findChild<QPushButton*>("btnMajClient"), &QPushButton::clicked,
            gestionClients, &client::rafraichirListeClients);
    connect(ui->menu_client->findChild<QPushButton*>("btnTriClient"), &QPushButton::clicked,
            gestionClients, &client::trierParNom);
    //connexions employe:
    //validateurs employe:
    // 1. Validation de l'ID: Accepte uniquement des chiffres
    ui->lineEdit_7->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]+"), this));

    // 2. Validation du Téléphone: Accepte de 0 à 8 chiffres
    ui->lineEdit_4->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,8}"), this));

    // 3. Validation de l'Email:
    QRegularExpression emailRegex(R"(^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}$)");
    emailRegex.setPatternOptions(QRegularExpression::CaseInsensitiveOption); // Ignore maj/min
    ui->lineEdit_email_2->setValidator(new QRegularExpressionValidator(emailRegex, this));

    // 4. Validation du Salaire: (FLOTTANT / DOUBLE) <-- NOUVEL AJOUT
    // Autorise un nombre flottant (ex: 1500.50)
    // Ici, de 0.00 à 99,999,999.00 avec 2 décimales.
    ui->salaire_2->setValidator(new QDoubleValidator(0.0, 99999999.0, 2, this));

    // --- FIN DES VALIDATEURS ---

}

osana_dashboard::~osana_dashboard()
{
    delete ui;
}
void osana_dashboard::rafraichir()
{
    QSqlQueryModel* model = emp.afficher();
    if (model) ui->tableView_2->setModel(model);
}

// Vide tous les champs du formulaire
void osana_dashboard::viderFormulaire()
{
    ui->lineEdit_7->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_email_2->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_date_2->setDate(QDate::currentDate());
    ui->dateEdit_recrutement_2->setDate(QDate::currentDate());
    ui->poste_2->clear();
    ui->salaire_2->clear();
}

// Vérifie que les champs requis (ID, Nom, Prénom) ne sont pas vides.
//return true si les champs requis sont remplis, sinon false.
bool osana_dashboard::validerChampsRequis()
{
    if (ui->lineEdit_7->text().isEmpty()) {
        QMessageBox::warning(this, "Champ Requis", "L'ID ne peut pas être vide.");
        ui->lineEdit_7->setFocus();
        return false;
    }
    if (ui->lineEdit_4->text().isEmpty()) {
        QMessageBox::warning(this, "Champ Requis", "Le Nom ne peut pas être vide.");
        ui->lineEdit_4->setFocus();
        return false;
    }
    if (ui->lineEdit_8->text().isEmpty()) {
        QMessageBox::warning(this, "Champ Requis", "Le Prénom ne peut pas être vide.");
        ui->lineEdit_8->setFocus();
        return false;
    }

    // Vérifie si l'email, s'il n'est pas vide, est dans un format acceptable
    if (!ui->lineEdit_email_2->hasAcceptableInput() && !ui->lineEdit_email_2->text().isEmpty()) {
        QMessageBox::warning(this, "Format Invalide", "Le format de l'email est incorrect.");
        ui->lineEdit_email_2->setFocus();
        return false;
    }

    return true; // Tous les champs requis sont valides
}

// --- SLOTS ---

// Bouton AJOUTER
void osana_dashboard::on_pushButton_5_clicked()
{
    // 1. Vérifier si les champs obligatoires sont remplis
    if (!validerChampsRequis()) {
        return; // Arrête l'ajout si la validation échoue
    }

    // 2. Récupérer les données
    emp.setId(ui->lineEdit_7->text());
    emp.setNom(ui->lineEdit_4->text());
    emp.setPrenom(ui->lineEdit_8->text());
    emp.setEmail(ui->lineEdit_email_2->text());
    emp.setTelephone(ui->lineEdit_4->text().toInt());
    emp.setDateNaissance(ui->lineEdit_date_2->date());
    emp.setDateRecrutement(ui->dateEdit_recrutement_2->date());
    emp.setPoste(ui->poste_2->text());
    emp.setSalaire(ui->salaire_2->text().toDouble()); // Convertit le texte en double

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
void osana_dashboard::on_btnSupprimer_clicked()
{
    QString id = ui->lineEdit_7->text();

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
void osana_dashboard::on_btnModifier_clicked()
{
    // 1. Vérifier si les champs obligatoires sont remplis
    if (!validerChampsRequis()) {
        return; // Arrête la modification si la validation échoue
    }

    // 2. Récupérer les données
    emp.setId(ui->lineEdit_7->text());
    emp.setNom(ui->lineEdit_4->text());
    emp.setPrenom(ui->lineEdit_8->text());
    emp.setEmail(ui->lineEdit_email_2->text());
    emp.setTelephone(ui->lineEdit_4->text().toInt());
    emp.setDateNaissance(ui->lineEdit_date_2->date());
    emp.setDateRecrutement(ui->dateEdit_recrutement_2->date());
    emp.setPoste(ui->poste_2->text());
    emp.setSalaire(ui->salaire_2->text().toDouble()); // Convertit le texte en double

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
void osana_dashboard::on_lineEdit_recherche_textChanged(const QString &text)
{
    if (text.isEmpty()) {
        rafraichir();
    } else {
        ui->tableView_2->setModel(emp.rechercher(text));
    }
}

// Clic sur le TABLEAU (pour pré-remplir le formulaire)
void osana_dashboard::on_tableView_2_clicked(const QModelIndex &index)
{
    // Récupère l'ID de la première colonne (colonne 0) de la ligne cliquée
    QString id = ui->tableView_2->model()->data(ui->tableView_2->model()->index(index.row(), 0)).toString();
    chargerFormulaire(id); // Charge les données de cet ID dans le formulaire
}

// Charge les données d'un employé (par ID) dans le formulaire
void osana_dashboard::chargerFormulaire(const QString& id)
{
    QSqlQuery q;
    q.prepare("SELECT * FROM EMPLOYES WHERE ID_EMPLOYE = :id");
    q.bindValue(":id", id);
    if (q.exec() && q.next()) {
        ui->lineEdit_7->setText(q.value("ID_EMPLOYE").toString());
        ui->lineEdit_4->setText(q.value("NOMEMPLOYE").toString());
        ui->lineEdit_8->setText(q.value("PRENOM").toString());
        ui->lineEdit_email_2->setText(q.value("EMAIL").toString());
        ui->lineEdit_4->setText(q.value("TELEPHONE").toString());
        ui->lineEdit_date_2->setDate(q.value("DATENAISSANCE").toDate());
        ui->dateEdit_recrutement_2->setDate(q.value("DATERECRUTEMENT").toDate());
        ui->poste_2->setText(q.value("POST").toString());
        ui->salaire_2->setText(q.value("SALAIRE").toString()); // Charge le salaire
    }
}
void osana_dashboard::on_btajouter_stock_3_clicked()
{
    QString idText = ui->lineEdit_IDstock_3->text().trimmed();


    if (idText.isEmpty()) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez saisir un identifiant (ID) !");
        ui->lineEdit_IDstock_3->setFocus();
        return;
    }


    bool okId;
    int id = idText.toInt(&okId);
    if (!okId || idText.contains(QRegularExpression("[^0-9]"))) {
        QMessageBox::critical(this, "Erreur de saisie",
                              "L'ID doit contenir uniquement des chiffres (pas de lettres ni de symboles).");
        ui->lineEdit_IDstock_3->setFocus();
        return;
    }


    QString nom = ui->lineEdit_nomstock_3->text();
    QString reference = ui->lineEdit_referencestock_3->text();
    QString categorie = ui->lineEdit_categorie_3->text();
    QString quantite = ui->lineEdit_quantite_3->text();
    QString prixachat = ui->lineEdit_prixachat_3->text();
    QString prixvente = ui->lineEdit_18->text();
    QString fournisseur = ui->lineEdit_19->text();
    QString datelivraison = ui->dateEdit_3->date().toString("yyyy-MM-dd");

    QString quantiteText = ui->lineEdit_quantite_3->text();


    bool ok;
    int quantiteInt = quantiteText.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "La quantité doit être un nombre entier !");
        return;
    }



    prixachat.replace(",", ".");
    prixvente.replace(",", ".");
    bool ok1 = true, ok2 = true;
    if (!prixachat.trimmed().isEmpty()) prixachat.toDouble(&ok1);
    if (!prixvente.trimmed().isEmpty()) prixvente.toDouble(&ok2);
    if (!ok1 || !ok2) {
        QMessageBox::critical(this, "Erreur de saisie",
                              "Veuillez entrer des valeurs numériques valides pour les prix !");
        return;
    }


    stock tm(id, nom, reference, categorie, quantite, prixachat, prixvente, fournisseur, datelivraison);

    bool test = tm.ajouter();
    if (test) {
        ui->tableView_2->setModel(tm.afficher());
        QMessageBox::information(this, "Succès", "Ajout effectué avec succès !");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout !");
    }
}

void osana_dashboard::on_btsupprimer_stock_3_clicked()
{
    int id = ui->lineEdit_IDstock_3->text().toInt();
    bool test = tm.supprimer(id);

    if (test)
    {


        ui->tableView_2->setModel(tm.afficher());
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\nClick Cancel to exit."),
                                 QMessageBox::Cancel);



    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Erreur"),
                              QObject::tr("Suppression non effectuée\nClick Cancel to exit."),
                              QMessageBox::Cancel);
    }
}

void osana_dashboard::on_btmodifier_stock_3_clicked()
{
    int id = ui->lineEdit_IDstock_3->text().toInt();
    QString nom = ui->lineEdit_nomstock_3->text();
    QString reference = ui->lineEdit_referencestock_3->text();
    QString categorie = ui->lineEdit_categorie_3->text();
    QString quantite = ui->lineEdit_quantite_3->text();
    QString prixachat = ui->lineEdit_prixachat_3->text();
    QString prixvente = ui->lineEdit_18->text();
    QString fournisseur = ui->lineEdit_19->text();
    QString datelivraison = ui->dateEdit_3->date().toString("yyyy-MM-dd");
    QString quantiteText = ui->lineEdit_quantite_3->text();


    bool ok;
    int quantiteInt = quantiteText.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "La quantité doit être un nombre entier !");
        return;
    }

    prixachat.replace(",", ".");
    prixvente.replace(",", ".");
    bool ok1 = true, ok2 = true;
    if (!prixachat.trimmed().isEmpty()) prixachat.toDouble(&ok1);
    if (!prixvente.trimmed().isEmpty()) prixvente.toDouble(&ok2);
    if (!ok1 || !ok2) {
        QMessageBox::critical(this, "Erreur de saisie",
                              "Veuillez entrer des valeurs numériques valides pour les prix !");
        return;
    }
    stock s(id, nom, reference, categorie, quantite, prixachat, prixvente, fournisseur, datelivraison);

    bool test = s.modifier();

    if (test) {
        QMessageBox::information(this, "Succès", "Modification effectuée !");
        ui->tableView_2->setModel(s.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification !");
    }
}

void osana_dashboard::goToPage(QWidget *page)
{
    ui->stackedWidget->setCurrentWidget(page);
}

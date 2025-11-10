#include "client.h"
#include <QRegularExpression>
#include <QDate>

// Constructeur
client::client(QWidget *parentWidget, QObject *parent)
    : QObject(parent), page(parentWidget)
{
    auto table = page->findChild<QTableWidget*>("clientTabWidget");
    if (table) {
        table->setColumnCount(7);
        QStringList headers = { "ID", "Nom", "Prénom", "Téléphone", "Email", "Naissance", "Inscription" };
        table->setHorizontalHeaderLabels(headers);
    }

    rafraichirListeClients();
}

// Validation simple
bool client::validerChamps(const QString &email, const QString &telephone, const QString &nom, const QString &prenom)
{
    if (nom.trimmed().isEmpty() || prenom.trimmed().isEmpty()) {
        QMessageBox::warning(page, "Erreur", "Nom et prénom obligatoires.");
        return false;
    }

    QRegularExpression regexEmail(R"(^[\w\.-]+@[\w\.-]+\.[a-zA-Z]{2,}$)");
    if (!regexEmail.match(email).hasMatch()) {
        QMessageBox::warning(page, "Erreur", "Adresse email invalide.");
        return false;
    }

    QRegularExpression regexTel(R"(^\d{8,}$)");
    if (!regexTel.match(telephone).hasMatch()) {
        QMessageBox::warning(page, "Erreur", "Numéro de téléphone invalide (8 chiffres minimum).");
        return false;
    }

    return true;
}

// Générer ID si vide
int client::genererIdSiVide()
{
    auto idEdit = page->findChild<QLineEdit*>("idClientLineEdit");
    if (!idEdit) return -1;

    bool ok;
    int id = idEdit->text().trimmed().toInt(&ok);
    if (ok && id > 0) return id;

    QSqlQuery q;
    if (!q.exec("SELECT NVL(MAX(ID_CLIENT),0)+1 AS NEXT_ID FROM SERS.CLIENT")) {
        qDebug() << "Erreur récup ID:" << q.lastError().text();
        return -1;
    }
    if (q.next()) return q.value("NEXT_ID").toInt();
    return -1;
}

// AJOUTER
void client::ajouterClient()
{
    auto nomEdit = page->findChild<QLineEdit*>("nomClientLineEdit");
    auto prenomEdit = page->findChild<QLineEdit*>("prenomClientLineEdit");
    auto telEdit = page->findChild<QLineEdit*>("telClientLineEdit");
    auto emailEdit = page->findChild<QLineEdit*>("emailClientLineEdit");
    auto dateNEdit = page->findChild<QDateEdit*>("dateNaissClient");
    auto dateIEdit = page->findChild<QDateEdit*>("dateInscrClient");

    if (!nomEdit || !prenomEdit || !telEdit || !emailEdit || !dateNEdit || !dateIEdit) {
        QMessageBox::critical(page, "Erreur", "Champs introuvables dans l'interface.");
        return;
    }

    QString nom = nomEdit->text().trimmed();
    QString prenom = prenomEdit->text().trimmed();
    QString telephone = telEdit->text().trimmed();
    QString email = emailEdit->text().trimmed();
    QString dateN = dateNEdit->date().toString("yyyy-MM-dd");
    QString dateI = dateIEdit->date().toString("yyyy-MM-dd");

    if (!validerChamps(email, telephone, nom, prenom))
        return;

    // Vérifier que l'email n'existe pas déjà
    QSqlQuery check;
    check.prepare("SELECT 1 FROM SERS.CLIENT WHERE EMAIL_C = :email");
    check.bindValue(":email", email);
    if (check.exec() && check.next()) {
        QMessageBox::warning(page, "Erreur", "Un client avec cet email existe déjà.");
        return;
    }

    int id = genererIdSiVide();
    if (id <= 0) {
        QMessageBox::critical(page, "Erreur", "Impossible de générer un ID valide.");
        return;
    }

    QSqlQuery query;
    query.prepare(
        "INSERT INTO SERS.CLIENT (ID_CLIENT, NOM_C, PRENOM_C, TEL_C, EMAIL_C, DATE_NAISSANCE, DATE_INSCRIPTION) "
        "VALUES (:id, :nom, :prenom, :tel, :email, TO_DATE(:dn,'YYYY-MM-DD'), TO_DATE(:di,'YYYY-MM-DD'))"
        );
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":tel", telephone);
    query.bindValue(":email", email);
    query.bindValue(":dn", dateN);
    query.bindValue(":di", dateI);

    if (!query.exec()) {
        QMessageBox::critical(page, "Erreur", "Échec ajout : " + query.lastError().text());
        return;
    }

    rafraichirListeClients();
    viderChamps();
    QMessageBox::information(page, "Succès", "Client ajouté avec succès.");
}



// RECHERCHER PAR ID
void client::rechercherClientParId()
{
    auto idEdit = page->findChild<QLineEdit*>("idClientLineEdit");
    if (!idEdit) return;

    bool ok;
    int id = idEdit->text().trimmed().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(page, "Erreur", "ID invalide.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM SERS.CLIENT WHERE ID_CLIENT = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(page, "Erreur", "Recherche impossible : " + query.lastError().text());
        return;
    }

    if (query.next()) {
        page->findChild<QLineEdit*>("nomClientLineEdit")->setText(query.value("NOM_C").toString());
        page->findChild<QLineEdit*>("prenomClientLineEdit")->setText(query.value("PRENOM_C").toString());
        page->findChild<QLineEdit*>("telClientLineEdit")->setText(query.value("TEL_C").toString());
        page->findChild<QLineEdit*>("emailClientLineEdit")->setText(query.value("EMAIL_C").toString());
        page->findChild<QDateEdit*>("dateNaissClient")->setDate(QDate::fromString(query.value("DATE_NAISSANCE").toString(), "yyyy-MM-dd"));
        page->findChild<QDateEdit*>("dateInscrClient")->setDate(QDate::fromString(query.value("DATE_INSCRIPTION").toString(), "yyyy-MM-dd"));
    } else {
        QMessageBox::information(page, "Non trouvé", "Aucun client avec cet ID.");
        viderChamps();
    }
}

// MODIFIER
void client::modifierClient()
{
    auto idEdit = page->findChild<QLineEdit*>("idClientLineEdit");
    if (!idEdit) return;

    bool ok;
    int id = idEdit->text().trimmed().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(page, "Erreur", "Recherchez d'abord un ID valide.");
        return;
    }

    QString nom = page->findChild<QLineEdit*>("nomClientLineEdit")->text().trimmed();
    QString prenom = page->findChild<QLineEdit*>("prenomClientLineEdit")->text().trimmed();
    QString telephone = page->findChild<QLineEdit*>("telClientLineEdit")->text().trimmed();
    QString email = page->findChild<QLineEdit*>("emailClientLineEdit")->text().trimmed();
    QString dateN = page->findChild<QDateEdit*>("dateNaissClient")->date().toString("yyyy-MM-dd");
    QString dateI = page->findChild<QDateEdit*>("dateInscrClient")->date().toString("yyyy-MM-dd");

    if (!validerChamps(email, telephone, nom, prenom))
        return;

    QSqlQuery query;
    query.prepare(
        "UPDATE SERS.CLIENT SET NOM_C=:nom, PRENOM_C=:prenom, TEL_C=:tel, EMAIL_C=:email, "
        "DATE_NAISSANCE=TO_DATE(:dn,'YYYY-MM-DD'), DATE_INSCRIPTION=TO_DATE(:di,'YYYY-MM-DD') "
        "WHERE ID_CLIENT=:id"
        );
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":tel", telephone);
    query.bindValue(":email", email);
    query.bindValue(":dn", dateN);
    query.bindValue(":di", dateI);

    if (!query.exec()) {
        QMessageBox::critical(page, "Erreur", "Échec modification : " + query.lastError().text());
        return;
    }

    rafraichirListeClients();
    QMessageBox::information(page, "Succès", "Client modifié !");
}

// SUPPRIMER
void client::supprimerClient()
{
    auto idEdit = page->findChild<QLineEdit*>("idClientLineEdit");
    if (!idEdit) return;

    bool ok;
    int id = idEdit->text().trimmed().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(page, "Erreur", "Recherchez d'abord un ID valide.");
        return;
    }

    if (QMessageBox::question(page, "Confirmer", "Supprimer ce client ?", QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
        return;

    QSqlQuery query;
    query.prepare("DELETE FROM SERS.CLIENT WHERE ID_CLIENT=:id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(page, "Erreur", "Échec suppression : " + query.lastError().text());
        return;
    }

    rafraichirListeClients();
    viderChamps();
    QMessageBox::information(page, "Succès", "Client supprimé !");
}

// RAFRAICHIR TABLE
void client::rafraichirListeClients()
{
    auto table = page->findChild<QTableWidget*>("clientTabWidget");
    if (!table) return;

    table->setRowCount(0);

    QSqlQuery query("SELECT ID_CLIENT, NOM_C, PRENOM_C, TEL_C, EMAIL_C, DATE_NAISSANCE, DATE_INSCRIPTION FROM SERS.CLIENT");
    int row = 0;
    while (query.next()) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(query.value("ID_CLIENT").toString()));
        table->setItem(row, 1, new QTableWidgetItem(query.value("NOM_C").toString()));
        table->setItem(row, 2, new QTableWidgetItem(query.value("PRENOM_C").toString()));
        table->setItem(row, 3, new QTableWidgetItem(query.value("TEL_C").toString()));
        table->setItem(row, 4, new QTableWidgetItem(query.value("EMAIL_C").toString()));
        table->setItem(row, 5, new QTableWidgetItem(query.value("DATE_NAISSANCE").toString()));
        table->setItem(row, 6, new QTableWidgetItem(query.value("DATE_INSCRIPTION").toString()));

        for (int col = 0; col < 7; ++col) {
            auto it = table->item(row, col);
            if (it) it->setFlags(it->flags() & ~Qt::ItemIsEditable);
        }
        row++;
    }
}

// TRIER
void client::trierParNom()
{
    auto table = page->findChild<QTableWidget*>("clientTabWidget");
    if (table) table->sortItems(1, Qt::AscendingOrder);
}

// VIDER CHAMPS
void client::viderChamps()
{
    auto id = page->findChild<QLineEdit*>("idClientLineEdit"); if (id) id->clear();
    auto nom = page->findChild<QLineEdit*>("nomClientLineEdit"); if (nom) nom->clear();
    auto prenom = page->findChild<QLineEdit*>("prenomClientLineEdit"); if (prenom) prenom->clear();
    auto tel = page->findChild<QLineEdit*>("telClientLineEdit"); if (tel) tel->clear();
    auto email = page->findChild<QLineEdit*>("emailClientLineEdit"); if (email) email->clear();
    auto dn = page->findChild<QDateEdit*>("dateNaissClient"); if (dn) dn->setDate(QDate::currentDate());
    auto di = page->findChild<QDateEdit*>("dateInscrClient"); if (di) di->setDate(QDate::currentDate());
}

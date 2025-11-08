#include "client.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>

// Connexion globale (déclarée dans main.cpp)
extern QSqlDatabase db;

CLIENT::CLIENT(int id, QString nom, QString prenom, QString telephone, QString date_naissance, QString date_inscription)
{
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->telephone = telephone;
    this->date_naissance = date_naissance;
    this->date_inscription = date_inscription;
}

// AJOUTER
bool CLIENT::ajouter()
{
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO GS_CLIENTS (ID, NOM, PRENOM, TELEPHONE, DATE_DE_NAISSANCE, DATE_INSCRIPTION) "
        "VALUES (:id, :nom, :prenom, :telephone, TO_DATE(:dn, 'DD/MM/YYYY'), TO_DATE(:di, 'DD/MM/YYYY'))"
        );

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":telephone", telephone);
    query.bindValue(":dn", date_naissance);
    query.bindValue(":di", date_inscription);

    if (!query.exec()) {
        qDebug() << "ERREUR AJOUT CLIENT:" << query.lastError().text();
        return false;
    }
    return true;
}

// SUPPRIMER
bool CLIENT::supprimer(int id)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM GS_CLIENTS WHERE ID = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "ERREUR SUPPRESSION CLIENT:" << query.lastError().text();
        return false;
    }
    return query.numRowsAffected() > 0;
}

// AFFICHER (avec debug pour vérifier)
QSqlQueryModel* CLIENT::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM GS_CLIENTS", db);

    if (model->lastError().isValid()) {
        qDebug() << "ERREUR AFFICHAGE CLIENTS:" << model->lastError().text();
    } else {
        qDebug() << "AFFICHAGE CLIENTS: " << model->rowCount() << " lignes trouvées.";
    }

    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prénom");
    model->setHeaderData(3, Qt::Horizontal, "Téléphone");
    model->setHeaderData(4, Qt::Horizontal, "Naissance");
    model->setHeaderData(5, Qt::Horizontal, "Inscription");

    return model;
}

// MODIFIER
bool CLIENT::modifier()
{
    QSqlQuery query(db);
    query.prepare(
        "UPDATE GS_CLIENTS SET NOM = :nom, PRENOM = :prenom, TELEPHONE = :telephone, "
        "DATE_DE_NAISSANCE = TO_DATE(:dn, 'DD/MM/YYYY'), "
        "DATE_INSCRIPTION = TO_DATE(:di, 'DD/MM/YYYY') "
        "WHERE ID = :id"
        );

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":telephone", telephone);
    query.bindValue(":dn", date_naissance);
    query.bindValue(":di", date_inscription);

    if (!query.exec()) {
        qDebug() << "ERREUR MODIFICATION CLIENT:" << query.lastError().text();
        return false;
    }
    return query.numRowsAffected() > 0;
}

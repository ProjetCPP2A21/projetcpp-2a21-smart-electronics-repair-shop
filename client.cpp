#include "client.h"
#include "connection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

CLIENT::CLIENT(int id, QString nom, QString prenom, QString telephone,
               QString date_naissance, QString date_inscription)
{
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->telephone = telephone;
    this->date_naissance = date_naissance;
    this->date_inscription = date_inscription;
}

bool CLIENT::ajouter()
{
    QSqlQuery q(Connection::getDatabase());
    q.prepare("INSERT INTO GS_CLIENTS (ID, NOM, PRENOM, TELEPHONE, DATE_DE_NAISSANCE, DATE_INSCRIPTION) "
              "VALUES (:id, :nom, :prenom, :tel, TO_DATE(:dn, 'DD/MM/YYYY'), TO_DATE(:di, 'DD/MM/YYYY'))");

    q.bindValue(":id", id);
    q.bindValue(":nom", nom);
    q.bindValue(":prenom", prenom);
    q.bindValue(":tel", telephone);
    q.bindValue(":dn", date_naissance);
    q.bindValue(":di", date_inscription);

    if (!q.exec()) {
        qDebug() << "AJOUT ÉCHOUÉ:" << q.lastError().text();
        return false;
    }
    return true;
}

bool CLIENT::modifier()
{
    QSqlQuery q(Connection::getDatabase());
    q.prepare("UPDATE GS_CLIENTS SET NOM=:nom, PRENOM=:prenom, TELEPHONE=:tel, "
              "DATE_DE_NAISSANCE=TO_DATE(:dn,'DD/MM/YYYY'), DATE_INSCRIPTION=TO_DATE(:di,'DD/MM/YYYY') "
              "WHERE ID=:id");

    q.bindValue(":id", id);
    q.bindValue(":nom", nom);
    q.bindValue(":prenom", prenom);
    q.bindValue(":tel", telephone);
    q.bindValue(":dn", date_naissance);
    q.bindValue(":di", date_inscription);

    return q.exec() && q.numRowsAffected() > 0;
}

bool CLIENT::supprimer(int id)
{
    QSqlQuery q(Connection::getDatabase());
    q.prepare("DELETE FROM GS_CLIENTS WHERE ID = :id");
    q.bindValue(":id", id);
    return q.exec() && q.numRowsAffected() > 0;
}

QSqlQueryModel* CLIENT::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(
        "SELECT ID, NOM, PRENOM, TELEPHONE, "
        "TO_CHAR(DATE_DE_NAISSANCE, 'DD/MM/YYYY'), "
        "TO_CHAR(DATE_INSCRIPTION, 'DD/MM/YYYY') "
        "FROM GS_CLIENTS", Connection::getDatabase());

    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prénom");
    model->setHeaderData(3, Qt::Horizontal, "Téléphone");
    model->setHeaderData(4, Qt::Horizontal, "Naissance");
    model->setHeaderData(5, Qt::Horizontal, "Inscription");

    return model;
}

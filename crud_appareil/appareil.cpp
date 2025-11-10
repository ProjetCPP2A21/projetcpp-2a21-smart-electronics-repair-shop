#include "appareil.h"
#include <QSqlQuery>
#include <QObject>
#include <QVariant> // Nécessaire pour les bindValue

// Constructeur par défaut
Appareil::Appareil()
{
    id_app = "";
    type = "";
    marque = "";
    modele = "";
    defaultdeclare = "";
    dateentree = QDate::currentDate();
    statut = "";
    remarques = "";
    prixestime = 0.0;
    dateestime = QDate::currentDate();
}

// Constructeur "rapide"
Appareil::Appareil(QString id, QString type, QString marque, QString modele)
{
    this->id_app = id;
    this->type = type;
    this->marque = marque;
    this->modele = modele;
}


bool Appareil::ajouter()
{
    QSqlQuery query;

    // --- CORRECTION : Nom de table APPAREILS et 10 champs ---
    query.prepare("INSERT INTO APPAREILS (ID_APP, TYPE, MARQUE, MODELE, DEFAULTDECLARE, DATEENTREE, STATUT, REMARQUES, PRIXESTIME, DATEESTIME) "
                  "VALUES (:id, :type, :marque, :modele, :default, :dateentree, :statut, :remarques, :prix, :dateestime)");

    // --- CORRECTION: 10 bindValue ---
    query.bindValue(":id", this->id_app);
    query.bindValue(":type", this->type);
    query.bindValue(":marque", this->marque);
    query.bindValue(":modele", this->modele);
    query.bindValue(":default", this->defaultdeclare);
    query.bindValue(":dateentree", this->dateentree);
    query.bindValue(":statut", this->statut);
    query.bindValue(":remarques", this->remarques);
    query.bindValue(":prix", this->prixestime);
    query.bindValue(":dateestime", this->dateestime);

    return query.exec();
}


bool Appareil::supprimer(QString id)
{
    QSqlQuery query;

    // --- CORRECTION : Nom de table APPAREILS ---
    query.prepare("DELETE FROM APPAREILS WHERE ID_APP = :id");
    query.bindValue(":id", id);
    return query.exec();
}


bool Appareil::charger(QString id)
{
    QSqlQuery query;

    // --- CORRECTION : Nom de table APPAREILS ---
    query.prepare("SELECT * FROM APPAREILS WHERE ID_APP = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next())
    {
        this->id_app = query.value(0).toString();
        this->type = query.value(1).toString();
        this->marque = query.value(2).toString();
        this->modele = query.value(3).toString();
        this->defaultdeclare = query.value(4).toString();
        this->dateentree = query.value(5).toDate();
        this->statut = query.value(6).toString();
        this->remarques = query.value(7).toString();
        this->prixestime = query.value(8).toDouble();
        this->dateestime = query.value(9).toDate();
        return true;
    }
    return false;
}


bool Appareil::modifier()
{
    QSqlQuery query;

    // --- CORRECTION : Nom de table APPAREILS et 9 champs à mettre à jour ---
    query.prepare("UPDATE APPAREILS SET "
                  "TYPE = :type, MARQUE = :marque, MODELE = :modele, DEFAULTDECLARE = :default, "
                  "DATEENTREE = :dateentree, STATUT = :statut, REMARQUES = :remarques, "
                  "PRIXESTIME = :prix, DATEESTIME = :dateestime "
                  "WHERE ID_APP = :id");

    // --- CORRECTION: 10 bindValue (9 pour SET, 1 pour WHERE) ---
    query.bindValue(":id", this->id_app);
    query.bindValue(":type", this->type);
    query.bindValue(":marque", this->marque);
    query.bindValue(":modele", this->modele);
    query.bindValue(":default", this->defaultdeclare);
    query.bindValue(":dateentree", this->dateentree);
    query.bindValue(":statut", this->statut);
    query.bindValue(":remarques", this->remarques);
    query.bindValue(":prix", this->prixestime);
    query.bindValue(":dateestime", this->dateestime);

    return query.exec();
}

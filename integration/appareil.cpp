#include "appareil.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>

// ============================================================
// CONSTRUCTEURS
// ============================================================

// 1. Constructeur par défaut (Vide)
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
    temp = 50;
}

// 2. Constructeur COMPLET (10 paramètres)
// C'est celui que MainWindow utilise.
Appareil::Appareil(QString id, QString type, QString marque, QString modele, QString defaut, QDate dateEntree, QString statut, QString remarques, double prix, QDate dateEstime, int temp)
{
    this->id_app = id;
    this->type = type;
    this->marque = marque;
    this->modele = modele;
    this->defaultdeclare = defaut;
    this->dateentree = dateEntree;
    this->statut = statut;
    this->remarques = remarques;
    this->prixestime = prix;
    this->dateestime = dateEstime;
    this->temp = temp ;
}

// (L'ancien constructeur à 4 paramètres a été supprimé car il créait l'erreur)

// ============================================================
// CRUD : CREATE (Ajouter)
// ============================================================

bool Appareil::ajouter()
{
    QSqlQuery query;
    // L'ordre des colonnes doit correspondre EXACTEMENT aux valeurs
    query.prepare("INSERT INTO APPAREILS (ID_APP, TYPE, MARQUE, MODELE, DEFAULTDECLARE, DATEENTREE, STATUT, REMARQUES, PRIXESTIME, DATEESTIME, TEMP_MAX) "
                  "VALUES (:id, :type, :marque, :modele, :default, :dateentree, :statut, :remarques, :prix, :dateestime, :temp)");

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
    query.bindValue(":temp", this->temp);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur Ajout :" << query.lastError().text();
        return false;
    }
}

// ============================================================
// CRUD : UPDATE (Modifier)
// ============================================================

bool Appareil::modifier()
{
    QSqlQuery query;

    query.prepare("UPDATE APPAREILS SET "
                  "TYPE = :type, "
                  "MARQUE = :marque, "
                  "MODELE = :modele, "
                  "DEFAULTDECLARE = :default, "
                  "DATEENTREE = :dateentree, "
                  "STATUT = :statut, "
                  "REMARQUES = :remarques, "
                  "PRIXESTIME = :prix, "
                  "DATEESTIME = :dateestime "
                  "TEMP_MAX = :temp "
                  "WHERE ID_APP = :id");

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
    query.bindValue(":temp", this->temp);

    // Retourne vrai seulement si une ligne a été modifiée
    if (query.exec()) {
        return query.numRowsAffected() > 0;
    } else {
        qDebug() << "Erreur Modif :" << query.lastError().text();
        return false;
    }
}

// ============================================================
// CRUD : DELETE (Supprimer)
// ============================================================

bool Appareil::supprimer(QString id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM APPAREILS WHERE ID_APP = :id");
    query.bindValue(":id", id);

    if (query.exec())
    {
        return query.numRowsAffected() > 0;
    }
    else
    {
        qDebug() << "Erreur Suppression :" << query.lastError().text();
        return false;
    }
}

// ============================================================
// UTILITAIRE (Charger un objet)
// ============================================================

bool Appareil::charger(QString id)
{
    QSqlQuery query;
    query.prepare("SELECT ID_APP, TYPE, MARQUE, MODELE, DEFAULTDECLARE, DATEENTREE, STATUT, REMARQUES, PRIXESTIME, DATEESTIME, TEMP_MAX "
                  "FROM APPAREILS WHERE ID_APP = :id");

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
        this->temp = query.value(10).toInt();
        return true;
    }
    return false;
}

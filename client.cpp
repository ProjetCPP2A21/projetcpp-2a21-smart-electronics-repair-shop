#include "client.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>
#include <QDate>  // Ajout pour calculer l'âge

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

// AFFICHER
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

//  Rechercher par ID
QSqlQueryModel* CLIENT::rechercher(int id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM GS_CLIENTS WHERE ID = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "ERREUR RECHERCHE CLIENT:" << query.lastError().text();
    }

    model->setQuery(std::move(query));

    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prénom");
    model->setHeaderData(3, Qt::Horizontal, "Téléphone");
    model->setHeaderData(4, Qt::Horizontal, "Naissance");
    model->setHeaderData(5, Qt::Horizontal, "Inscription");

    return model;
}

//  Afficher trié par ID
QSqlQueryModel* CLIENT::afficherTrieParID()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM GS_CLIENTS ORDER BY ID ASC", db);

    if (model->lastError().isValid()) {
        qDebug() << "ERREUR AFFICHAGE TRIÉ CLIENTS:" << model->lastError().text();
    } else {
        qDebug() << "AFFICHAGE TRIÉ CLIENTS: " << model->rowCount() << " lignes trouvées.";
    }

    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prénom");
    model->setHeaderData(3, Qt::Horizontal, "Téléphone");
    model->setHeaderData(4, Qt::Horizontal, "Naissance");
    model->setHeaderData(5, Qt::Horizontal, "Inscription");

    return model;
}

//  Statistiques par âge
QSqlQueryModel* CLIENT::statsParAge()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(
        "SELECT "
        "CASE "
        "WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, DATE_DE_NAISSANCE)/12) < 18 THEN '<18' "
        "WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, DATE_DE_NAISSANCE)/12) BETWEEN 18 AND 30 THEN '18-30' "
        "WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, DATE_DE_NAISSANCE)/12) BETWEEN 31 AND 50 THEN '31-50' "
        "ELSE '>50' "
        "END AS TRANCHE_AGE, "
        "COUNT(*) AS NOMBRE_CLIENTS "
        "FROM GS_CLIENTS "
        "GROUP BY "
        "CASE "
        "WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, DATE_DE_NAISSANCE)/12) < 18 THEN '<18' "
        "WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, DATE_DE_NAISSANCE)/12) BETWEEN 18 AND 30 THEN '18-30' "
        "WHEN FLOOR(MONTHS_BETWEEN(SYSDATE, DATE_DE_NAISSANCE)/12) BETWEEN 31 AND 50 THEN '31-50' "
        "ELSE '>50' "
        "END "
        "ORDER BY TRANCHE_AGE", db);

    if (model->lastError().isValid()) {
        qDebug() << "ERREUR STATS PAR ÂGE:" << model->lastError().text();
    }

    model->setHeaderData(0, Qt::Horizontal, "Tranche d'âge");
    model->setHeaderData(1, Qt::Horizontal, "Nombre de clients");

    return model;
}
// =============== PRISE DE RENDEZ-VOUS  ===============
bool CLIENT::ajouterRDV(int id_client, QDate date, QString heure)
{
    QSqlQuery q(db);

    // Vérifier que le client existe
    q.prepare("SELECT 1 FROM GS_CLIENTS WHERE ID = :id");
    q.bindValue(":id", id_client);
    if (!q.exec() || !q.next()) return false;

    // Insérer le RDV (clé composite → pas besoin d'ID_RDV)
    q.prepare("INSERT INTO GS_RDV (DATE_RDV, HEURE, ID) "
              "VALUES (:d, :h, :id)");
    q.bindValue(":d", date.toString("dd/MM/yyyy"));
    q.bindValue(":h", heure);
    q.bindValue(":id", id_client);

    return q.exec();
}

QSqlQueryModel* CLIENT::afficherRDVParDate(QDate date)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(
        "SELECT r.HEURE, c.NOM || ' ' || c.PRENOM AS CLIENT "
        "FROM GS_RDV r "
        "JOIN GS_CLIENTS c ON r.ID = c.ID "
        "WHERE r.DATE_RDV = '" + date.toString("dd/MM/yyyy") + "' "
                                            "ORDER BY r.HEURE", db);

    model->setHeaderData(0, Qt::Horizontal, "Heure");
    model->setHeaderData(1, Qt::Horizontal, "Client");
    return model;
}

int CLIENT::compterRDVParJour(QDate date)
{
    QSqlQuery q(db);
    q.prepare("SELECT COUNT(*) FROM GS_RDV WHERE DATE_RDV = :d");
    q.bindValue(":d", date.toString("dd/MM/yyyy"));
    return (q.exec() && q.next()) ? q.value(0).toInt() : 0;
}

QMap<QDate, int> CLIENT::chargerDisponibilites(QDate debut, QDate fin)
{
    QMap<QDate, int> map;
    QSqlQuery q(db);
    q.prepare("SELECT DATE_RDV, COUNT(*) FROM GS_RDV "
              "WHERE DATE_RDV BETWEEN :d1 AND :d2 "
              "GROUP BY DATE_RDV");
    q.bindValue(":d1", debut.toString("dd/MM/yyyy"));
    q.bindValue(":d2", fin.toString("dd/MM/yyyy"));
    if (q.exec()) {
        while (q.next()) {
            map[QDate::fromString(q.value(0).toString(), "dd/MM/yyyy")] = q.value(1).toInt();
        }
    }
    return map;
}
// ====== HISTORIQUE DES RÉPARATIONS ======
QSqlQueryModel* CLIENT::historiqueRDV(int id_client)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query(db);
    query.prepare(
        "SELECT "
        "    TO_CHAR(TO_DATE(r.DATE_RDV, 'DD/MM/YYYY'), 'DD/MM/YYYY') AS DATE_RDV, "
        "    r.HEURE, "
        "    c.NOM || ' ' || c.PRENOM AS CLIENT_COMPLET, "
        "    c.TELEPHONE, "
        "    TO_CHAR(c.DATE_DE_NAISSANCE, 'DD/MM/YYYY') AS DATE_NAISSANCE, "
        "    NVL( "
        "        (SELECT MIN(TO_CHAR(TO_DATE(r2.DATE_RDV, 'DD/MM/YYYY'), 'DD/MM/YYYY')) "
        "         FROM GS_RDV r2 "
        "         WHERE r2.ID = r.ID "
        "           AND (r2.DATE_RDV > r.DATE_RDV "
        "                OR (r2.DATE_RDV = r.DATE_RDV AND r2.HEURE > r.HEURE)) "
        "        ), "
        "        'Pas encore' "
        "    ) AS PROCHAIN_RDV "
        "FROM GS_RDV r "
        "INNER JOIN GS_CLIENTS c ON r.ID = c.ID "
        "WHERE r.ID = :id "
        "ORDER BY r.DATE_RDV DESC, r.HEURE DESC"
        );

    query.bindValue(":id", id_client);
    query.exec();
    model->setQuery(std::move(query));

    model->setHeaderData(0, Qt::Horizontal, "Date RDV");
    model->setHeaderData(1, Qt::Horizontal, "Heure");
    model->setHeaderData(2, Qt::Horizontal, "Client");
    model->setHeaderData(3, Qt::Horizontal, "Téléphone");
    model->setHeaderData(4, Qt::Horizontal, "Naissance");
    model->setHeaderData(5, Qt::Horizontal, "Prochain RDV");

    return model;
}

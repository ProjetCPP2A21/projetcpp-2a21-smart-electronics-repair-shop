#include "client.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>
#include <QDate>  // Ajout pour calculer l'âge
#include <QTime>  // Pour les RDV en cours

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
    lastError.clear();
}

// AJOUTER
bool CLIENT::ajouter()
{
    QSqlQuery query(db);
    
    // Essayer d'abord avec prepare() et binds nommés
    query.prepare(
        "INSERT INTO CLIENTS "
        "(ID, NOM, PRENOM, TELEPHONE, DATE_DE_NAISSANCE, DATE_INSCRIPTION) "
        "VALUES (:id, :nom, :prenom, :tel, TO_DATE(:dn, 'DD/MM/YYYY'), TO_DATE(:di, 'DD/MM/YYYY'))");
    
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":tel", telephone);
    query.bindValue(":dn", date_naissance);
    query.bindValue(":di", date_inscription);
    
    if (!query.exec()) {
        // Si prepare() échoue (erreur S1010), utiliser une requête directe
        QString nomEscaped = nom;
        nomEscaped.replace("'", "''");
        QString prenomEscaped = prenom;
        prenomEscaped.replace("'", "''");
        QString telEscaped = telephone;
        telEscaped.replace("'", "''");
        
        QString sql = QString(
            "INSERT INTO CLIENTS "
            "(ID, NOM, PRENOM, TELEPHONE, DATE_DE_NAISSANCE, DATE_INSCRIPTION) "
            "VALUES (%1, '%2', '%3', '%4', TO_DATE('%5', 'DD/MM/YYYY'), TO_DATE('%6', 'DD/MM/YYYY'))")
            .arg(id)
            .arg(nomEscaped)
            .arg(prenomEscaped)
            .arg(telEscaped)
            .arg(date_naissance)
            .arg(date_inscription);
        
        QSqlQuery directQuery(db);
        if (!directQuery.exec(sql)) {
            lastError = directQuery.lastError().text();
            qDebug() << "ERREUR AJOUT CLIENT:" << lastError;
            qDebug() << "SQL:" << sql;
            return false;
        }
    }
    
    lastError.clear();
    return true;
}

// SUPPRIMER
bool CLIENT::supprimer(int id)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM CLIENTS WHERE ID = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        lastError = query.lastError().text();
        qDebug() << "ERREUR SUPPRESSION CLIENT:" << lastError;
        return false;
    }
    lastError.clear();
    return query.numRowsAffected() > 0;
}

// AFFICHER
QSqlQueryModel* CLIENT::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM CLIENTS", db);

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
    
    // Essayer d'abord avec prepare() et binds nommés
    query.prepare(
        "UPDATE CLIENTS SET "
        "NOM = :nom, PRENOM = :prenom, TELEPHONE = :tel, "
        "DATE_DE_NAISSANCE = TO_DATE(:dn, 'DD/MM/YYYY'), "
        "DATE_INSCRIPTION = TO_DATE(:di, 'DD/MM/YYYY') "
        "WHERE ID = :id");
    
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":tel", telephone);
    query.bindValue(":dn", date_naissance);
    query.bindValue(":di", date_inscription);
    
    if (!query.exec()) {
        // Si prepare() échoue (erreur S1010), utiliser une requête directe
        QString nomEscaped = nom;
        nomEscaped.replace("'", "''");
        QString prenomEscaped = prenom;
        prenomEscaped.replace("'", "''");
        QString telEscaped = telephone;
        telEscaped.replace("'", "''");
        
        QString sql = QString(
            "UPDATE CLIENTS SET "
            "NOM = '%1', PRENOM = '%2', TELEPHONE = '%3', "
            "DATE_DE_NAISSANCE = TO_DATE('%4', 'DD/MM/YYYY'), "
            "DATE_INSCRIPTION = TO_DATE('%5', 'DD/MM/YYYY') "
            "WHERE ID = %6")
            .arg(nomEscaped)
            .arg(prenomEscaped)
            .arg(telEscaped)
            .arg(date_naissance)
            .arg(date_inscription)
            .arg(id);
        
        QSqlQuery directQuery(db);
        if (!directQuery.exec(sql)) {
            lastError = directQuery.lastError().text();
            qDebug() << "ERREUR MODIFICATION CLIENT:" << lastError;
            qDebug() << "SQL:" << sql;
            return false;
        }
        lastError.clear();
        return directQuery.numRowsAffected() > 0;
    }
    
    lastError.clear();
    return query.numRowsAffected() > 0;
}

//  Rechercher par ID
QSqlQueryModel* CLIENT::rechercher(int id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM CLIENTS WHERE ID = :id");
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

    model->setQuery("SELECT * FROM CLIENTS ORDER BY ID ASC", db);

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
//changed
// ====================== STATISTIQUES PAR ÂGE (PROGRAMMATIC VERSION) ======================
QSqlQueryModel* CLIENT::statsParAge()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    // Fetch all clients first
    QSqlQuery query(db);
    query.prepare("SELECT DATE_DE_NAISSANCE FROM CLIENTS");

    if (!query.exec()) {
        qDebug() << "ERREUR FETCH CLIENTS FOR STATS:" << query.lastError().text();
        // Return empty model with headers
        model->setHeaderData(0, Qt::Horizontal, "Tranche d'âge");
        model->setHeaderData(1, Qt::Horizontal, "Nombre de clients");
        return model;
    }

    // Count age groups
    int countUnder18 = 0;
    int count18to30 = 0;
    int count31to50 = 0;
    int countOver50 = 0;

    QDate currentDate = QDate::currentDate();

    while (query.next()) {
        QString dateStr = query.value(0).toString();
        QDate birthDate = QDate::fromString(dateStr, "dd/MM/yyyy");

        if (!birthDate.isValid()) {
            continue;
        }

        // Calculate age in years
        int ageYears = birthDate.daysTo(currentDate) / 365;

        if (ageYears < 18) {
            countUnder18++;
        } else if (ageYears >= 18 && ageYears <= 30) {
            count18to30++;
        } else if (ageYears >= 31 && ageYears <= 50) {
            count31to50++;
        } else {
            countOver50++;
        }
    }

    // Create a result model using UNION queries
    QStringList queries;

    if (countUnder18 > 0)
        queries << QString("SELECT '<18' AS TRANCHE_AGE, %1 AS NOMBRE_CLIENTS").arg(countUnder18);
    if (count18to30 > 0)
        queries << QString("SELECT '18-30' AS TRANCHE_AGE, %1 AS NOMBRE_CLIENTS").arg(count18to30);
    if (count31to50 > 0)
        queries << QString("SELECT '31-50' AS TRANCHE_AGE, %1 AS NOMBRE_CLIENTS").arg(count31to50);
    if (countOver50 > 0)
        queries << QString("SELECT '>50' AS TRANCHE_AGE, %1 AS NOMBRE_CLIENTS").arg(countOver50);

    if (queries.isEmpty()) {
        // No clients found
        model->setQuery("SELECT 'Aucun client' AS TRANCHE_AGE, 0 AS NOMBRE_CLIENTS FROM DUAL", db);
    } else {
        QString unionQuery = queries.join(" UNION ALL ");
        model->setQuery(unionQuery, db);
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
    q.prepare("SELECT 1 FROM CLIENTS WHERE ID = :id");
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
        "JOIN CLIENTS c ON r.ID = c.ID "
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
        "INNER JOIN CLIENTS c ON r.ID = c.ID "
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

// ====== RÉCUPÉRER LES RDV EN COURS (MAINTENANT) ======
QList<int> CLIENT::getRDVEnCours()
{
    QList<int> ids;
    QSqlQuery query(db);
    
    // Récupérer la date et l'heure actuelles
    QDate dateActuelle = QDate::currentDate();
    QTime heureActuelle = QTime::currentTime();
    
    // Formater la date et l'heure pour la comparaison
    QString dateStr = dateActuelle.toString("dd/MM/yyyy");
    QString heureStr = QString("%1:00").arg(heureActuelle.hour(), 2, 10, QChar('0'));
    
    // Chercher les RDV qui correspondent à la date et l'heure actuelles
    query.prepare("SELECT ID FROM GS_RDV WHERE DATE_RDV = :date AND HEURE = :heure");
    query.bindValue(":date", dateStr);
    query.bindValue(":heure", heureStr);
    
    if (query.exec()) {
        while (query.next()) {
            ids.append(query.value(0).toInt());
        }
    } else {
        qDebug() << "ERREUR RECHERCHE RDV EN COURS:" << query.lastError().text();
    }
    
    return ids;
}

// ====== AFFICHER TOUS LES RDV ======
QSqlQueryModel* CLIENT::afficherTousLesRDV()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query(db);
    query.prepare(
        "SELECT "
        "    r.ID AS ID_CLIENT, "
        "    TO_CHAR(TO_DATE(r.DATE_RDV, 'DD/MM/YYYY'), 'DD/MM/YYYY') AS DATE_RDV, "
        "    r.HEURE, "
        "    c.NOM || ' ' || c.PRENOM AS CLIENT "
        "FROM GS_RDV r "
        "INNER JOIN CLIENTS c ON r.ID = c.ID "
        "ORDER BY TO_DATE(r.DATE_RDV, 'DD/MM/YYYY') ASC, r.HEURE ASC");

    query.exec();
    model->setQuery(std::move(query));

    model->setHeaderData(0, Qt::Horizontal, "ID Client");
    model->setHeaderData(1, Qt::Horizontal, "Date RDV");
    model->setHeaderData(2, Qt::Horizontal, "Heure");
    model->setHeaderData(3, Qt::Horizontal, "Client");

    return model;
}

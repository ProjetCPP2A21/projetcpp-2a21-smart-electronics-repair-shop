#include "employer.h"
#include <QSqlError>

Employer::Employer() {
    tel = 0; salaire = 0;
}

Employer::Employer(QString id, QString nom, QString prenom, QString email, int tel, QDate dateN, QDate dateR, QString poste, double salaire, QString mtp, QString question, QString reponse)
{
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->tel = tel;
    this->dateNaissance = dateN;
    this->dateRecrutement = dateR;
    this->poste = poste;
    this->salaire = salaire;
    this->mtp = mtp;
    this->question = question;
    this->reponse = reponse;
}

bool Employer::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYES (ID_EMPLOYE, NOMEMPLOYE, PRENOM, EMAIL, TELEPHONE, DATENAISSANCE, DATERECRUTEMENT, POST, SALAIRE, MTP, QUESTION, REPONSE) "
                  "VALUES (:id, :nom, :prenom, :email, :tel, :dateN, :dateR, :poste, :salaire, :mtp, :quest, :rep)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":tel", tel);
    query.bindValue(":dateN", dateNaissance);
    query.bindValue(":dateR", dateRecrutement);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire);
    query.bindValue(":mtp", mtp);
    query.bindValue(":quest", question);
    query.bindValue(":rep", reponse);

    // === MODIFICATION POUR LE DEBUG ===
    if (query.exec()) {
        return true;
    } else {
        // Affiche l'erreur exacte dans la console de Qt Creator (en bas)
        qDebug() << "Erreur SQL lors de l'ajout :" << query.lastError().text();
        return false;
    }
}

bool Employer::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYES SET NOMEMPLOYE = :nom, PRENOM = :prenom, EMAIL = :email, TELEPHONE = :tel, "
                  "DATENAISSANCE = :dateN, DATERECRUTEMENT = :dateR, POST = :poste, SALAIRE = :salaire, "
                  "MTP = :mtp, QUESTION = :quest, REPONSE = :rep "
                  "WHERE ID_EMPLOYE = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":tel", tel);
    query.bindValue(":dateN", dateNaissance);
    query.bindValue(":dateR", dateRecrutement);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire);

    // Sécurité
    query.bindValue(":mtp", mtp);
    query.bindValue(":quest", question);
    query.bindValue(":rep", reponse);

    return query.exec();
}

bool Employer::supprimer(QString id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYES WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlQueryModel * Employer::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYES");
    return model;
}
QSqlQueryModel * Employer::rechercher(QString val)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYES WHERE ID_EMPLOYE LIKE '%"+val+"%' OR NOMEMPLOYE LIKE '%"+val+"%'");
    return model;
}


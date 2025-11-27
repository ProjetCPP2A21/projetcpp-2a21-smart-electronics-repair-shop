#include "employe.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool employe::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYES (ID_EMPLOYE, NOM_EMPLOYE, PRENOM, TELEPHONE, EMAIL, DATENAISSANCE, DATERECRUTEMENT, POST, SALAIRE) "
                  "VALUES (:id, :nom, :prenom, :tel, :email, :dn, :dr, :poste, :salaire)");
    query.bindValue(":id", id_employe);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":tel", telephone);
    query.bindValue(":email", email);
    query.bindValue(":dn", date_naissance);
    query.bindValue(":dr", date_recrutement);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire);

    return query.exec();
}

QSqlQueryModel* employe::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EMPLOYE, NOMEMPLOYE, PRENOM, TELEPHONE, EMAIL, DATENAISSANCE, DATERECRUTEMENT, POST, SALAIRE FROM EMPLOYES");
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prénom");
    model->setHeaderData(3, Qt::Horizontal, "Téléphone");
    model->setHeaderData(4, Qt::Horizontal, "Email");
    model->setHeaderData(5, Qt::Horizontal, "Naissance");
    model->setHeaderData(6, Qt::Horizontal, "Recrutement");
    model->setHeaderData(7, Qt::Horizontal, "Poste");
    model->setHeaderData(8, Qt::Horizontal, "Salaire");
    return model;
}

bool employe::supprimer(const QString& id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYES WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", id);
    return query.exec() && query.numRowsAffected() > 0;
}

bool employe::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYES SET NOMEMPLOYE=:nom, PRENOM=:prenom, TELEPHONE=:tel, EMAIL=:email, "
                  "DATENAISSANCE=:dn, DATERECRUTEMENT=:dr, POST=:poste, SALAIRE=:salaire WHERE ID_EMPLOYE=:id");
    query.bindValue(":id", id_employe);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":tel", telephone);
    query.bindValue(":email", email);
    query.bindValue(":dn", date_naissance);
    query.bindValue(":dr", date_recrutement);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire);
    return query.exec();
}

QSqlQueryModel* employe::rechercher(const QString& critere)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT ID_EMPLOYE, NOMEMPLOYE, PRENOM, TELEPHONE, EMAIL, DATENAISSANCE, DATERECRUTEMENT, POST, SALAIRE FROM EMPLOYES "
                  "WHERE NOMEMPLOYE LIKE :c OR EMAIL LIKE :c OR ID_EMPLOYE LIKE :c");
    query.bindValue(":c", "%" + critere + "%");
    if (query.exec()) {
        model->setQuery(std::move(query));  // Évite copie
    }
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prénom");
    model->setHeaderData(3, Qt::Horizontal, "Téléphone");
    model->setHeaderData(4, Qt::Horizontal, "Email");
    model->setHeaderData(5, Qt::Horizontal, "Naissance");
    model->setHeaderData(6, Qt::Horizontal, "Recrutement");
    model->setHeaderData(7, Qt::Horizontal, "Poste");
    model->setHeaderData(8, Qt::Horizontal, "Salaire");
    return model;
}

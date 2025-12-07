#include "stock.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include <QApplication>
#include <QSerialPort>
stock::stock(int id, QString nom, QString reference, QString categorie, QString quantite,
             QString prixachat, QString prixvente, QString fournisseur, QString datelivraison)
{
    this->id = id;
    this->nom = nom;
    this->reference = reference;
    this->categorie = categorie;
    this->quantite = quantite;
    this->prixachat = prixachat;
    this->prixvente = prixvente;
    this->fournisseur = fournisseur;
    this->datelivraison = datelivraison;
}


bool stock::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("insert into stock (ID_STOCK, NOMPIECE, REFERENCE, CATEGORIE, QUANTITE, PRIXACHAT, PRIXVENTE, FOURNISSEUR, DATELIVRAISON) "
                  "values (:id, :nom, :reference, :categorie, :quantite, :prixachat, :prixvente, :fournisseur, TO_DATE(:datelivraison,'YYYY-MM-DD'))");

    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":reference", reference);
    query.bindValue(":categorie", categorie);
    query.bindValue(":quantite", quantite.toInt());
    query.bindValue(":prixachat", prixachat.toDouble());
    query.bindValue(":prixvente", prixvente.toDouble());
    query.bindValue(":fournisseur", fournisseur);
    query.bindValue(":datelivraison", datelivraison);

    if (!query.exec()) {
        qDebug() << "Erreur ajoute:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL", "Échec ajout : " + query.lastError().text());
        return false;
    }
    return true;
}

QSqlQueryModel* stock::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM stock");



    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_STOCK"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMPIECE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("REFERENCE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("CATEGORIE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRIXACHAT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("PRIXVENTE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("FOURNISSEUR"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("DATELIVRAISON"));

    return model;
}


bool stock::supprimer(int id)
{
    QSqlQuery query;
    QString idString = QString::number(id); // Conversion en QString pour VARCHAR

    // Vérifier d'abord si l'ID existe
    query.prepare("SELECT COUNT(*) FROM stock WHERE ID_STOCK = :id");
    query.bindValue(":id", idString);

    if (!query.exec()) {
        qDebug() << "Erreur vérification ID:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL", "Erreur de vérification : " + query.lastError().text());
        return false;
    }

    query.next();
    int count = query.value(0).toInt();

    if (count == 0) {
        qDebug() << "Aucun produit trouvé avec ID:" << idString;
        QMessageBox::warning(nullptr, "Erreur", "Aucun produit trouvé avec l'ID : " + idString);
        return false;
    }

    // Supprimer le produit
    query.prepare("DELETE FROM stock WHERE ID_STOCK = :id");
    query.bindValue(":id", idString);

    if(query.exec()) {
        qDebug() << "Produit supprimé avec succès, ID:" << idString;
        return true;
    } else {
        qDebug() << "Erreur suppression:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL", "Échec suppression : " + query.lastError().text());
        return false;
    }

}
bool stock::modifier()
{
    QSqlQuery query;
    query.prepare("update stock set NOMPIECE =:nom, REFERENCE=:reference, CATEGORIE=:categorie, QUANTITE=:quantite, PRIXACHAT=:prixachat, PRIXVENTE=:prixvente, "
                  "FOURNISSEUR=:fournisseur, DATELIVRAISON=TO_DATE(:datelivraison,'YYYY-MM-DD') "
                  "where ID_STOCK=:id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":reference", reference);
    query.bindValue(":categorie", categorie);
    query.bindValue(":quantite", quantite.toInt());
    query.bindValue(":prixachat", prixachat.toDouble());
    query.bindValue(":prixvente", prixvente.toDouble());
    query.bindValue(":fournisseur", fournisseur);
    query.bindValue(":datelivraison", datelivraison);

    if (!query.exec()) {
        qDebug() << "Erreur modification:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL",
                              "Échec modification : " + query.lastError().text());
        return false;
    }

    return true;
}
QSqlQueryModel* stock::rechercher(QString nom)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM stock WHERE NOMPIECE LIKE :nom");
    query.bindValue(":nom", "%" + nom + "%"); // '%' pour trouver n'importe où

    if (!query.exec()) {
        qDebug() << "Erreur recherche:" << query.lastError().text();
    }

    model->setQuery(query);

    // En-têtes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_STOCK"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMPIECE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("REFERENCE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("CATEGORIE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRIXACHAT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("PRIXVENTE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("FOURNISSEUR"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("DATELIVRAISON"));

    return model;
}

QSqlQueryModel* stock::trier(QString critere, QString ordre)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    QString queryStr = "SELECT * FROM stock ORDER BY " + critere + " " + ordre;

    model->setQuery(queryStr);

    if (model->lastError().isValid()) {
        qDebug() << "Erreur tri:" << model->lastError();
    }

    return model;
}
void stock::rechercherArduino(QSerialPort* arduino, const QString& idText)
{
    // VOTRE FONCTION EXACTE - copier/coller
    if (idText.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez entrer un ID !");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYES WHERE TRIM(ID_EMPLOYE) = :id");
    query.bindValue(":id", idText.trimmed());

    bool idExiste = false;

    if (!query.exec()) {
        qDebug() << "Erreur SQL :" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
        return;
    }

    if (query.next()) {
        idExiste = true;
        QMessageBox::information(nullptr, "Succès", "ID trouvé dans la base !");
    } else {
        QMessageBox::warning(nullptr, "Non trouvé", "ID introuvable dans la base.");
    }

    if (arduino && arduino->isOpen()) {
        QString signal = idExiste ? "1" : "0";
        QByteArray data = signal.toLatin1();
        arduino->write(data);
        arduino->flush();

        qDebug() << "Envoyé à Arduino :" << data;
    } else {
        QMessageBox::critical(nullptr, "Erreur Arduino", "Arduino n'est pas connecté !");
    }
}

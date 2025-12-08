#ifndef APPAREIL_H
#define APPAREIL_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Appareil
{
public:
    // Constructeur par défaut
    Appareil();

    // LE CONSTRUCTEUR MANQUANT (C'est celui-ci qui corrige votre erreur)
    Appareil(QString id, QString type, QString marque, QString modele,
             QString defaut, QDate dateEntree, QString statut,
             QString remarques, double prix, QDate dateEstime, int temp);

    // Getters (Accesseurs) - Optionnel mais utile
    QString getID() { return id_app; }
    QString getType() { return type; }
    QString getMarque() { return marque; }
    QString getModele() { return modele; }

    // Setters (Mutateurs) - Optionnel
    void setID(QString id) { id_app = id; }
    void setType(QString t) { type = t; }
    void setMarque(QString m) { marque = m; }
    void setModele(QString m) { modele = m; }

    // Fonctionnalités CRUD
    bool ajouter();
    bool modifier();
    bool supprimer(QString id);
    bool charger(QString id); // Pour remplir l'objet depuis la BDD

private:
    // Attributs correspondant à votre base de données et appareil.cpp
    QString id_app;
    QString type;
    QString marque;
    QString modele;
    QString defaultdeclare;
    QDate dateentree;
    QString statut;
    QString remarques;
    double prixestime;
    QDate dateestime;
    int temp;
};

#endif // APPAREIL_H

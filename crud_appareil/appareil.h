#ifndef APPAREIL_H
#define APPAREIL_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Appareil
{
    // Attributs de la base de données
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

public:

    //Constructeurs
    Appareil();
    Appareil(QString id, QString type, QString marque, QString modele);

    // --- Getters ---
    QString getID() { return id_app; }
    QString getType() { return type; }
    QString getMarque() { return marque; }
    QString getModele() { return modele; }
    QString getDefaultDeclare() { return defaultdeclare; }
    QDate getDateEntree() { return dateentree; }
    QString getStatut() { return statut; }
    QString getRemarques() { return remarques; }
    double getPrixEstime() { return prixestime; }
    QDate getDateEstime() { return dateestime; }

    // --- Setters ---
    void setID(QString id) { id_app = id; }
    void setType(QString t) { type = t; }
    void setMarque(QString m) { marque = m; }
    void setModele(QString m) { modele = m; }
    void setDefaultDeclare(QString d) { defaultdeclare = d; }
    void setDateEntree(QDate d) { dateentree = d; }
    void setStatut(QString s) { statut = s; }
    void setRemarques(QString r) { remarques = r; }
    void setPrixEstime(double p) { prixestime = p; }
    void setDateEstime(QDate d) { dateestime = d; }

    // Fonctionnalités CRUD
    bool ajouter();
    bool supprimer(QString id);
    bool modifier();
    bool charger(QString id);
};

#endif // APPAREIL_H

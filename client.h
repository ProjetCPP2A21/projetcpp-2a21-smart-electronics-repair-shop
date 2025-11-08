#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class CLIENT
{
    int id;
    QString nom, prenom, telephone, date_naissance, date_inscription;

public:
    //Constructeurs
    CLIENT(){}
    CLIENT(int id, QString nom, QString prenom, QString telephone,QString date_naissance, QString date_inscription);

    // Getters
    int getID() { return id; }
    QString getNom()  { return nom; }
    QString getPrenom()  { return prenom; }
    QString getTelephone()  { return telephone; }
    QString getDateNaissance()  { return date_naissance; }
    QString getDateInscription() { return date_inscription; }

    // Setters
    void setID(int id) {this->id=id; }
    void setNom( QString n) { nom = n; }
    void setPrenom( QString p) { prenom = p; }
    void setTelephone( QString t) { telephone = t; }
    void setDateNaissance(QString d) { date_naissance = d; }
    void setDateInscription(QString d) { date_inscription = d; }
    //FONCTIONS
    bool ajouter();
    bool modifier();
    bool supprimer(int);
    QSqlQueryModel* afficher();
};

#endif

#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQueryModel>

class CLIENT
{
private:
    int id;
    QString nom, prenom, telephone, date_naissance, date_inscription;

public:
    CLIENT() {}
    CLIENT(int id, QString nom, QString prenom, QString telephone,
           QString date_naissance, QString date_inscription);

    int getID() const { return id; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QString getTelephone() const { return telephone; }
    QString getDateNaissance() const { return date_naissance; }
    QString getDateInscription() const { return date_inscription; }

    void setID(int id) { this->id = id; }
    void setNom(const QString& n) { nom = n; }
    void setPrenom(const QString& p) { prenom = p; }
    void setTelephone(const QString& t) { telephone = t; }
    void setDateNaissance(const QString& d) { date_naissance = d; }
    void setDateInscription(const QString& d) { date_inscription = d; }

    bool ajouter();
    bool modifier();
    static bool supprimer(int id);
    static QSqlQueryModel* afficher();
};

#endif // CLIENT_H

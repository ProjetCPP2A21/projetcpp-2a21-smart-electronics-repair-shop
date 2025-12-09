#ifndef EMPLOYER_H
#define EMPLOYER_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Employer
{
    QString id, nom, prenom, email, poste, mtp, question, reponse;
    int tel;
    double salaire;
    QDate dateNaissance, dateRecrutement;

public:
    // Constructeurs
    Employer();
    Employer(QString, QString, QString, QString, int, QDate, QDate, QString, double, QString, QString, QString);

    // Getters
    QString getId() { return id; }
    QString getNom() { return nom; }
    QString getPrenom() { return prenom; }
    QString getMtp() { return mtp; }
    QString getQuestion() { return question; }
    QString getReponse() { return reponse; }

    // Setters
    void setId(QString id) { this->id = id; }
    void setNom(QString n) { nom = n; }
    void setPrenom(QString p) { prenom = p; }
    void setEmail(QString e) { email = e; }
    void setTelephone(int t) { tel = t; }
    void setDateNaissance(QDate d) { dateNaissance = d; }
    void setDateRecrutement(QDate d) { dateRecrutement = d; }
    void setPoste(QString p) { poste = p; }
    void setSalaire(double s) { salaire = s; }

    // Nouveaux Setters Sécurité
    void setMtp(QString m) { mtp = m; }
    void setQuestion(QString q) { question = q; }
    void setReponse(QString r) { reponse = r; }

    // Fonctions CRUD
    bool ajouter();
    bool modifier();
    bool supprimer(QString id);
    QSqlQueryModel * afficher();
    QSqlQueryModel * rechercher(QString val);
};

#endif // EMPLOYER_H

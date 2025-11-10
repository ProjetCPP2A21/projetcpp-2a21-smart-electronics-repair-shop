#ifndef EMPLOYER_H
#define EMPLOYER_H

#include <QString>
#include <QSqlQueryModel>
#include <QDate>

class Employer
{
    QString id_employe;
    QString nom, prenom, email, poste;
    int telephone;
    QDate date_naissance, date_recrutement;
    double salaire;

public:
    // CONSTRUCTEUR : ordre = ordre des membres
    Employer(QString id = "", QString n = "", QString p = "", QString e = "", int tel = 0,
             QString po = "", double sal = 0.0, QDate dn = QDate(), QDate dr = QDate())
        : id_employe(id), nom(n), prenom(p), email(e), telephone(tel),
        poste(po), salaire(sal), date_naissance(dn), date_recrutement(dr) {}

    // Getters
    QString getId() const { return id_employe; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QString getEmail() const { return email; }
    int getTelephone() const { return telephone; }
    QString getPoste() const { return poste; }
    double getSalaire() const { return salaire; }
    QDate getDateNaissance() const { return date_naissance; }
    QDate getDateRecrutement() const { return date_recrutement; }

    // Setters
    void setId(const QString& id) { id_employe = id; }
    void setNom(const QString& n) { nom = n; }
    void setPrenom(const QString& p) { prenom = p; }
    void setEmail(const QString& e) { email = e; }
    void setTelephone(int tel) { telephone = tel; }
    void setPoste(const QString& po) { poste = po; }
    void setSalaire(double sal) { salaire = sal; }
    void setDateNaissance(const QDate& d) { date_naissance = d; }
    void setDateRecrutement(const QDate& d) { date_recrutement = d; }

    // CRUD
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(const QString& id);
    bool modifier();
    QSqlQueryModel* rechercher(const QString& critere);
};

#endif // EMPLOYER_H

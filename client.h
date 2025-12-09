#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QList>
#include <QTime>

class CLIENT
{
    int id;
    QString nom, prenom, telephone, date_naissance, date_inscription;
    QString lastError;

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
    QString getLastError() const { return lastError; }

    // Nouvelles fonctions
    QSqlQueryModel* rechercher(int id);  // Rechercher par ID
    QSqlQueryModel* afficherTrieParID();  // Trier par ID
    QSqlQueryModel* statsParAge();  // Statistiques par âge
    bool ajouterRDV(int id_client, QDate date, QString heure);
    QSqlQueryModel* afficherRDVParDate(QDate date);
    int compterRDVParJour(QDate date);
    QMap<QDate, int> chargerDisponibilites(QDate debut, QDate fin);
    QSqlQueryModel* historiqueRDV(int id_client);
    QList<int> getRDVEnCours();  // Retourne la liste des IDs clients avec RDV maintenant
    QSqlQueryModel* afficherTousLesRDV();  // Afficher tous les RDV avec ID client
};

#endif

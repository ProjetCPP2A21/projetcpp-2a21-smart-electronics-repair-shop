#ifndef STOCK_H
#define STOCK_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include <QSerialPort>
class QSerialPort;
class stock
{
private:
    QString nom, reference, categorie, quantite, prixachat, prixvente, fournisseur, datelivraison;
    int id;
public:
    stock() {}
    stock(int,QString,QString,QString,QString,QString,QString,QString,QString);
    //getters
    QString getNom(){return nom;}
    QString getReference(){return reference;}
    QString getCategorie(){return categorie;}
    QString getQuantite(){return quantite;}
    QString getPrixachat(){return prixachat;}
    QString getPrixvente(){return prixvente;}
    QString getFournisseur(){return fournisseur;}
    QString getDatelivraison(){return datelivraison;}
    int getID(){return id;}
    //settersss
    void setNom(QString n) {nom = n; }
    void setReference(QString r) {reference = r; }
    void setCategorie(QString c) {categorie = c; }
    void setQuantite(QString q) {quantite = q; }
    void setPrixachat(QString a) {prixachat  = a; }
    void setPrixvente(QString v) {prixvente = v; }
    void setFournisseur(QString f) {fournisseur = f; }
    void setDatelivraison(QString l) {datelivraison = l; }
    void setID(int id) {this->id = id; }


    //fonctionnalités
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * rechercher(QString nom);
    QSqlQueryModel * trier(QString critere, QString ordre);

    // Nouvelle méthode pour Arduino
     void rechercherArduino(QSerialPort* arduino, const QString& idText);
void verifierStockEtAlerter();

};

#endif

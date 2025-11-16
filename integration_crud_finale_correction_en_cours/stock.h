#ifndef STOCK_H
#define STOCK_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>

class stock
{
private:
    QString nom, reference, categorie, quantite, prixachat, prixvente, fournisseur, datelivraison;
    int id;
    void on_btajouter_stock_3_clicked(); //stock add
    void on_btsupprimer_stock_3_clicked(); //stock delete
    void on_btmodifier_stock_3_clicked(); //stock edit
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




};

#endif

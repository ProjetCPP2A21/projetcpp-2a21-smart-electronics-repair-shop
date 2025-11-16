#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

class fournisseur : public QObject
{
    Q_OBJECT

public:
    explicit fournisseur(QWidget *parentWidget, QObject *parent = nullptr);
    ~fournisseur() = default;

public slots:
    void ajouterFournisseur();
    void rechercherFournisseurParId();
    void modifierFournisseur();
    void supprimerFournisseur();
    void rafraichirListeFournisseurs();
    void trierParNomEntreprise();

private:
    QWidget *page;

    void viderChamps();
    bool validerChamps(const QString &email, const QString &telephone, const QString &nomEntreprise);
    int genererIdSiVide(); // retourne l'ID à utiliser (soit l'ID saisi, soit MAX+1 depuis la BDD)
};

#endif

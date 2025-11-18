#ifndef CLIENT_H
#define CLIENT_H

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
#include <QDebug>

class client : public QObject
{
    Q_OBJECT

public:
    explicit client(QWidget *parentWidget, QObject *parent = nullptr);
    ~client() = default;

public slots:
    void ajouterClient();
    void rechercherClientParId();
    void modifierClient();
    void supprimerClient();
    void rafraichirListeClients();
    void trierParNom();

private:
    QWidget *page;

    void viderChamps();
    bool validerChamps(const QString &email, const QString &telephone, const QString &nom, const QString &prenom);
    int genererIdSiVide(); // retourne l'ID à utiliser
};

#endif

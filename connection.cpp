#include "connection.h"
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>

Connection::Connection()
{
    db = QSqlDatabase::addDatabase("QODBC");

    if (db.isOpen())
        db.close();
}

bool Connection::createconnect()
{
    db.setDatabaseName("electronicshop");
    db.setUserName("electronicshop");
    db.setPassword("0101");

    if (db.open()) {


        QMessageBox::information(nullptr, "Succès", "Connexion établie à la base de données !");
        return true;
    } else {

        QMessageBox::critical(nullptr, "Erreur", "Échec de la connexion : " + db.lastError().text());
        return false;
    }
}


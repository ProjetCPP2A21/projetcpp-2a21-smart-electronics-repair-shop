#include "connection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

QSqlDatabase Connection::db;

Connection::Connection() {}

bool Connection::createconnect()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("SARRA");
    db.setPassword("0000");

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Erreur", "Connexion échouée :\n" + db.lastError().text());
        return false;
    }

    QSqlQuery q(db);
    q.exec("ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY'");
    qDebug() << "Connecté à Oracle !";
    return true;
}

void Connection::closeconnect()
{
    if (db.isOpen()) db.close();
}

QSqlDatabase Connection::getDatabase()
{
    return db;
}

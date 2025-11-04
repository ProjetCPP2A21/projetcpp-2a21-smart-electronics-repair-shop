#include "connection.h"

Connection::Connection()
{
    db = QSqlDatabase::addDatabase("QODBC");
}

Connection::~Connection()
{
    if (db.isOpen())
        db.close();
}

Connection& Connection::instance()
{
    static Connection instance;
    return instance;
}

bool Connection::createConnection()
{
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("adem01");
    db.setPassword("esprit17");

    if (db.open()) {
        qDebug() << "Connexion établie ✅";
        return true;
    } else {
        qDebug() << "Échec de la connexion ❌:" << db.lastError().text();
        return false;
    }
}

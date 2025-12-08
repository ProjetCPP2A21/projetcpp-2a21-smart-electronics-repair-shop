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
    db.setDatabaseName("electronicshop");
    db.setUserName("electronicshop");
    db.setPassword("0101");

    if (db.open()) {
        qDebug() << "Connexion établie ✅";
        return true;
    } else {
        qDebug() << "Échec de la connexion ❌:" << db.lastError().text();
        return false;
    }
}

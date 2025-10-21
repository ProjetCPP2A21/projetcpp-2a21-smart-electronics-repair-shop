#include "connection.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>


Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_projet2A");//inserer le nom de la source de données
    db.setUserName("adem");//inserer nom de l'utilisateur
    db.setPassword("gharbi0102");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;





    return  test;
}

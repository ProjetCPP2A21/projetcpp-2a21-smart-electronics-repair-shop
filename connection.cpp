#include "connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

Connection::Connection(){

}

bool Connection::createconnect()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");  // Your ODBC source
    db.setUserName("adem01");          // Your username (A MODIFIER)
    db.setPassword("esprit17");          // Your password (A MODIFIER)

    if (db.open()) {
        test = true;
        qDebug() << "✅ Database connected successfully!";
        QMessageBox::information(nullptr, "Success", "Database connected!");
    } else {
        qDebug() << "❌ Connection failed:" << db.lastError().text();
        QMessageBox::critical(nullptr, "Error", "Connection failed: " + db.lastError().text());
    }

    return test;
}

#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

// Connexion globale accessible partout
QSqlDatabase db;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;

    bool test = c.createconnect();
    if (test)
    {
        db = c.getDb();  // Assigne à la globale

        w.show();
        QMessageBox::information(nullptr, QObject::tr("Base de données ouverte"),
                                 QObject::tr("Connexion réussie.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Base de données non ouverte"),
                              QObject::tr("Échec de connexion.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        return 1;  // Quitte si échec
    }

    return a.exec();
}

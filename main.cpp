#include "connection.h"
#include "nstock.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test = c.createconnect();

    if (test) {
        nstock w;
        w.show();
        return a.exec();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database error"),
                              QObject::tr("Connexion à la base échouée."));
        return -1;
    }
}

#include "gemployer.h"
#include "connection.h"
#include <QMessageBox>
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // ✅ Correct function name (it's instance(), not CreateInstance)
    Connection& c = Connection::instance();

    bool test = c.createConnection();

    Gemployer w;
    if (test)
    {
        w.show();
        QMessageBox::information(
            nullptr,
            QObject::tr("Base de données"),
            QObject::tr("Connexion établie.\nCliquer sur Annuler pour quitter."),
            QMessageBox::Cancel
            );
    }
    else
    {
        // ✅ Fix typo: QMessageBOx → QMessageBox
        QMessageBox::critical(
            nullptr,
            QObject::tr("Base de données"),
            QObject::tr("Échec de la connexion.\nCliquer sur Annuler pour quitter."),
            QMessageBox::Cancel
            );
    }

    return a.exec();
}

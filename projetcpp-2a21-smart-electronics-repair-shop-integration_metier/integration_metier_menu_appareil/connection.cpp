#include "connection.h"

// Constructeur: s'exécute une seule fois
Connection::Connection()
{
    // On ajoute la base de données en utilisant le pilote ODBC
    db = QSqlDatabase::addDatabase("QODBC");
}

// Destructeur: ferme la connexion si elle est ouverte
Connection::~Connection()
{
    if (db.isOpen())
        db.close();
}

// Méthode 'instance' (Singleton)
Connection& Connection::instance()
{
    static Connection instance; // L'unique instance est créée ici
    return instance;
}

// Méthode pour établir la connexion
bool Connection::createConnection()
{
    // On définit les paramètres de connexion
    // 1. Le nom du DSN ODBC (configuré dans Windows)
    db.setDatabaseName("electronicshop");

    // 2. L'utilisateur (schéma)
    db.setUserName("electronicshop");

    // 3. Le mot de passe
    db.setPassword("0101");

    // On tente d'ouvrir la connexion
    if (db.open()) {
        qDebug() << "Connexion établie ✅";
        return true;
    } else {
        // En cas d'échec, on affiche l'erreur
        qDebug() << "Échec de la connexion ❌:" << db.lastError().text();
        return false;
    }
}

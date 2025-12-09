#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class Connection
{
public:
    // Méthode pour obtenir l'unique instance de la classe
    static Connection& instance();

    // Méthode pour établir la connexion
    bool createConnection();

private:
    QSqlDatabase db; // L'objet de base de données

    // Constructeur et destructeur privés
    Connection();
    ~Connection();

    // Empêcher la copie de l'objet (Singleton)
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
};

#endif // CONNECTION_H

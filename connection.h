#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>

class Connection
{
public:
    static Connection& instance();   // ✅ Correct declaration
    bool createConnection();         // ✅ Open database connection

private:
    QSqlDatabase db;

    Connection();                    // Private constructor
    ~Connection();                   // Destructor

    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
};

#endif // CONNECTION_H

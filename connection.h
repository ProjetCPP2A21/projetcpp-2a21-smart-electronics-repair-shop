#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>

class Connection
{
public:
    Connection();
    bool createconnect();
    void closeconnect();
    static QSqlDatabase getDatabase();
private:
    static QSqlDatabase db;
};

#endif // CONNECTION_H

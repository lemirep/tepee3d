#ifndef DATABASEUSER_H
#define DATABASEUSER_H

#include <QSqlRecord>
#include <QList>

// YOU NEED TO IMPLEMENT THIS INTERFACE IN ORDER TO RECEIVE SQL RESULTS
class   DatabaseServiceUserInterface
{
public :
    virtual void receiveResultFromSQLQuery(const QList<QSqlRecord> &result) = 0;
};


#endif // DATABASEUSER_H

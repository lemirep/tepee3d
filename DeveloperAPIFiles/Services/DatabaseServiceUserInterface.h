#ifndef DATABASEUSER_H
#define DATABASEUSER_H

#include <QSqlRecord>
#include <QList>

class   DatabaseServiceUserInterface
{
public :
    virtual void receiveResultFromSQLQuery(const QList<QSqlRecord> &result) = 0;
};


#endif // DATABASEUSER_H

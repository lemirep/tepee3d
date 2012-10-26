#ifndef DATABASETHREAD_H
#define DATABASETHREAD_H

#include <QThread>
#include "managebdd.h"

class DatabaseThread : public QThread
{
    Q_OBJECT
signals:
    void    resultQuery(QList<QSqlRecord>, int);
    void    queryToExec(QString Query, int);
public:
    DatabaseThread();
    ~DatabaseThread();
    void run();
    void stop();
};

#endif // DATABASETHREAD_H

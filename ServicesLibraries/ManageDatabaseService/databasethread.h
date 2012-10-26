#ifndef DATABASETHREAD_H
#define DATABASETHREAD_H

#include <QThread>
#include "ServiceInterface.h"
#include "managebdd.h"


class DatabaseThread : public QThread, Services::ServiceInterface
{
    Q_OBJECT
    Q_INTERFACES(Services::ServiceInterface)
    Q_PLUGIN_METADATA(IID "com.tepee3d.Services.databaseservice")

public:
    DatabaseThread();
    ~DatabaseThread();
    void        run();
    void        stop();

    void        initLibraryConnection(QObject *parent);
    QObject*    getLibraryQObject();

signals:
    void        resultQuery(QList<QSqlRecord>, int);
    void        queryToExec(QString Query, int);
};

#endif // DATABASETHREAD_H

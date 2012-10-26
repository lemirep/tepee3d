#ifndef MANAGEBDD_H
#define MANAGEBDD_H
#include <QSqlRecord>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QList>
#include <iostream>
#include <string.h>
#include <QtSql>

class ManageBDD : public QObject
{
    Q_OBJECT
public:
    ManageBDD();
    ManageBDD(QString);
    ~ManageBDD();

    bool    openDatabase(QString);
    bool    checkExistLocalDatabase();
    void    createLocalDatabase();
signals:
    void    resultQuery(QList<QSqlRecord>, int);
public slots:
    void    queryToExec(QString Query, int);
private :
    QString         localDBName;
    QString         field;
    QString         username;
    QSqlDatabase    dataBase;
    QList<QString>  fieldName ;
    QList<QString>  value;
};

#endif // MANAGEBDD_H

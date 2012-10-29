#ifndef MANAGEBDD_H
#define MANAGEBDD_H

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
    void    resultFromSQLQuery(const QList<QSqlRecord>&, QObject *receiver);
public slots:
    void    executeSQLQuery(const QString& Query, QObject *sender);
private :
    QString         localDBName;
    QString         field;
    QString         username;
    QSqlDatabase    dataBase;
    QList<QString>  fieldName ;
    QList<QString>  value;
};

#endif // MANAGEBDD_H

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
    ~ManageBDD();

    bool    openDatabase(const QString& dbName);
signals:
    void    resultFromSQLQuery(QList<QSqlRecord>, QObject *receiver, int id, void *data);
public slots:
    void    executeSQLQuery(const QString& Query, QObject *sender, int id, const QString &dbName, void *data);
private :
    QString         localDBName;
    QString         field;
    QString         username;
    QSqlDatabase    dataBase;
    QList<QString>  fieldName ;
    QList<QString>  value;
};

#endif // MANAGEBDD_H

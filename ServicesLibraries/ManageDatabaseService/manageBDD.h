#ifndef MANAGEBDD_H
#define MANAGEBDD_H

#include <QCoreApplication>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QList>
#include <QFile>
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
    QString         previousDbName;
    QString         field;
    QString         username;
    QSqlDatabase    dataBase;
    QList<QString>  fieldName ;
    QList<QString>  value;
    QString         applicationPath;
    QString         databasePath;
    QHash<QString, QString> nameToPathHash;
};

#endif // MANAGEBDD_H

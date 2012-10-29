#include "databasethread.h"
//This class launch ManageBDD in a thread
//DEBUG
#include <iostream>
#include <QDebug>

DatabaseThread::DatabaseThread() : QThread()
{
}

DatabaseThread::~DatabaseThread()
{
    this->stop();
}

void            DatabaseThread::initLibraryConnection(QObject *parent)
{
    this->setParent(parent);
    this->start();
}

QObject*        DatabaseThread::getLibraryQObject()
{
    return this;
}


//initialize manage bdd and connect signal to transfert sql query from application to the manage bdd
void DatabaseThread::run()
{
    qDebug()<< "thread database lib is running";
    ManageBDD MB;

    qRegisterMetaType< QList<QSqlRecord> >("QList<QSqlRecord>");
    QObject::connect(this->parent(), SIGNAL(executeSQLQuery(const QString &, QObject *)),
                     &MB, SLOT(executeSQLQuery(const QString&, QObject*)), Qt::QueuedConnection);
    QObject::connect(&MB, SIGNAL(resultFromSQLQuery(const QList<QSqlRecord>&, QObject *)),
                     this, SLOT(transmitSQLResult(const QList<QSqlRecord>&, QObject*)), Qt::QueuedConnection);
    qDebug() << "Manager BDD Initialized";
    this->exec();
    qDebug() << "Thread event loop launched";
}


void    DatabaseThread::transmitSQLResult(const QList<QSqlRecord> &result, QObject *receiver)
{
    qDebug() << "SQL Query Result Received";
    // TO RECEIVE RESULT OBJECT MUST IMPLEMENT
    DatabaseServiceUserInterface * user;
    if (receiver != NULL && (user = dynamic_cast<DatabaseServiceUserInterface *>(receiver)) != NULL)
    {
        qDebug() << "Transmitting results";
        user->receiveResultFromSQLQuery(result);
        qDebug() << "Results transmitted";
    }
    else
        qDebug() << "Object is not an instance of DatabaseUserInterface";
}

//stop the thread
void DatabaseThread::stop()
{
    if (currentThread() != this)
        QMetaObject::invokeMethod(this, "stop", Qt::QueuedConnection);
    else
        quit();
}

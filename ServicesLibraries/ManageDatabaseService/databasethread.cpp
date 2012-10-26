#include "databasethread.h"
//This class launch ManageBDD in a thread
//DEBUG
#include <iostream>

DatabaseThread::DatabaseThread() : QThread()
{
//    std::cout << "thread database lib created" << std::endl;
}

DatabaseThread::~DatabaseThread()
{
}

void            DatabaseThread::initLibraryConnection(QObject *parent)
{
    this->start();
/*    parent->DBThread = new DatabaseThread();
    qRegisterMetaType< QList<QSqlRecord> >("QList<QSqlRecord>");
    qRegisterMetaType< QRegExp >("QRegExp");
    QObject::connect(parent->DBThread, SIGNAL(resultQuery(QList<QSqlRecord>,int)), parent, SIGNAL(resultQuery(QList<QSqlRecord>,int)));
    QObject::connect(parent, SIGNAL(queryToExec(QString,int)), parent->DBThread, SIGNAL(queryToExec(QString,int)));
    parent->DBThread->start();
*/
}

QObject*        DatabaseThread::getLibraryQObject()
{
    return this;
}


//initialize manage bdd and connect signal to transfert sql query from application to the manage bdd
void DatabaseThread::run()
{
    std::cout << "thread database lib is running" << std::endl;
    ManageBDD MB;

    qRegisterMetaType< QList<QSqlRecord> >("QList<QSqlRecord>");
    qRegisterMetaType< QRegExp >("QRegExp");
//    QObject::connect(this, SIGNAL(queryToExec(QString,int)), &MB, SLOT(queryToExec(QString,int)));
//    QObject::connect(&MB, SIGNAL(resultQuery(QList<QSqlRecord>,int)), this, SIGNAL(resultQuery(QList<QSqlRecord>,int)));
    std::cout << "Manager BDD Initialized" << std::endl;
    this->exec();
    std::cout << "Thread event loop launched" << std::endl;
}

//stop the thread
void DatabaseThread::stop()
{
    if (currentThread() != this)
        QMetaObject::invokeMethod(this, "stop", Qt::QueuedConnection);
    else
        quit();
}

#include "databasethread.h"
//This class launch ManageBDD in a thread

DatabaseThread::DatabaseThread()
{
    std::cout << "thread database created" << std::endl;
}

DatabaseThread::~DatabaseThread()
{
}

//initialize manage bdd and connect signal to transfert sql query from application to the manage bdd
void DatabaseThread::run()
{
    std::cout << "thread database is running" << std::endl;
    ManageBDD MB;

    qRegisterMetaType< QList<QSqlRecord> >("QList<QSqlRecord>");
    qRegisterMetaType< QRegExp >("QRegExp");
    QObject::connect(this, SIGNAL(queryToExec(QString,int)), &MB, SLOT(queryToExec(QString,int)));
    QObject::connect(&MB, SIGNAL(resultQuery(QList<QSqlRecord>,int)), this, SIGNAL(resultQuery(QList<QSqlRecord>,int)));

    this->exec();
}

//stop the thread
void DatabaseThread::stop()
{
    if (currentThread() != this)
        QMetaObject::invokeMethod(this, "stop", Qt::QueuedConnection);
    else
        quit();
}

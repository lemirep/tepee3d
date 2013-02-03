#include "databasethread.h"
//This class launch ManageBDD in a thread
//DEBUG
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

bool            DatabaseThread::connectServiceToUser(QObject *user)
{
    qDebug() << "Connecting user to DatabaseServices";
    // SQL
    if (dynamic_cast<DatabaseServiceUserInterface*>(user) != NULL)
        return QObject::connect(user, SIGNAL(executeSQLQuery(const QString &, QObject *, int)),
                         this, SIGNAL(executeSQLQuery(const QString&,QObject*,int)));
    qWarning() << "Object does not implement DatabaseServiceUserInterface";
    return false;
}

bool            DatabaseThread::disconnectServiceFromUser(QObject *user)
{
    // SQL
    if (dynamic_cast<DatabaseServiceUserInterface*>(user) != NULL)
       return QObject::disconnect(user, SIGNAL(executeSQLQuery(const QString &, QObject *,int)),
                            this, SIGNAL(executeSQLQuery(const QString&,QObject*,int)));
    qWarning() << "Object does not implement DatabaseServiceUserInterface";
    return false;
}

//initialize manage bdd and connect signal to transfert sql query from application to the manage bdd
void DatabaseThread::run()
{
    qDebug()<< "thread database lib is running";
    ManageBDD MB;

    qRegisterMetaType< QList<QSqlRecord> >("QList<QSqlRecord>");
    QObject::connect(this, SIGNAL(executeSQLQuery(const QString &, QObject *, int)),
                     &MB, SLOT(executeSQLQuery(const QString&, QObject*, int)), Qt::QueuedConnection);
    QObject::connect(&MB, SIGNAL(resultFromSQLQuery(const QList<QSqlRecord>&, QObject *, int)),
                     this, SLOT(transmitSQLResult(const QList<QSqlRecord>&, QObject*, int)), Qt::QueuedConnection);
    qDebug() << "Manager BDD Initialized";
    this->exec();
    qDebug() << "Thread event loop launched";
}


void    DatabaseThread::transmitSQLResult(const QList<QSqlRecord> &result, QObject *receiver, int id)
{
    qDebug() << "SQL Query Result Received";
    // TO RECEIVE RESULT OBJECT MUST IMPLEMENT
    DatabaseServiceUserInterface * user;
    if (receiver != NULL && (user = dynamic_cast<DatabaseServiceUserInterface *>(receiver)) != NULL)
    {
        qDebug() << "Transmitting results";
        user->receiveResultFromSQLQuery(result, id);
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

#include "databasethread.h"
//This class launch ManageBDD in a thread
//DEBUG
#include <QDebug>

/*!
 * \class DatabaseThread
 * \code
 * #include <databasethread.h>
 * \endcode
 * \brief The DatabaseThread class inherits from QThread. It is the Service Layer of
 * the database management and handles connections with a ManageBDD instance living in
 * a thread to perfom SQL queries asynchronously.
 *
 * \sa ManageBDD
 *
 * \inmodule Tepee3D
 */

/*!
 * \class Services::DatabaseServiceUserInterface
 *
 * \code
 * #include <DatabaseServiceUserInterface.h>
 * \endcode
 *
 * \brief Interface that has to be implemented by users wishing to subscribe
 * to the Database Service.
 *
 * User implementing this interface can then execute SQL queries on the database
 * by emitting the following signal :
 * \code
 * void executeSQLQuery(const QString& query, QObject *sender, int id);
 * \endcode
 *
 * \inmodule Tepee3D
 */

/*!
 * \fn void DatabaseServiceUserInterface::receiveResultFromSQLQuery(QList<QSqlRecord> result, int id)
 *
 * Method that will be called when a
 */


/*!
 * Constructs a new DatabaseThread instance.
 */
DatabaseThread::DatabaseThread() : QThread()
{
}

/*!
 * Destroys a DatabaseThread instance, stopping the thread associated with it.
 */
DatabaseThread::~DatabaseThread()
{
    this->stop();
}

/*!
 * Initializes library connections with Qt Signals using \a parent.
 *
 */
void            DatabaseThread::initLibraryConnection(QObject *parent)
{
    this->setParent(parent);
    QObject::connect(this, SIGNAL(threadInitialized()), parent, SLOT(libraryInitialized()));
    this->start();
}

/*!
 * Returns the QObject instance of the Database Service Library so that
 * it can be used for signal connections.
 */
QObject*        DatabaseThread::getLibraryQObject()
{
    return this;
}

/*!
 * Subscribes \a user to the Database Service if \a user implements correctly
 * the Services::DatabaseServiceUserInterface. Returns true if subscription when
 * accordingly, false otherwise.
 */
bool            DatabaseThread::connectServiceToUser(QObject *user)
{
    qDebug() << "Connecting user to DatabaseServices";
    // SQL
    if (dynamic_cast<Services::DatabaseServiceUserInterface*>(user) != NULL)
        return QObject::connect(user, SIGNAL(executeSQLQuery(const QString &, QObject *, int)),
                         this, SIGNAL(executeSQLQuery(const QString&,QObject*,int)));
    qWarning() << "Object does not implement DatabaseServiceUserInterface";
    return false;
}

/*!
 * Unsubscribes \a user from the Database Service Library. Returns true if unsubscribing went
 * right, false otherwise.
 */

bool            DatabaseThread::disconnectServiceFromUser(QObject *user)
{
    // SQL
    if (dynamic_cast<Services::DatabaseServiceUserInterface*>(user) != NULL)
       return QObject::disconnect(user, SIGNAL(executeSQLQuery(const QString &, QObject *,int)),
                            this, SIGNAL(executeSQLQuery(const QString&,QObject*,int)));
    qWarning() << "Object does not implement DatabaseServiceUserInterface";
    return false;
}

/*!
 * Executed in a Thread context. Initializes a ManageBDD instance store in the stack of the thread.
 * Signal connections are made with the instance and the ManageBDD instance to transmit queries and
 * receive results. Connections are made with Qt::QueuedConnection.
 */
//initialize manage bdd and connect signal to transfert sql query from application to the manage bdd
void DatabaseThread::run()
{
    qDebug()<< "thread database lib is running";
    ManageBDD MB;

    qRegisterMetaType< QList<QSqlRecord> >("QList<QSqlRecord>");
    QObject::connect(this, SIGNAL(executeSQLQuery(const QString &, QObject *, int)),
                     &MB, SLOT(executeSQLQuery(const QString&, QObject*, int)), Qt::QueuedConnection);
    QObject::connect(&MB, SIGNAL(resultFromSQLQuery(QList<QSqlRecord>, QObject *, int)),
                     this, SLOT(transmitSQLResult(QList<QSqlRecord>, QObject*, int)), Qt::QueuedConnection);
    qDebug() << "Manager BDD Initialized";
    emit threadInitialized();
    qDebug() << "Thread event loop launched";
    this->exec();
}

/*!
 * Triggered when a SQL result is transmitted from the Thread to the main thread.
 * Transmits \a result to \a receiver with \a id.
 */
void    DatabaseThread::transmitSQLResult(QList<QSqlRecord> result, QObject *receiver, int id)
{
    qDebug() << "SQL Query Result Received";
    // TO RECEIVE RESULT OBJECT MUST IMPLEMENT
    Services::DatabaseServiceUserInterface * user;
    if (receiver != NULL && (user = dynamic_cast<Services::DatabaseServiceUserInterface *>(receiver)) != NULL)
    {
        qDebug() << "Transmitting results";
        user->receiveResultFromSQLQuery(result, id);
        qDebug() << "Results transmitted";
    }
    else
        qDebug() << "Object is not an instance of DatabaseUserInterface";
}

/*!
 * Stops the DatabaseThread.
 */
//stop the thread
void DatabaseThread::stop()
{
    if (currentThread() != this)
        QMetaObject::invokeMethod(this, "stop", Qt::QueuedConnection);
    else
        quit();
}

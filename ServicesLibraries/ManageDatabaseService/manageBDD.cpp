#include "manageBDD.h"
// DEBUG
#include <QDebug>


/*!
 * \class ManageBDD
 * \code
 * #include <managebdd.h>
 * \endcode
 * \brief The ManageBDD class, offers the ability to execute queries on
 * the SQLite database.
 *
 * The Service should hava a single instance of this class and preferably living in
 * a thread so that a single database connection can be used throughout the entire
 * time the application is used.
 *
 * \inmodule Tepee3D
 */


/*!
 * Constructs a new ManageBDD instance, opens a database connection
 * and fill it for the first use if necessary.
 */
ManageBDD::ManageBDD() : QObject()
{
    this->dataBase = QSqlDatabase::addDatabase("QSQLITE");
    if (this->openDatabase("Tepee3D.sql"))
    {
        qDebug() << "ManageBDD::Database Opened";
        if (!this->checkExistLocalDatabase())
            qDebug() << "ManageBDD::Database corrupted";
//            this->createLocalDatabase();
        qDebug() << "ManageBDD::Thread running and database initialized";
    }
    else
        qDebug() << "ManageBDD:: Database not opened";

}

///*!
// * Constructs a new ManageBDD instance, opens a database connection to the database
// * named by \a name and fill it for the first use if necessary.
// */
//ManageBDD::ManageBDD(QString name) : QObject()
//{
//    this->dataBase = QSqlDatabase::addDatabase("QSQLITE");
//    if (this->openDatabase(name))
//    {
//        this->sqlQuery = QSqlQuery(this->dataBase);
//        if (!this->checkExistLocalDatabase())
//            this->createLocalDatabase();
//    }
//}

/*!
 * Destroys a ManageBDD instance, close the database connection if opened.
 */
ManageBDD::~ManageBDD()
{
    if (this->dataBase.open())
        this->dataBase.close();
    this->dataBase.removeDatabase(this->dataBase.connectionName());
}

/*!
 * Opens a database connection to the database specified by \a dbname.
 * If the connection is successfully opened, returns true, false otherwise.
 */
bool ManageBDD::openDatabase(QString dbName)
{
    this->localDBName = QDir::currentPath() + "/" + dbName;
    qDebug() << localDBName;
    this->dataBase.setHostName("localhost");
    this->dataBase.setDatabaseName(localDBName);

    // THE DATABASE IS NOW CONTAINED IN THE TEPEE3DENGINE
    // THIS ALLOWS US TO PROVIDE A DATABASE SCHEMA WITHOUT HAVING TO
    // CREATE IT ON THE FIRST BOOT


//#ifdef Q_OS_LINUX
//    QString path(QDir::home().path());
//    path.append(QDir::separator()).append(this->localDBName);
//    path = QDir::toNativeSeparators(path);
//    this->dataBase.setDatabaseName(path);
//#else
//    this->dataBase.setDatabaseName(this->localDBName);
//#endif

    return this->dataBase.open();
}

/*!
 * Executes \a query on the database. The result will be transmitted to \a sender
 * along with the given \a id.
 */
//execute a query in database and send the result by a signal
void ManageBDD::executeSQLQuery(const QString& query, QObject *sender, int id)
{
    if (this->dataBase.open())
    {
        qDebug() << "Received query : {" << query << "}";
        QSqlQuery sqlQuery(this->dataBase);
        sqlQuery.prepare(query);
        if (sqlQuery.exec())
            qDebug() << "Query Execution Succeeded";
        else
            qDebug() << "YOU SHOULD CHECK YOUR QUERY";
        QList<QSqlRecord> results;
        results.push_back(sqlQuery.record());
        while (sqlQuery.next())
            results.push_back(sqlQuery.record());
        emit resultFromSQLQuery(results, sender, id);
    }
}

/*!
 * Creates the Database for the first time if it was empty.
 */
//create local database, in this method you should indicate which table you want create
void ManageBDD::createLocalDatabase()
{
    if (dataBase.open())
    {
        QSqlQuery query(this->dataBase);
        if (query.prepare("CREATE TABLE IF NOT EXISTS exist (id INTEGER UNIQUE PRIMARY KEY)"))

            if (query.exec())
            {
                if(query.prepare("CREATE TABLE IF NOT EXISTS `test` (`id` text NOT NULL PRIMARY KEY  , `name` text NOT NULL)"))
                {
                    query.exec();
                    std::cout << "Databasse creation successful" << std::endl;
                }
                else
                    std::cout << "Fail to create database " << std::endl;
            }
    }
}

/*!
 * Checks wether the database is initialized of if it needs to be filled.
 * Returns true if this is the case, false otherwise.
 */
//Check if local database exists
bool ManageBDD::checkExistLocalDatabase()
{
    if (dataBase.open())
    {
        qDebug() << "ManageBDD::Database is already created";
        QSqlQuery qry;
        qry.prepare( "SELECT * FROM room" );
        return (qry.exec());
    }
    qDebug() << "ManageBDD::Databasse is not created yet";
    return (false);
}


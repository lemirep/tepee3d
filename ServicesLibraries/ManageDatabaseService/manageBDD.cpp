#include "manageBDD.h"
// DEBUG
#include <QDebug>


/*!
 * \class ManageBDD
 * \code
 * #include <manageBDD.h>
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
    this->applicationPath = QCoreApplication::applicationDirPath();
    this->localDBName = "";
    this->databasePath = "";
}

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
 * Opens a database connection to the database specified by \a dbName.
 * If the connection is successfully opened, returns true, false otherwise.
 */
bool ManageBDD::openDatabase(const QString& dbName)
{
    // CLEAR DB PATH IN CASE
    this->localDBName = "";
#ifdef Q_OS_QNX
    // ON QNX, DATABASE HAVE TO BE COPIED TO THE data DIRECTORY
    // IN ORDER TO BE USED

    if (this->databasePath.isEmpty())
    {
        QDir dbDir(this->applicationPath);
        dbDir.cdUp();
        dbDir.cdUp();
        dbDir.cd("data");
        this->databasePath = dbDir.absolutePath();
    }
    QFile dbFile(this->databasePath + "/" + dbName);
    qDebug() << dbFile.fileName();
    if (!dbFile.exists())
    {
        qDebug() << "File doesn't exist";
        QFile dbTemplate(this->applicationPath + "/databases/" + dbName);
        qDebug() << "Trying to copy " << dbTemplate.fileName();
        if (dbTemplate.exists())
        {
            qDebug() << "Database Template exists";
            if (dbTemplate.copy(dbFile.fileName()))
            {
                this->localDBName = dbFile.fileName();
                qDebug() << "File Copied Successfully";
            }
        }
    }
    else
        qDebug() << "File already exists";

#endif

#ifdef Q_OS_WIN32
    // ON WINDOWS THE SQL DATABASES MUST BE IN THE APPDATA DIRECTORY
    // OTHERWISE THE PROGRAM AS TO BE RUN AS ADMINISTRATOR TO SAVE IN THE BDD


#endif

#ifdef Q_OS_LINUX
    // ON LINUX DATABASES CAN BE READ DIRECTLY FROM THE databases DIRECTORY
    // OF THE APPLICATION
    if (this->databasePath.isEmpty())
        this->databasePath = QDir::currentPath() + "/databases/";
    this->localDBName =  this->databasePath + dbName;
#endif

    qDebug() << localDBName;
    this->dataBase.setHostName("localhost");
    this->dataBase.setDatabaseName(localDBName);


    // THE DATABASE IS NOW CONTAINED IN THE TEPEE3DENGINE
    // THIS ALLOWS US TO PROVIDE A DATABASE SCHEMA WITHOUT HAVING TO
    // CREATE IT ON THE FIRST BOOT
    return this->dataBase.open();
}

/*!
 * Executes \a query on the database. The result will be transmitted to \a sender
 * along with the given \a id and \a data parameters.
 */
//execute a query in database and send the result by a signal
void ManageBDD::executeSQLQuery(const QString& query, QObject *sender, int id, const QString &dbName, void *data)
{
    QList<QSqlRecord> results;
    if (this->openDatabase(dbName))
    {
        qDebug() << "Received query : {" << query << "}";
        QSqlQuery sqlQuery(this->dataBase);
        sqlQuery.prepare(query);
        if (sqlQuery.exec())
            qDebug() << "Query Execution Succeeded";
        else
            qDebug() << "YOU SHOULD CHECK YOUR QUERY";
        results.push_back(sqlQuery.record());
        while (sqlQuery.next())
            results.push_back(sqlQuery.record());
        this->dataBase.close();
    }
    emit resultFromSQLQuery(results, sender, id, data);
}


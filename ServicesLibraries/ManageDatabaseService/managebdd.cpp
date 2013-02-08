#include "managebdd.h"
// DEBUG
#include <QDebug>


ManageBDD::ManageBDD() : QObject()
{
    this->dataBase = QSqlDatabase::addDatabase("QSQLITE");
    this->openDatabase("tepee3D.sql");
    if (!this->checkExistLocalDatabase())
        this->createLocalDatabase();
    std::cout << "Thread running and database initialized" << std::endl;
}

ManageBDD::ManageBDD(QString name) : QObject()
{
    this->dataBase = QSqlDatabase::addDatabase("QSQLITE");
    this->openDatabase(name);
    if (!this->checkExistLocalDatabase())
        this->createLocalDatabase();
}

ManageBDD::~ManageBDD()
{
    if (this->dataBase.open())
        this->dataBase.close();
    this->dataBase.removeDatabase(this->dataBase.connectionName());
}

bool ManageBDD::openDatabase(QString dbname)
{
    std::cout << dbname.toStdString() << std::endl;
    this->localDBName = dbname;
    this->dataBase.setHostName("localhost");

#ifdef Q_OS_LINUX
    QString path(QDir::home().path());
    path.append(QDir::separator()).append(this->localDBName);
    path = QDir::toNativeSeparators(path);
    this->dataBase.setDatabaseName(path);
#else
    this->dataBase.setDatabaseName(this->localDBName);
#endif
    return (this->dataBase.open());
}

//execute a query in database and send the result by a signal
void ManageBDD::executeSQLQuery(const QString& query, QObject *sender, int id)
{
    if (this->dataBase.open())
    {
        qDebug() << "Received query : " << query;
        QSqlQuery q(query, this->dataBase);
        QList<QSqlRecord> results;
        results.push_back(q.record());
        while (q.next())
            results.push_back(q.record());
        emit resultFromSQLQuery(results, sender, id);
    }
}

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

//Check if local database exists
bool ManageBDD::checkExistLocalDatabase()
{
    if (dataBase.open())
    {
        std::cout << "Databasse is already created" << std::endl;
        QSqlQuery qry;
        qry.prepare( "SELECT * FROM exist" );
        return (qry.exec());
    }
    std::cout << "Databasse is not created yet" << std::endl;
    return (false);
}


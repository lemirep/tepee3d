#include "WatchPlugin.h"

WatchPlugin::WatchPlugin() : PluginBase()
{
    qDebug() << "CREATION OF WatchPlugin";
    this->databaseCallBacks[RETRIEVE_CLOCK] = &WatchPlugin::retrieveClocksFromDatabaseCallBack;
    this->databaseCallBacks[GENERIC_REQUEST] = &WatchPlugin::genericDatabaseCallBack;
    this->clockModel = new Models::ListModel(new ClockListItem());
    this->initPlugin();
}

int WatchPlugin::getPluginId()
{
    return 32;
}

void WatchPlugin::initPlugin()
{
    qDebug() << " INITIALIZING PLUGINS ";
    emit("CREATE TABLE clock (clockId INTEGER NOT NULL PRIMARY KEY, clockUtc double, clockCity varchar(255))",this,GENERIC_REQUEST,DATABASE_NAME);
    emit ("SELECT * FROM clock", this, RETRIEVE_CLOCK, DATABASE_NAME);
}

void WatchPlugin::clearPluginBeforeRemoval()
{
}

QString WatchPlugin::getPluginName()
{
    return QString("WatchPlugin");
}

QString WatchPlugin::getPluginDescription()
{
    return QString("WatchPlugin Description");
}

Plugins::PluginBase* WatchPlugin::getPluginBase()
{
    return this;
}

QString WatchPlugin::getRoomPluginQmlFile() const
{
    return QString("WatchPlugin.qml");
}

QString WatchPlugin::getMenuPluginQmlFile() const
{
    return QString("Menu.qml");
}

Plugins::PluginBase* WatchPlugin::createNewInstance()
{
    return new WatchPlugin();
}

void    WatchPlugin::receiveResultFromSQLQuery( QList<QSqlRecord> result, int id, void *data)
{
    (this->*this->databaseCallBacks[id])(result, data);
}

void    WatchPlugin::receiveResultFromHttpRequest(QNetworkReply *reply, int requestId, void *)
{
    qDebug() << "WatchPlugin::Received Network Reply with id : " + requestId;
    qDebug() << reply->readAll();
}

void WatchPlugin::onFocusStateChanged()
{
}

void WatchPlugin::onIdleFocusState()
{
    qDebug() << "Idle focus handler";
}

void WatchPlugin::onSelectedFocusState()
{
    qDebug() << "Selected focus handler";
}

void WatchPlugin::onFocusedFocusState()
{
    qDebug() << "Focused focus handler";
}

QString WatchPlugin::getTime()
{
    return QTime::currentTime().toString();

}

QObject*  WatchPlugin::getClockModel() const
{
    return this->clockModel;
}

void WatchPlugin::retrieveClocksFromDababase()
{
    QString retrieveShowsRequest = QString("SELECT clockId, clockUtc, clockCity FROM clock;");
    emit executeSQLQuery(retrieveShowsRequest, this, RETRIEVE_CLOCK, DATABASE_NAME);
}

void WatchPlugin::retrieveClocksFromDatabaseCallBack(QList<QSqlRecord> result, void *data)
{
    Q_UNUSED(data)
    if (result.size() > 1)
    {
        result.pop_front();
        foreach (QSqlRecord record, result)
        {
            ClockListItem *clock = new ClockListItem(record.value(0).toInt(), record.value(1).toDouble(),record.value(2).toString());
            this->clockModel->appendRow(clock);
        }
    }
}

void WatchPlugin::genericDatabaseCallBack(QList<QSqlRecord> result, void *data)
{
    Q_UNUSED(result)
    Q_UNUSED(data)
}

void WatchPlugin::addClockToDB(QString city, QString utc)
{
    emit("INSERT INTO clock (clockUtc, clockCity) VALUES('" + city +"'," +  utc + ")",this,GENERIC_REQUEST,DATABASE_NAME);
}

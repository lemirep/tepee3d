#include "WatchPlugin.h"

WatchPlugin::WatchPlugin() : PluginBase()
{
    qDebug() << "CREATION OF WatchPlugin";
    this->databaseCallBacks[RETRIEVE_CLOCK] = &WatchPlugin::retrieveClocksFromDatabaseCallBack;
    this->databaseCallBacks[GENERIC_REQUEST] = &WatchPlugin::genericDatabaseCallBack;
    this->clockModel = new Models::ListModel(new ClockListItem());
    this->initPlugin();
}

int WatchPlugin::getPluginId() const
{
    return 32;
}

void WatchPlugin::initPlugin()
{
    qDebug() << " INITIALIZING PLUGINS ";
    emit executeSQLQuery("CREATE TABLE clock (clockId INTEGER NOT NULL PRIMARY KEY, clockCity varchar(255), clockUtc double)",this,GENERIC_REQUEST,DATABASE_NAME);
    qDebug()  << "SELECT * FROM clock";
    emit executeSQLQuery("SELECT * FROM clock", this, RETRIEVE_CLOCK, DATABASE_NAME);
    this->setPluginState("clocks_view");
}

void        WatchPlugin::clearPluginBeforeRemoval()
{
    delete this->clockModel;
}

QString     WatchPlugin::getPluginName() const
{
    return QString("WatchPlugin");
}

QString WatchPlugin::getPluginRepoName() const
{
    return QString("watch_plugin");
}

QString     WatchPlugin::getPluginDescription() const
{
    return QString("WatchPlugin Description");
}

QString WatchPlugin::getPluginVersion() const
{
    return PLUGIN_VERSION;
}

Plugins::PluginBase* WatchPlugin::getPluginBase()
{
    return this;
}

QString     WatchPlugin::getRoomPluginQmlFile() const
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
    QString retrieveClockRequest = QString("SELECT clockId, clockUtc, clockCity FROM clock;");
    emit executeSQLQuery(retrieveClockRequest, this, RETRIEVE_CLOCK, DATABASE_NAME);
}

void WatchPlugin::retrieveClocksFromDatabaseCallBack(QList<QSqlRecord> result, void *data)
{
    Q_UNUSED(data)
    bool init  = true;
    int firtclock = 1;

    if (result.size() > 1)
    {
        result.pop_front();
        foreach (QSqlRecord record, result)
        {
            if (init)
                firtclock = record.value(0).toInt();
            init = false;
            ClockListItem *clock = new ClockListItem(record.value(0).toInt(), record.value(1).toDouble(),record.value(2).toString());
            this->clockModel->appendRow(clock);
        }
        this->setCurrentCity(firtclock);
        this->setCurrentId(firtclock);
        this->setCurrentUtc(firtclock);
    }
}

void WatchPlugin::genericDatabaseCallBack(QList<QSqlRecord> result, void *data)
{
    Q_UNUSED(result)
    Q_UNUSED(data)
}

void WatchPlugin::addClockToDB(QString city, QString utc)
{
    emit executeSQLQuery("INSERT INTO clock (clockCity, clockUtc) VALUES('" + city +"'," +  utc + ")",this,GENERIC_REQUEST,DATABASE_NAME);
}

void        WatchPlugin::reInitModel()
{    
    this->clockModel->clear();
    this->retrieveClocksFromDababase();
}

QString WatchPlugin::pluginState() const
{
    return this->m_pluginState;
}

void WatchPlugin::setPluginState(const QString& value)
{
    this->m_pluginState = value;
    emit pluginStateChanged();
}

void        WatchPlugin::setCurrentCity(int index)
{
    ClockListItem *Item = reinterpret_cast<ClockListItem  *>(this->clockModel->find(index));
    if (Item == NULL)
    {
        qDebug() << "Item with index <" << index << "> not found";
        this->currentCity = "";
        return ;
    }
    this->setItemChangedCity(Item->getClockCity());
    emit ItemChangedCity();

}

void       WatchPlugin::setCurrentUtc(int index)
{
    ClockListItem *Item = reinterpret_cast<ClockListItem  *>(this->clockModel->find(index));
    if (Item == NULL)
    {
        qDebug() << "Item with index <" << index << "> not found";
        this->currentUtc = 0;
        return ;
    }
    this->setItemChangedUtc(Item->getClockUtc());
    emit ItemChangedUtc();
}

void       WatchPlugin::setCurrentId(int index)
{
    ClockListItem *Item = reinterpret_cast<ClockListItem  *>(this->clockModel->find(index));
    if (Item == NULL)
    {
        qDebug() << "Item with index <" << index << "> not found";
        this->currentId = 0;
        return ;
    }
    this->currentId = Item->getClockId();
}

QString     WatchPlugin::getCurrentCity() const
{
    return this->currentCity;
}

double      WatchPlugin::getCurrentUtc() const
{
    return this->currentUtc;
}

int         WatchPlugin::getCurrentId() const
{
    return this->currentId;
}


void WatchPlugin::updateClockDB(int clockId, QString city, QString utc)
{
    QString updateClock = "UPDATE clock SET clockCity='"+ city + "', clockUtc='" + utc + "' WHERE clockId = " + QString::number(clockId);
    emit executeSQLQuery(updateClock, this, RETRIEVE_CLOCK, DATABASE_NAME);
}

void WatchPlugin::deleteClockDB(int clockId)
{
    QString deleteClock = "delete FROM clock WHERE clockId = " + QString::number(clockId);
    qDebug() << deleteClock;
    emit executeSQLQuery(deleteClock, this, RETRIEVE_CLOCK, DATABASE_NAME);
}

QString WatchPlugin::getItemChangedCity() const
{
    return this->currentCity;
}
void WatchPlugin::setItemChangedCity(QString c)
{
    this->currentCity = c;
}

double WatchPlugin::getItemChangedUtc() const
{
    return this->currentUtc;
}
void WatchPlugin::setItemChangedUtc(double c)
{
    this->currentUtc = c;
}

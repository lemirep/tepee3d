#include "WatchPlugin.h"

WatchPlugin::WatchPlugin() : PluginBase()
{
    qDebug() << "CREATION OF WatchPlugin";
}

int WatchPlugin::getPluginId()
{
    return 32;
}

void WatchPlugin::initPlugin()
{
    qDebug() << " INITIALIZING PLUGINS ";
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

void    WatchPlugin::receiveResultFromSQLQuery( QList<QSqlRecord> q, int , void *)
{
    if (q.size() < 2)
        return ;
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

#include "watchmain.h"

watchMain::watchMain() : PluginBase()
{
    this->initPlugin();
}

int watchMain::getPluginId()
{
    return 2;
}

void watchMain::initPlugin()
{
    this->executeHttpGetRequest(QNetworkRequest(QUrl("http://127.0.0.1/RESTphp/index.php")),1);
}

QString watchMain::getPluginName()
{
    return QString("qmlwatchMain");
}

QString watchMain::getPluginDescription()
{
    return QString("WatchPlugins.qml");
}

Plugins::PluginBase* watchMain::getPluginBase()
{
    return this;
}

QString watchMain::getRoomPluginQmlFile() const
{
    return QString("WatchPlugins.qml");
}

QString watchMain::getMenuPluginQmlFile() const
{
    return QString("Menu.qml");
}

Plugins::PluginBase* watchMain::createNewInstance()
{
    return new watchMain();
}

void    watchMain::receiveResultFromSQLQuery( QList<QSqlRecord> , int )
{
}

void    watchMain::receiveResultFromHttpRequest(QNetworkReply *reply)
{
    qDebug() << reply->readAll();
}

void   watchMain::exposeContentToQml(QQmlContext *)
{
}

#include "XBMCPlugin.h"

XBMCPlugin::XBMCPlugin() : PluginBase()
{
    this->initPlugin();
}
// ALL the function should be implemented

int XBMCPlugin::getPluginId()
{
    return PLUGIN_ID;
}

void XBMCPlugin::initPlugin()
{
    this->executeHttpGetRequest(QNetworkRequest(QUrl("http://127.0.0.1/RESTphp/index.php")),1);
}

void XBMCPlugin::clearPluginBeforeRemoval()
{
}

QString XBMCPlugin::getPluginName()
{
    return QString("XBMCPlugin");
}

QString XBMCPlugin::getPluginDescription()
{
    return QString("XBMCPlugin.qml");
}

Plugins::PluginBase* XBMCPlugin::getPluginBase()
{
    return this;
}

QString XBMCPlugin::getRoomPluginQmlFile() const
{
    return QString("XBMCPlugin.qml");
}

QString XBMCPlugin::getMenuPluginQmlFile() const
{
    return QString("Menu.qml");
}

Plugins::PluginBase* XBMCPlugin::createNewInstance()
{
    return new XBMCPlugin();
}

void    XBMCPlugin::receiveResultFromSQLQuery(QList<QSqlRecord> reply, int id, void *data)
{
}

void    XBMCPlugin::receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data)
{
    qDebug() << reply->readAll();
}


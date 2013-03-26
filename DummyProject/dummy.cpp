#include "dummy.h"

Dummy::Dummy() : PluginBase()
{
    this->initPlugin();
}
// ALL the function should be implemented
/*
int Dummy::getPluginId()
{
    return 1;
}

void Dummy::initPlugin()
{
    this->executeHttpGetRequest(QNetworkRequest(QUrl("http://127.0.0.1/RESTphp/index.php")),1);
}

QString Dummy::getPluginName()
{
    return QString("qmlDummy");
}

QString Dummy::getPluginDescription()
{
    return QString("DummyPlugins.qml");
}

Plugins::PluginBase* Dummy::getPluginBase()
{
    return this;
}

QString Dummy::getRoomPluginQmlFile() const
{
    return QString("DummyPlugins.qml");
}

QString Dummy::getMenuPluginQmlFile() const
{
    return QString("Menu.qml");
}

Plugins::PluginBase* Dummy::createNewInstance()
{
    return new Dummy();
}

void    Dummy::receiveResultFromSQLQuery( QList<QSqlRecord> , int )
{
}

void    Dummy::receiveResultFromHttpRequest(QNetworkReply *reply, int )
{
    qDebug() << reply->readAll();
}
*/

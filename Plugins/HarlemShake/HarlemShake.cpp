#include "HarlemShake.h"

HarlemShake::HarlemShake() : PluginBase()
{
    qDebug() << "CREATION OF HARLEMSHAKE";
}

int HarlemShake::getPluginId()
{
    return 1;
}

void HarlemShake::initPlugin()
{
    qDebug() << " INITIALIZING PLUGINS ";
}

QString HarlemShake::getPluginName()
{
    return QString("HarlemShake");
}

QString HarlemShake::getPluginDescription()
{
    return QString("HarlemShake Description");
}

Plugins::PluginBase* HarlemShake::getPluginBase()
{
    return this;
}

QString HarlemShake::getRoomPluginQmlFile() const
{
    return QString("HarlemShake.qml");
}

QString HarlemShake::getMenuPluginQmlFile() const
{
    return QString("Menu.qml");
}

Plugins::PluginBase* HarlemShake::createNewInstance()
{
    return new HarlemShake();
}

void    HarlemShake::receiveResultFromSQLQuery( QList<QSqlRecord> q, int , void *)
{
    if (q.size() < 2)
        return ;
}

void    HarlemShake::receiveResultFromHttpRequest(QNetworkReply *reply, int requestId, void *)
{
    qDebug() << "HarlemShake::Received Network Reply with id : " + requestId;
    qDebug() << reply->readAll();
}

void HarlemShake::onFocusStateChanged()
{
}

void HarlemShake::onIdleFocusState()
{
    qDebug() << "Idle focus handler";
}

void HarlemShake::onSelectedFocusState()
{
    qDebug() << "Selected focus handler";
}

void HarlemShake::onFocusedFocusState()
{
    qDebug() << "Focused focus handler";
}


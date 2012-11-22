#include "PluginBase.h"
//DEBUG
#include <QDebug>

Plugins::PluginBase::PluginBase()
{
    qDebug() << "NEW PLUGINBASE INSTANCE CREATED ";
}

Plugins::PluginBase* Plugins::PluginBase::getPluginBase()
{
    return this;
}

void    Plugins::PluginBase::setFocusState(PluginState requestedState)
{
    qDebug() << "Setting Focus State " << requestedState;
}

void    Plugins::PluginBase::resultFromSQL()
{
    qDebug() << "PLUGIN BASE RESULT FROM SQL";
}

void    Plugins::PluginBase::executeHttpGetRequest(const QNetworkRequest &request)
{
    emit executeHttpRequest(request, Get, NULL, this);
}

void    Plugins::PluginBase::executeHttpDeleteRequest(const QNetworkRequest &request)
{
    emit executeHttpRequest(request, Delete, NULL, this);
}

void    Plugins::PluginBase::executeHttpPostRequest(const QNetworkRequest &request, QHttpMultiPart* multiPart)
{
    emit executeHttpRequest(request, Post, multiPart, this);
}

void    Plugins::PluginBase::executeHttpPutRequest(const QNetworkRequest &request, QHttpMultiPart* multiPart)
{
    emit executeHttpRequest(request, Put, multiPart, this);
}

bool    Plugins::PluginBase::needsUpdating() const
{
    return false;
}

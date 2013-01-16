#include "PluginBase.h"
//DEBUG
#include <QDebug>

Plugins::PluginBase::PluginBase() : QObject(NULL)
{
    qDebug() << "NEW PLUGINBASE INSTANCE CREATED ";
    this->focusState = Plugins::PluginEnums::pluginIdleState;
}

Plugins::PluginBase* Plugins::PluginBase::getPluginBase()
{
    return this;
}

void    Plugins::PluginBase::setFocusState(Plugins::PluginEnums::PluginState requestedState)
{
    qDebug() << "Setting Focus State " << requestedState;
    this->focusState = requestedState;
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

Plugins::PluginEnums::PluginState    Plugins::PluginBase::getFocusState()   const
{
    return this->focusState;
}

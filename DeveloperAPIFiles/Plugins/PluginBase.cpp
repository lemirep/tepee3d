#include "PluginBase.h"
//DEBUG
#include <QDebug>

/*!
 * \class Plugins::PluginBase
 *
 * \brief The Plugins::PluginBase class is the base class a Tepee3D plugin
 * has to inherit from. It wraps access to the various services a plugin has access
 * to as well as providing informations about the plugin that will be needed to by the
 * application to properly manage plugins.
 */

Plugins::PluginBase::PluginBase() : QObject(NULL)
{
    qDebug() << "NEW PLUGINBASE INSTANCE CREATED ";
    this->setFocusState(Plugins::PluginEnums::pluginIdleState);
    QObject::connect(this, SIGNAL(roomLeft()), this, SLOT(onRoomEntered()));
}

Plugins::PluginBase* Plugins::PluginBase::getPluginBase()
{
    return this;
}

void    Plugins::PluginBase::onRoomEntered()
{
    this->setFocusState(Plugins::PluginEnums::pluginIdleState);
}

void    Plugins::PluginBase::setFocusState(Plugins::PluginEnums::PluginState requestedState)
{
    qDebug() << "Setting Focus State " << requestedState;
    this->focusState = requestedState;
    emit (focusStateChanged(QVariant(requestedState)));
}

void    Plugins::PluginBase::askForFocusState(Plugins::PluginEnums::PluginState requestedState)
{
    // ASK THE ROOM FOR A NEW FOCUS STATE
    emit askForFocusState(requestedState, this);
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

void    Plugins::PluginBase::exposeContentToQml(QQmlContext *context)
{
    // EXPOSE YOUR QML CONTENT HERE
    // BE CAREFUL IN CASE YOUR PLUGIN IS LOADED SEVERAL TIME TO HAVE
    // A CONSISTENT BEHAVIOR : EITHER ALL PLUGINS BEHAVE THE SAME OR EACH PLUGIN CAN BE SET DIFFERENTLY
    qDebug() << "Plugin Base Exposing Qml Content";
}


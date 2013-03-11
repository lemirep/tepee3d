#include "PluginBase.h"
//DEBUG
#include <QDebug>

/*!
 * \class Plugins::PluginBase
 * \code
 * #include <PluginBase.h>
 * \endcode
 * \brief The Plugins::PluginBase class is the base class a Tepee3D plugin
 * has to inherit from. It wraps access to the various services a plugin has access
 * to as well as providing informations about the plugin that will be needed to by the
 * application to properly manage plugins.
 *
 * \inmodule Tepee3D
 */

Plugins::PluginBase::PluginBase() : QObject(NULL)
{
    qDebug() << "NEW PLUGINBASE INSTANCE CREATED ";
    this->setFocusState(Plugins::PluginEnums::pluginIdleState);
    QObject::connect(this, SIGNAL(roomLeft()), this, SLOT(onRoomEntered()));
}

/*!
 * Returns the current instance of the plugin.
 */
Plugins::PluginBase* Plugins::PluginBase::getPluginBase()
{
    return this;
}

/*!
 * Slot triggered when the Tepee3DEngine enters the room containing the plugin.
 */
void    Plugins::PluginBase::onRoomEntered()
{
    this->setFocusState(Plugins::PluginEnums::pluginIdleState);
}

/*!
 * Tells the plugin its focusState \a requestedState has changed.
 */
void    Plugins::PluginBase::setFocusState(Plugins::PluginEnums::PluginState requestedState)
{
    qDebug() << "Setting Focus State " << requestedState;
    this->focusState = requestedState;
    emit (focusStateChanged(QVariant(requestedState)));
}

/*!
 * When a plugin wishes to change its focusState, call this method with the required focusState \a requestedState.
 */
void    Plugins::PluginBase::askForFocusState(Plugins::PluginEnums::PluginState requestedState)
{
    // ASK THE ROOM FOR A NEW FOCUS STATE
    emit askForFocusState(requestedState, this);
}

/*!
 * Called when receiving SQL results from the Database Service.
 */
void    Plugins::PluginBase::resultFromSQL()
{
    qDebug() << "PLUGIN BASE RESULT FROM SQL";
}

/*!
 * Sends Http Get \a request to network manager.
 */
void    Plugins::PluginBase::executeHttpGetRequest(const QNetworkRequest &request)
{
    emit executeHttpRequest(request, Get, NULL, this);
}

/*!
 * Sends Http Delete \a request to network manager.
 */
void    Plugins::PluginBase::executeHttpDeleteRequest(const QNetworkRequest &request)
{
    emit executeHttpRequest(request, Delete, NULL, this);
}

/*!
 * Sends Http Post \a request to network manager.
 */
void    Plugins::PluginBase::executeHttpPostRequest(const QNetworkRequest &request, QHttpMultiPart* multiPart)
{
    emit executeHttpRequest(request, Post, multiPart, this);
}

/*!
 * Sends Http Put \a request to network manager.
 */
void    Plugins::PluginBase::executeHttpPutRequest(const QNetworkRequest &request, QHttpMultiPart* multiPart)
{
    emit executeHttpRequest(request, Put, multiPart, this);
}

/*!
 * Returns a boolean telling whether this pluugin needs logical updating every seconds or not.
 */
bool    Plugins::PluginBase::needsUpdating() const
{
    return false;
}

/*!
 * Returns the current focusState of the plugin.
 */
Plugins::PluginEnums::PluginState    Plugins::PluginBase::getFocusState()   const
{
    return this->focusState;
}
/*!
 * Offers the plugin a way to expose content to QML if it needs to do so.
 */
void    Plugins::PluginBase::exposeContentToQml(QQmlContext *)
{
    // EXPOSE YOUR QML CONTENT HERE
    // BE CAREFUL IN CASE YOUR PLUGIN IS LOADED SEVERAL TIME TO HAVE
    // A CONSISTENT BEHAVIOR : EITHER ALL PLUGINS BEHAVE THE SAME OR EACH PLUGIN CAN BE SET DIFFERENTLY
    qDebug() << "Plugin Base Exposing Qml Content";
}


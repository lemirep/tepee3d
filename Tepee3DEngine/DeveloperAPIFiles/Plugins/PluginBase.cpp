/****************************************************************************
**
** Copyright (C) Paul Lemire, Tepee3DTeam and/or its subsidiary(-ies).
** Contact: paul.lemire@epitech.eu
** Contact: tepee3d_2014@labeip.epitech.eu
**
** This file is part of the Tepee3D project
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
****************************************************************************/

#include "PluginBase.h"
//DEBUG
#include <QDebug>


/*!
 * \class Plugins::PluginEnums
 * \code
 * #include <PluginEnum.h>
 * \endcode
 *
 * \brief Contains the various enums needed by plugins
 *
 * \inmodule Tepee3D
 */

/*!
 * \fn PluginsEnums::PluginState Plugins::PluginEnums::valueOf(int value)
 *
 * Returns the PluginState enum corresponding to \a value.
 */


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

/*!
 * \fn int Plugins::PluginBase::getPluginId() const
 *
 * Returns the id of the plugins. This is the unique id you were provided during
 * the plugin creation process online;
 */

/*!
 * \fn QString Plugins::PluginBase::getPluginName() const
 *
 * Returns the name of the plugins.
 */

/*!
 * \fn QString Plugins::PluginBase::getPluginDescription() const
 *
 * Returns a description of the plugin.
 */

/*!
  * \fn QString Plugins::PluginBase::getPluginVersion() const
  *
  * Returns the current version of the plugin, needed to check for updates.
  */

/*!
 * \fn QString Plugins::PluginBase::getRoomPluginQmlFile() const
 *
 * Returns the main qml file's name so that the engine knows which file to load.
 */

/*!
 * \fn QString Plugins::PluginBase::getMenuPluginQmlFile() const
 *
 * Returns the name of the qml file used to set the plugin and that will be loaded in the plugin menu area.
 */

/*!
 * \fn Plugins::PluginBase*  Plugins::PluginBase::createNewInstance()
 *
 * Returns a new instance of the plugin.
 */

/*!
 * \fn void Plugins::PluginBase::receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, void *data)
 *
 * Called by the Database Service Library to transmit the \a result of a previously executed query as well
 * as and \a id and \a data parameters to help recognize the query.
 */

/*!
 * \fn void Plugins::PluginBase::receiveResultFromHttpRequest(QNetworkReply *reply, int requestId, void *data)
 *
 * Triggered when the \a reply of a previously executed network request is received.
 * The \a requestId and the \a data parameter that might have optionaly been passed when executing the request, are forwarded
 * back.
 */

/*!
 * \fn void Plugins::PluginBase::executeSQLQuery(const QString& query, QObject *sender, int id, const QString& dbName, void *data = NULL)
 *
 * Emitted when a database \a query needs to be executed on a the database names \a dbName. The result of its execution will be transmitted to the \a sender
 * along with an \a id to recognize the query. Note that an optional \a data pointer can be passed and will be retransmitted with the result of the query.
 */

/*!
 * \fn void Plugins::PluginBase::executeHttpRequest(const QNetworkRequest &request, int requestType, QHttpMultiPart *multipart, QObject *sender, int requestId, void *data)
 *
 * Emitted when a network \a request needs to be performed, with the \a requestType to identify the type HTTP request and a \a multipart which can be null to transmit
 * data through the request. The reply will be transmitted to \a sender along with the \a data pointer and \a requestId of his choice.
 */

/*!
 * \fn void Plugins::PluginBase::askForFocusState(Plugins::PluginEnums::PluginState requestedState, QObject *sender)
 *
 * Emitted when a plugin ask for a new focus state \a requestedState. The response will be transmitted to \a sender.
 */

/*!
 * \fn void Plugins::PluginBase::focusStateChanged(QVariant focusState, QVariant previousState)
 *
 * Emitted when the \a focusState of a plugin has changed with the \a previousState in which the plugin was.
 */


/*!
 * \fn void Plugins::PluginBase::roomEntered()
 *
 * Emitted when the room in which the PluginBase instance lives is entered.
 */

/*!
 * \fn void Plugins::PluginBase::roomLeft()
 *
 * Emitted when the room in which the PluginBase instance lives is left.
 */

/*!
 * Constructs a new Plugins::PluginBase instance. On construction, the plugin is not yet connected
 * to the various services. If you need services to initialize your plugin you should reimplement the
 * init Plugin method.
 * \sa initPlugin()
 */
Plugins::PluginBase::PluginBase() : QObject()
{
    qDebug() << "NEW PLUGINBASE INSTANCE CREATED ";
    this->focusHandler[Plugins::PluginEnums::pluginIdleState]     = &Plugins::PluginBase::onIdleFocusState;
    this->focusHandler[Plugins::PluginEnums::pluginSelectedState] = &Plugins::PluginBase::onSelectedFocusState;
    this->focusHandler[Plugins::PluginEnums::pluginFocusedState]  = &Plugins::PluginBase::onFocusedFocusState;
    this->setFocusState(Plugins::PluginEnums::pluginIdleState);
}

/*!
 * Virtual destructors of a PluginBase instance. Primarly needed for dynamc_cast safety.
 */
Plugins::PluginBase::~PluginBase()
{
}

/*!
 * \fn void Plugins::PluginBase::initPlugin()
 *
 * Initializes the plugins. You must implement this method and perform
 * all necessary operations to properly initialize your plugin. You can call any
 * services provided by the application at this point if you need to do so.
 */

/*!
 * Returns the current instance of the plugin.
 */
Plugins::PluginBase* Plugins::PluginBase::getPluginBase()
{
    return this;
}

/*!
 * Sets the plugin's focus state and alert the qml view that the focusState \a requestedState has changed.
 * The corresponding focus handler is called
 */
void    Plugins::PluginBase::setFocusState(Plugins::PluginEnums::PluginState requestedState)
{
    qDebug() << "Setting Focus State " << requestedState << " Calling corresponding handler";
    Plugins::PluginEnums::PluginState oldFocusState = this->focusState;
    this->focusState = requestedState;
    // CALL FOCUS STATE HANDLER
    (this->*this->focusHandler[this->focusState])();
    emit (focusStateChanged(QVariant(requestedState), QVariant(oldFocusState)));
}

/*!
 * Call this method When a plugin wishes to change its focusState, for the given \a requestedState.
 */
void    Plugins::PluginBase::askForFocusState(Plugins::PluginEnums::PluginState requestedState)
{
    // ASK THE ROOM FOR A NEW FOCUS STATE
    emit askForFocusState(requestedState, this);
}

/*!
 *  Return the position vector of the plugin in the room.
 */
QVector3D Plugins::PluginBase::getPluginPosition() const
{
    return this->m_position;
}

/*!
 * Sets the plugin's position to \a position;
 */
void Plugins::PluginBase::setPluginPosition(const QVector3D &position)
{
    this->m_position = position;
}

/*!
 * Handler for idle focusState. Your implementation should override this method to behave
 * the way you would like your plugin to behave.
 */
void Plugins::PluginBase::onIdleFocusState()
{
}

/*!
 * Handler for selected focusState. Your implementation should override this method to behave
 * the way you would like your plugin to behave.
 */
void Plugins::PluginBase::onSelectedFocusState()
{
}

/*!
 * Handler for focused focusState. Your implementation should override this method to behave
 * the way you would like your plugin to behave.
 */
void Plugins::PluginBase::onFocusedFocusState()
{
}

/*!
 * Sends Http Get \a request to network manager, \a requestId and \a data will be transmitted with the reply to identify the request.
 */
void    Plugins::PluginBase::executeHttpGetRequest(const QNetworkRequest &request, int requestId, void *data)
{
    emit executeHttpRequest(request, Get, NULL, this, requestId, data);
}

/*!
 * Sends Http Delete \a request to network manager, \a requestId and \a data will be transmitted with the reply to identify the request.
 */
void    Plugins::PluginBase::executeHttpDeleteRequest(const QNetworkRequest &request, int requestId, void *data)
{
    emit executeHttpRequest(request, Delete, NULL, this, requestId, data);
}

/*!
 * Sends Http Post \a request to network manager with \a multiPart for data, \a requestId and \a data will be transmitted with the reply to identify the request.
 */
void    Plugins::PluginBase::executeHttpPostRequest(const QNetworkRequest &request, QHttpMultiPart* multiPart, int requestId, void *data)
{
    emit executeHttpRequest(request, Post, multiPart, this, requestId, data);
}

/*!
 * Sends Http Put \a request to network manager with \a multiPart for data, \a requestId and \a data will be transmitted with the reply to identify the request.
 */
void    Plugins::PluginBase::executeHttpPutRequest(const QNetworkRequest &request, QHttpMultiPart* multiPart, int requestId, void *data)
{
    emit executeHttpRequest(request, Put, multiPart, this, requestId, data);
}

/*!
 * Returns a boolean telling whether this plugin needs logical updating every seconds or not.
 */
bool    Plugins::PluginBase::needsUpdating() const
{
    return false;
}

/*!
 * If the plugin needs to be updated, reimplement this method in your base class to suit your need.
 * It will be called every second when the plugin is in the current room.
 *
 * \sa needsUpdating();
 */
void Plugins::PluginBase::updatePlugin()
{
}

/*!
 * Returns a Json representation of the plugin. This can be use for synching across multiple devices.
 */
QJsonObject Plugins::PluginBase::toJsonRepresentation() const
{
    QJsonObject pluginJsonObject;

    pluginJsonObject.insert("id", QJsonValue(this->getPluginId()));
    pluginJsonObject.insert("name", QJsonValue(this->getPluginName()));
    pluginJsonObject.insert("description", QJsonValue(this->getPluginDescription()));
    pluginJsonObject.insert("version", QJsonValue(this->getPluginVersion()));

    return pluginJsonObject;
}

/*!
 * Exposes the plugin C++ class to the QML Context \a context. That way the methods marked as
 * QINVOKABLE of the plugin class can be called by prefixing them with the PluginNames
 *
 * For more information, consider reading the following link : \l {http://qt-project.org/doc/qt-5.0/qtqml/qtqml-cppintegration-exposecppattributes.html}
 */
void Plugins::PluginBase::exposeContentToQml(QQmlContext *context)
{
    context->setContextProperty(this->getPluginName(), this);
}

/*!
 * Returns the current focusState of the plugin.
 */
Plugins::PluginEnums::PluginState    Plugins::PluginBase::getFocusState()   const
{
    return this->focusState;
}

/*!
 * \fn void Plugins::PluginBase::onRoomEntered()
 *
 * Triggered when the room in which the plugin is loaded is entered. The focus state is by default set to idle.
 * The corresponding roomEntered signal is emitted here.
 */
void Plugins::PluginBase::onRoomEntered()
{
    emit (roomEntered());
    this->setFocusState(Plugins::PluginEnums::pluginIdleState);
}

/*!
 * \fn void Plugins::PluginBase::onRoomLeft()
 *
 * Emitted when the room in which the plugin is loaded is left. The focus state is by default set to idle.
 * The corresponding roomLeft signal is emitted here.
 */
void Plugins::PluginBase::onRoomLeft()
{
    emit (roomLeft());
    this->setFocusState(Plugins::PluginEnums::pluginIdleState);
}

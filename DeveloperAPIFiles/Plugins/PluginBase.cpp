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
 * \fn int Plugins::PluginBase::getPluginId()
 *
 * Returns the id of the plugins.
 */


/*!
 * \fn QString Plugins::PluginBase::getPluginName()
 *
 * Returns the name of the plugins.
 */

/*!
 * \fn QString Plugins::PluginBase::getPluginDescription()
 *
 * Returns a description of the plugin.
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
 * \fn void Plugins::PluginBase::exposeContentToQml(QQmlContext *context)
 *
 * Exposes QML content to the QML \a context if the plugins needs it. If you wish to easily pass
 * data between your C++ plugin and its QML file, you should create a mapping class and expose it to the \a context.
 *
 * For more information, consider reading the following link : \l {http://qt-project.org/doc/qt-5.0/qtqml/qtqml-cppintegration-exposecppattributes.html}
 */

/*!
 * \fn void Plugins::PluginBase::receiveResultFromSQLQuery(QList<QSqlRecord> result, int id)
 *
 * Called by the Database Service Library to transmit the \a result of a previously executed query as well
 * as and \a id to help recognize the query.
 */

/*!
 * \fn void Plugins::PluginBase::receiveResultFromHttpRequest(QNetworkReply *reply)
 *
 * Triggered when the \a reply of a previously executed network request is received.
 */

/*!
 * \fn void Plugins::PluginBase::executeSQLQuery(const QString& query, QObject *sender, int id)
 *
 * Emitted when a database \a query needs to be executed. The result of its execution will be transmitted to the \a sender
 * along with an \a id to recognize the query.
 */

/*!
 * \fn void Plugins::PluginBase::executeHttpRequest(const QNetworkRequest &request, int requestType, QHttpMultiPart *multipart, QObject *sender)
 *
 * Emitted when a network \a request needs to be performed, with the \a requestType to identify the type HTTP request and a \a multipart which can be null to transmit
 * data through the request. The reply will be transmitted to \a sender.
 */

/*!
 * \fn void Plugins::PluginBase::askForFocusState(Plugins::PluginEnums::PluginState requestedState, QObject *sender)
 *
 * Emitted when a plugin ask for a new focus state \a requestedState. The response will be transmitted to \a sender.
 */

/*!
 * \fn void Plugins::PluginBase::focusStateChanged(QVariant focusState)
 *
 * Emitted when the \a focusState of a plugin has changed.
 */

/*!
 * Constructs a new Plugins::PluginBase instance.
 */
Plugins::PluginBase::PluginBase() : QObject()
{
    qDebug() << "NEW PLUGINBASE INSTANCE CREATED ";
    this->focusHandler[Plugins::PluginEnums::pluginIdleState]     = &Plugins::PluginBase::onIdleFocusState;
    this->focusHandler[Plugins::PluginEnums::pluginSelectedState] = &Plugins::PluginBase::onSelectedFocusState;
    this->focusHandler[Plugins::PluginEnums::pluginFocusedState]  = &Plugins::PluginBase::onFocusedFocusState;
    this->setFocusState(Plugins::PluginEnums::pluginIdleState);
    this->initPlugin();
}

/*!
 * \fn void Plugins::PluginBase::initPlugin()
 *
 * Initializes the plugins.
 */
void        Plugins::PluginBase::initPlugin()
{
}

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
    qDebug() << "Setting Focus State " << requestedState;
    Plugins::PluginEnums::PluginState oldFocusState = this->focusState;
    this->focusState = requestedState;
    // CALL FOCUS STATE HANDLER
    (this->*this->focusHandler[this->focusState])();
    emit (focusStateChanged(QVariant(requestedState), QVariant(oldFocusState)));
}

/*!
 * When a plugin wishes to change its focusState, call this method with the required \a requestedState.
 */
void    Plugins::PluginBase::askForFocusState(Plugins::PluginEnums::PluginState requestedState)
{
    // ASK THE ROOM FOR A NEW FOCUS STATE
    emit askForFocusState(requestedState, this);
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
 * Sends Http Get \a request to network manager, \a requestId will be transmitted with the reply to identify the request.
 */
void    Plugins::PluginBase::executeHttpGetRequest(const QNetworkRequest &request, int requestId, void *data)
{
    emit executeHttpRequest(request, Get, NULL, this, requestId, data);
}

/*!
 * Sends Http Delete \a request to network manager, \a requestId will be transmitted with the reply to identify the request.
 */
void    Plugins::PluginBase::executeHttpDeleteRequest(const QNetworkRequest &request, int requestId, void *data)
{
    emit executeHttpRequest(request, Delete, NULL, this, requestId, data);
}

/*!
 * Sends Http Post \a request to network manager with \a multiPart for data, \a requestId will be transmitted with the reply to identify the request.
 */
void    Plugins::PluginBase::executeHttpPostRequest(const QNetworkRequest &request, QHttpMultiPart* multiPart, int requestId, void *data)
{
    emit executeHttpRequest(request, Post, multiPart, this, requestId, data);
}

/*!
 * Sends Http Put \a request to network manager with \a multiPart for data, \a requestId will be transmitted with the reply to identify the request.
 */
void    Plugins::PluginBase::executeHttpPutRequest(const QNetworkRequest &request, QHttpMultiPart* multiPart, int requestId, void *data)
{
    emit executeHttpRequest(request, Put, multiPart, this, requestId, data);
}

/*!
 * Returns a boolean telling whether this pluugin needs logical updating every seconds or not.
 */
bool    Plugins::PluginBase::needsUpdating() const
{
    return false;
}

/*!
 * Exposes the plugin C++ class to the QML Context. That way the methods marked as
 * QINVOKABLE of the plugin class can be called by prefixing them with the PluginNames
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
 * \fn void Plugins::PluginBase::roomEntered()
 *
 * Triggered when the room in which the plugin is loaded is entered. The focus state is by default set to idle.
 */
void Plugins::PluginBase::onRoomEntered()
{
    emit (roomEntered());
    this->setFocusState(Plugins::PluginEnums::pluginIdleState);
}

/*!
 * \fn void Plugins::PluginBase::roomLeft()
 *
 * Emitted when the room in which the plugin is loaded is left. The focus state is by default set to idle.
 */
void Plugins::PluginBase::onRoomLeft()
{
    emit (roomLeft());
    this->setFocusState(Plugins::PluginEnums::pluginIdleState);
}

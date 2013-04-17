#include "PluginQmlPluginProperties.h"

/*!
 * \class Plugins::PluginQmlPluginProperties
 * \code
 * #include <PluginQmlPluginProperties.h>
 * \endcode
 *
 * \brief The Plugins::PluginQmlPluginProperties class is a custom
 * QQuickItem class that allows to access a plugin's logical properties
 * from the Qml View.
 *
 * \inmodule Tepee3D
 */

/*!
 * \property int Plugins::PluginQmlPluginProperties::pluginId
 */

/*!
 * \property int Plugins::PluginQmlPluginProperties::pluginRoomId
 */

/*!
 * \property Plugins::PluginEnums::PluginState Plugins::PluginQmlPluginProperties::focusState
 */

/*!
 * Constructs a new Plugins::PluginQmlPluginProperties instance.
 */
Plugins::PluginQmlPluginProperties::PluginQmlPluginProperties() : QQuickItem()
{
    qDebug() << "PluginQmlProperties Created";
    this->pluginId = -1;
    this->pluginRoomId = -1;
    this->plugin = NULL;
}

/*!
 * Destroys a Plugins::PluginQmlPluginProperties instance, disconnection signals from the Plugins::PluginBase
 * it is refering to if existing.
 *
 */
Plugins::PluginQmlPluginProperties::~PluginQmlPluginProperties()
{
    if (this->plugin != NULL)
    {
        QObject::disconnect(this->plugin, SIGNAL(focusStateChanged(QVariant, QVariant)), this, SIGNAL(focusStateChanged(QVariant, QVariant)));
        QObject::disconnect(this->plugin, SIGNAL(roomEntered()), this, SIGNAL(roomEntered()));
        QObject::disconnect(this->plugin, SIGNAL(roomLeft()), this, SIGNAL(roomLeft()));
    }
    delete this->plugin;
}

/*!
 * Requests the new \a focusState of the plugin.
 */
void    Plugins::PluginQmlPluginProperties::askForFocusState(int focusState)
{
    qDebug() << "PluginQmlProperties askForFocusState " << focusState;
    if (this->plugin)
        this->plugin->askForFocusState(Plugins::PluginEnums::valueOf(focusState));
}

/*!
 * Sets the plugin id to \a id.
 */
void    Plugins::PluginQmlPluginProperties::setPluginId(int id)
{
    this->pluginId = id;
    this->findPluginForRoomAndPluginId();
    emit (pluginIdChanged());
}

/*!
 * Returns the plugin id.
 */
int     Plugins::PluginQmlPluginProperties::getPluginId() const
{
    return this->pluginId;
}

/*!
 * Sets the room Id \a id of the current plugin.
 */
void    Plugins::PluginQmlPluginProperties::setPluginRoomId(int id)
{
    this->pluginRoomId = id;
    this->findPluginForRoomAndPluginId();
    emit (pluginRoomIdChanged());
}

/*!
 * Returns the room Id of the currentPlugin.
 */
int     Plugins::PluginQmlPluginProperties::getPluginRoomId()   const
{
    return this->pluginRoomId;
}

/*!
 * Returns the focusState of the plugin.
 */
Plugins::PluginEnums::PluginState    Plugins::PluginQmlPluginProperties::getFocusState() const
{
    if (this->plugin)
        return this->plugin->getFocusState();
    return Plugins::PluginEnums::pluginIdleState;
}

/*!
 * Finds and sets the PluginQmlPluginProperties to the plugin identified by a pluginId in a given room
 * identified by a roomId.
 */
void    Plugins::PluginQmlPluginProperties::findPluginForRoomAndPluginId()
{
    if (this->pluginId != -1 && this->pluginRoomId != -1)
    {
        qDebug() << "Plugin and roomId are valid";
        this->plugin = View::ViewToModelMapper::getPluginFromRoom(this->pluginRoomId, this->pluginId);
        QObject::connect(this->plugin, SIGNAL(focusStateChanged(QVariant, QVariant)), this, SIGNAL(focusStateChanged(QVariant, QVariant)));
        QObject::connect(this->plugin, SIGNAL(roomEntered()), this, SIGNAL(roomEntered()));
        QObject::connect(this->plugin, SIGNAL(roomLeft()), this, SIGNAL(roomLeft()));
        this->plugin->setFocusState(Plugins::PluginEnums::pluginIdleState);
    }
}

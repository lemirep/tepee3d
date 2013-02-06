#include "PluginQmlPluginProperties.h"

/*!
 * \class Plugins::PluginQmlPluginProperties
 *
 * \brief The Plugins::PluginQmlPluginProperties class is a custom
 * QQuickItem class that allows to access a plugin's logical properties
 * from the Qml View.
 */

Plugins::PluginQmlPluginProperties::PluginQmlPluginProperties() : QQuickItem()
{
    qDebug() << "PluginQmlProperties Created";
    this->pluginId = -1;
    this->pluginRoomId = -1;
    this->plugin = NULL;
}


void    Plugins::PluginQmlPluginProperties::askForFocusState(int focusState)
{
    qDebug() << "PluginQmlProperties askForFocusState " << focusState;
    if (this->plugin)
        this->plugin->askForFocusState(Plugins::PluginEnums::valueOf(focusState));
}

void    Plugins::PluginQmlPluginProperties::setPluginId(int id)
{
    this->pluginId = id;
    this->findPluginForRoomAndPluginId();
    emit (pluginIdChanged());
}

int     Plugins::PluginQmlPluginProperties::getPluginId() const
{
    return this->pluginId;
}

void    Plugins::PluginQmlPluginProperties::setPluginRoomId(int id)
{
    this->pluginRoomId = id;
    this->findPluginForRoomAndPluginId();
    emit (pluginRoomIdChanged());
}

int     Plugins::PluginQmlPluginProperties::getPluginRoomId()   const
{
    return this->pluginRoomId;
}

void    Plugins::PluginQmlPluginProperties::setFocusState(Plugins::PluginEnums::PluginState focusState)
{
    if (this->plugin)
    {
        this->plugin->setFocusState(focusState);
        emit (focusStateChanged(focusState));
    }
}

Plugins::PluginEnums::PluginState    Plugins::PluginQmlPluginProperties::getFocusState() const
{
    if (this->plugin)
        return this->plugin->getFocusState();
    return Plugins::PluginEnums::pluginIdleState;
}

void    Plugins::PluginQmlPluginProperties::findPluginForRoomAndPluginId()
{
    if (this->pluginId != -1 && this->pluginRoomId != -1)
    {
        qDebug() << "Plugin and roomId are valid";
        this->plugin = View::ViewToModelMapper::getPluginFromRoom(this->pluginRoomId, this->pluginId);
        QObject::connect(this->plugin, SIGNAL(focusStateChanged(QVariant)), this, SIGNAL(focusStateChanged(QVariant)));
        QObject::connect(this->plugin, SIGNAL(roomEntered()), this, SIGNAL(roomEntered()));
        QObject::connect(this->plugin, SIGNAL(roomLeft()), this, SIGNAL(roomLeft()));
        this->plugin->setFocusState(Plugins::PluginEnums::pluginIdleState);
    }
}

#include "PluginQmlPluginProperties.h"

Plugins::PluginQmlPluginProperties::PluginQmlPluginProperties() : QQuickItem()
{
    qDebug() << "PluginQmlProperties Created";
    this->pluginId = -1;
    this->pluginRoomId = -1;
    this->plugin = NULL;
}


void    Plugins::PluginQmlPluginProperties::askForFocusState(Plugins::PluginEnums::PluginState focusState)
{
    qDebug() << "PluginQmlProperties askForFocusState";
}

void    Plugins::PluginQmlPluginProperties::setPluginId(int id)
{
    this->pluginId = id;
    this->findPluginForRoomAndPluginId();
    emit (pluginIdChanged());
//    emit focusStateChanged(Plugins::PluginEnums::pluginIdleState);
//    emit focusStateChanged(Plugins::PluginEnums::pluginFocusedState);
//    emit focusStateChanged(Plugins::PluginEnums::pluginSelectedState);
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
        this->plugin->setFocusState(Plugins::PluginEnums::pluginIdleState);
    }
}

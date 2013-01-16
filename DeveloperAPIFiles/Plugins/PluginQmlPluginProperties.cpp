#include "PluginQmlPluginProperties.h"

Plugins::PluginQmlPluginProperties::PluginQmlPluginProperties() : QQuickItem()
{
    qDebug() << "PluginQmlProperties Created";
    this->pluginId = -1;
    this->plugin = NULL;
}


void    Plugins::PluginQmlPluginProperties::askForFocusState(Plugins::PluginEnums::PluginState focusState)
{
    qDebug() << "PluginQmlProperties askForFocusState";
}

void    Plugins::PluginQmlPluginProperties::setPluginId(int id)
{
    this->pluginId = id;

    // FIND PLUGINBASE WITH GIVEN ID AND SAVE IT IN this->plugin

    emit (pluginIdChanged());
    emit focusStateChanged(Plugins::PluginEnums::pluginIdleState);
//    emit focusStateChanged(Plugins::PluginEnums::pluginFocusedState);
//    emit focusStateChanged(Plugins::PluginEnums::pluginSelectedState);
}

int     Plugins::PluginQmlPluginProperties::getPluginId() const
{
    return this->pluginId;
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

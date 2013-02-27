#include "PluginModelItem.h"
// DEBUG
#include <QDebug>

Plugins::PluginModelItem::PluginModelItem(Plugins::PluginBase* plugin, QObject *parent) : ListItem(parent)
{
    this->plugin = plugin;
}

Plugins::PluginModelItem::~PluginModelItem()
{
    qDebug() << "DELETING PLUGIN MODEL ITEM";
}

/*!
 * Returns the id of the PluginModelItem.
 */
int     Plugins::PluginModelItem::id()  const
{
    return this->plugin->getPluginId();
}

/*!
 * Returns the role values of a given role of the PluginModelItem.
 */
QVariant    Plugins::PluginModelItem::data(int role)    const
{
    switch (role)
    {
    case pluginId :
        return this->id();
    case pluginName :
        return this->plugin->getPluginName();
    case pluginRoomQmlFile :
        return this->plugin->getRoomPluginQmlFile();
    case pluginMenuQmlFile :
        return this->plugin->getMenuPluginQmlFile();
    default :
        return QVariant();
    }
}

/*!
 * Returns a hash containing the roles of the PluginModelItem.
 */
QHash<int, QByteArray>  Plugins::PluginModelItem::roleNames()   const
{
    QHash<int, QByteArray>  roles;

    roles[pluginId]   = "pluginId";
    roles[pluginName] = "pluginName";
    roles[pluginRoomQmlFile] = "pluginRoomQmlFile";
    roles[pluginMenuQmlFile] = "pluginMenuQmlFile";

    return roles;
}

/*!
 * Returns the instance of the plugin the PluginModelItem is a description of.
 */

Plugins::PluginBase*    Plugins::PluginModelItem::getPlugin()   const
{
    return this->plugin;
}

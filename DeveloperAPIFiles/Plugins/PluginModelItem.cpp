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

int     Plugins::PluginModelItem::id()  const
{
    return this->plugin->getPluginId();
}

QVariant    Plugins::PluginModelItem::data(int role)    const
{
    switch (role)
    {
    case pluginId :
        return this->id();
    case pluginName :
        return this->plugin->getPluginName();
    default :
        return QVariant();
    }
}

QHash<int, QByteArray>  Plugins::PluginModelItem::roleNames()   const
{
    QHash<int, QByteArray>  roles;

    roles[pluginId]   = "pluginId";
    roles[pluginName] = "pluginName";

    return roles;
}

Plugins::PluginBase*    Plugins::PluginModelItem::getPlugin()   const
{
    return this->plugin;
}

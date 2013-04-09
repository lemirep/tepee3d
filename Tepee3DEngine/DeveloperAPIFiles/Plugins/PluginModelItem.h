#ifndef PLUGINMODELITEM_H
#define PLUGINMODELITEM_H

#include "ListItem.h"
#include "PluginBase.h"

namespace Models
{

class PluginModelItem : public Models::ListItem
{
    Q_OBJECT

public:

    enum    PluginModelItemRoles
    {
        pluginId    =   Qt::UserRole + 1,
        pluginName,
        pluginRoomQmlFile,
        pluginMenuQmlFile,
        pluginPosition
    };

    explicit PluginModelItem(Plugins::PluginBase *plugin, QObject *parent = 0);
    ~PluginModelItem();

    int                     id()                const;
    QVariant                data(int role)      const;
    QHash<int, QByteArray>  roleNames()         const;
    Plugins::PluginBase*    getPlugin()         const;

private:
    Plugins::PluginBase*    plugin;

};

}

#endif // PLUGINMODELITEM_H

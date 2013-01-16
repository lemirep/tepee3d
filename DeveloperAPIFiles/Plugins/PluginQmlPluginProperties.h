#ifndef PLUGINQMLPLUGINPROPERTIES_H
#define PLUGINQMLPLUGINPROPERTIES_H

#include <QObject>
#include <QQuickItem>
#include <QDebug>
#include "PluginBase.h"
#include "PluginEnums.h"

namespace Plugins
{
// USED TO FIND PLUGIN BASE FROM QML
class PluginQmlPluginProperties : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int pluginId READ getPluginId WRITE setPluginId NOTIFY pluginIdChanged)
    Q_PROPERTY(Plugins::PluginEnums::PluginState focusState READ getFocusState NOTIFY focusStateChanged)

public:
    PluginQmlPluginProperties();

    Q_INVOKABLE void askForFocusState(PluginEnums::PluginState);

    int     getPluginId()   const;
    void    setPluginId(int id);

    PluginEnums::PluginState    getFocusState() const;
    void                        setFocusState(PluginEnums::PluginState focusState);

private:
    int                 pluginId;
    PluginBase *plugin;


signals:
    void pluginIdChanged();
    void focusStateChanged(QVariant newFocusStateValue);
};
}
#endif // PLUGINQMLPLUGINPROPERTIES_H

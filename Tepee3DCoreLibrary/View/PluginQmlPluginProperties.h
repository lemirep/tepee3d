#ifndef PLUGINQMLPLUGINPROPERTIES_H
#define PLUGINQMLPLUGINPROPERTIES_H

#include <QObject>
#include <QQuickItem>
#include <QDebug>
#include "ViewToModelMapper.h"
#include "PluginBase.h"
#include "PluginEnums.h"

// CUSTOM C++ QML OBJECT USED TO MAP A QML PLUGIN TO A PLUGINBASE MODEL

namespace Plugins
{
// USED TO FIND PLUGIN BASE FROM QML
class PluginQmlPluginProperties : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int pluginId READ getPluginId WRITE setPluginId NOTIFY pluginIdChanged)
    Q_PROPERTY(int pluginRoomId READ getPluginRoomId WRITE setPluginRoomId NOTIFY pluginRoomIdChanged)
    Q_PROPERTY(Plugins::PluginEnums::PluginState focusState READ getFocusState NOTIFY focusStateChanged)
    Q_ENUMS(Plugins::PluginEnums::PluginState)

public:
    explicit PluginQmlPluginProperties();
    ~PluginQmlPluginProperties();

    Q_INVOKABLE void            askForFocusState(int);

    int                         getPluginId()   const;
    void                        setPluginId(int id);

    int                         getPluginRoomId()   const;
    void                        setPluginRoomId(int id);

    PluginEnums::PluginState    getFocusState() const;

private:
    int                 pluginId;
    int                 pluginRoomId;
    PluginBase          *plugin;

    void                        findPluginForRoomAndPluginId();

signals:
    void                        pluginIdChanged();
    void                        focusStateChanged(QVariant newFocusStateValue, QVariant previousFocusState);
    void                        pluginRoomIdChanged();
    void                        roomEntered();
    void                        roomLeft();
};
}
#endif // PLUGINQMLPLUGINPROPERTIES_H

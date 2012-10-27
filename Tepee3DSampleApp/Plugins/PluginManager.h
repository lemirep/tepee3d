#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QSignalMapper>
#include <QHash>
#include <PluginBase.h>
#include "PluginLoader.h"
#include "QmlContentExposerInterface.h"
#include "ListModel.h"
#include "PluginModelItem.h"

namespace Plugins
{
class PluginManager : public QObject, public QmlContentExposerInterface
{
    Q_OBJECT
public:
    explicit PluginManager(QObject *parent = 0);
    ~PluginManager();

    QHash<PluginBase *, int>   getPluginsHash()  const;
    QList<PluginBase *>        getAvailablePlugins() const;
    void                       loadLocalPlugins();

    void                       exposeContentToQml(QQmlContext *context);
private:
    QSignalMapper   *signalMapper;
    QHash<PluginBase *, int>   loadedPlugins;
    ListModel*      availablePluginsModel;

};
}

#endif // PLUGINMANAGER_H

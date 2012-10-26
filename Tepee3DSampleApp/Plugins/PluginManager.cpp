#include "PluginManager.h"

Plugins::PluginManager::PluginManager(QObject *parent) : QObject(parent)
{
    this->loadedPlugins = QHash<PluginBase *, int>();
    this->loadLocalPlugins();
    // THE SIGNAL MAPPER WILL BE USED TO MANAGE CONNECTIONS BETWEEN
    // PLUGINS AND THE SERVICE MANAGER, AUTOMATICALLY PASSING THE PLUGIN
    // INSTANCE TO SERVICE SIGNALS SO THAT THE SERVICE AUTOMATICALLY RESPONDS TO THE PLUGIN
    // WHO MADE THE REQUEST
    this->signalMapper = new QSignalMapper(this);
}

Plugins::PluginManager::~PluginManager()
{
}

void Plugins::PluginManager::loadLocalPlugins()
{
    PluginLoader::loadWidgetPlugins();
}

QList<Plugins::PluginBase *> Plugins::PluginManager::getAvailablePlugins() const
{
    return PluginLoader::getWidgetPlugins();
}

QHash<Plugins::PluginBase *, int>   Plugins::PluginManager::getPluginsHash() const
{
    return this->loadedPlugins;
}

void    Plugins::PluginManager::exposeContentToQml(QQmlContext *context)
{

}

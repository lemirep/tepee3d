#include "PluginManager.h"

Plugins::PluginManager::PluginManager(QObject *parent) : QObject(parent)
{
    this->loadedPlugins = QHash<PluginBase *, int>();
    this->availablePluginsModel = NULL;
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
    if (this->availablePluginsModel == NULL)
        this->availablePluginsModel = new ListModel(new Plugins::PluginModelItem(NULL, NULL));
    else
        this->availablePluginsModel->clear();
    foreach (Plugins::PluginBase*  plugin, PluginLoader::getWidgetPlugins())
        this->availablePluginsModel->appendRow(new Plugins::PluginModelItem(plugin, this));
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
    context->setContextProperty("availablePluginsModel", this->availablePluginsModel);
}

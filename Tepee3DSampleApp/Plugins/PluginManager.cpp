#include "PluginManager.h"
// DEBUG
#include <QDebug>


/*!
 * \namespace Plugins
 * \brief The Plugins namespace contains classes responsible for plugin
 * management, plugin declaration and plugin model represantation.
 */

/*!
 * \class Plugins::PluginManager
 * \brief The Plugins::PluginManager class manages plugins. It loads locally
 * available plugins, allow the creation of a new plugin instance and initializes
 * it for it to work within the Tepee3D application.
 *
 * The Plugins::PluginsManager class is a singleton class. When initialized, it asks
 * for the locally available plugins and creates a model containing them. This model
 * hold the plugin representations available in the add new plugin menu of the
 * application. It also offers a way to create a new instance of a given plugin. The
 * locally available plugins only serve as a presentation purpose and are not
 * initialized the same way as room plugins. Then, a plugin instance can be initialized
 * for use inside a room by connecting it to the various services and exposing eventual
 * Qml content to the Qml Engine.
 *
 *\sa Plugins::PluginsLoader
 */

ListModel* Plugins::PluginManager::locallyAvailablePluginsModel = NULL;
ListModel* Plugins::PluginManager::onlineAvailablePluginsModel = NULL;
Plugins::PluginManager* Plugins::PluginManager::instance = NULL;

Plugins::PluginManager::PluginManager(QObject *parent) : QObject(parent)
{
    this->loadLocalPlugins();
    // THE SIGNAL MAPPER WILL BE USED TO MANAGE CONNECTIONS BETWEEN
    // PLUGINS AND THE SERVICE MANAGER, AUTOMATICALLY PASSING THE PLUGIN
    // INSTANCE TO SERVICE SIGNALS SO THAT THE SERVICE AUTOMATICALLY RESPONDS TO THE PLUGIN
    // WHO MADE THE REQUEST
//    this->signalMapper = new QSignalMapper(this);
}

Plugins::PluginManager::~PluginManager()
{
}

Plugins::PluginManager* Plugins::PluginManager::getInstance(QObject *parent)
{
    if (Plugins::PluginManager::instance == NULL)
        Plugins::PluginManager::instance = new Plugins::PluginManager(parent);
    return Plugins::PluginManager::instance;
}

// REFRESH LOCALLY AVAILABLE PLUGINS ON A REGULAR BASIC TO ALWAYS BE UP TO DATE
void Plugins::PluginManager::loadLocalPlugins()
{
    PluginLoader::loadWidgetPlugins();
    if (Plugins::PluginManager::locallyAvailablePluginsModel == NULL)
        Plugins::PluginManager::locallyAvailablePluginsModel = new ListModel(new Plugins::PluginModelItem(NULL, NULL));
    else
        Plugins::PluginManager::locallyAvailablePluginsModel->clear();
    foreach (Plugins::PluginBase*  plugin, PluginLoader::getWidgetPlugins())
    {
        Plugins::PluginManager::locallyAvailablePluginsModel->appendRow(new Plugins::PluginModelItem(plugin, this));
        // DO PLUGIN CONNECTION TO SIGNAL MAPPER FOR SERVICES HERE
    }
}

void    Plugins::PluginManager::receiveResultFromSQLQuery(const QList<QSqlRecord> &, int)
{
    qDebug() << "PluginManager Received Result";
}

Plugins::PluginBase* Plugins::PluginManager::getNewInstanceOfPlugin(PluginBase *plugin)
{
    if (plugin == NULL)
        return NULL;
    return plugin->createNewInstance();
}

Plugins::PluginBase* Plugins::PluginManager::getNewInstanceOfPlugin(int pluginModelItemId)
{
    Plugins::PluginModelItem*   pluginModelItem = NULL;
    Plugins::PluginBase *pluginBase = NULL;
    if ((pluginModelItem = (Plugins::PluginModelItem*)Plugins::PluginManager::locallyAvailablePluginsModel->find(pluginModelItemId)) != NULL)
        pluginBase = pluginModelItem->getPlugin();

    return Plugins::PluginManager::getNewInstanceOfPlugin(pluginBase);
}

void    Plugins::PluginManager::initRoomPlugin(PluginBase *roomPlugin)
{
    // CONNECT OBJECT TO SERVICES
    Services::ServicesManager::connectObjectToServices(roomPlugin);
    // EXPOSE QML CONTENT FROM PLUGIN
    View::QmlViewProperties::exposeContentToQml(roomPlugin);
}

void    Plugins::PluginManager::exposeContentToQml(QQmlContext *context)
{
    context->setContextProperty("availablePluginsModel", this->locallyAvailablePluginsModel);
    qmlRegisterType<Plugins::PluginEnums>("Plugins", 1, 0, "PluginEnums");
    qmlRegisterType<Plugins::PluginQmlPluginProperties>("Plugins", 1, 0, "PluginProperties");
}

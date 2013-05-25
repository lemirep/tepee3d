#include "PluginManager.h"
// DEBUG
#include <QDebug>


/*!
 * \namespace Plugins
 * \brief The Plugins namespace contains classes responsible for plugin
 * management, plugin declaration and plugin model representation.
 *
 * \inmodule Tepee3D
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
 * \since 1.0
 * \sa Plugins::PluginsLoader
 * \inmodule Tepee3D
 */

Models::ListModel* Plugins::PluginManager::locallyAvailablePluginsModel = NULL;
Models::ListModel* Plugins::PluginManager::onlineAvailablePluginsModel = NULL;
Plugins::PluginManager* Plugins::PluginManager::instance = NULL;

/*!
 * Initializes the Plugins::PluginsManager instance.
 */

Plugins::PluginManager::PluginManager(QObject *parent) : QObject(parent)
{
    this->webServicesCallBacks[GET_ONLINE_PLUGINS] = &Plugins::PluginManager::retrieveOnlinePluginsForCurrentPlatformCallBack;
    this->loadLocalPlugins();
}

/*!
 * Asks the Tepee3D server for a list of available plugins for the current platform.
 */
void Plugins::PluginManager::retrieveOnlinePluginsForCurrentPlatform()
{
    // CREATE A JSON FOR THE REQUEST
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart httpPart;
    httpPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    httpPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"json\""));

    QJsonObject requestObj;
    QJsonObject commandObj;

    commandObj.insert("command", QJsonValue(QString("getPlugins")));
    commandObj.insert("plateform", QJsonValue(PlatformFactory::getPlatformInitializer()->getPlatformName()));
    requestObj.insert("request", QJsonValue(commandObj));

    httpPart.setBody(QJsonDocument(requestObj).toJson());
    multiPart->append(httpPart);

    // EXECUTE THE REQUEST
    emit executeHttpRequest(QNetworkRequest(QUrl("http://tepee3d.dyndns.org:3000")),
                            WebServiceUserInterface::Post,
                            multiPart,
                            this,
                            GET_ONLINE_PLUGINS);
}

/*!
 * Parses the json list of plugins returned by the Tepee3D server that are available for the current platform.
 */
void Plugins::PluginManager::retrieveOnlinePluginsForCurrentPlatformCallBack(QNetworkReply *reply, void *data)
{
    if (reply != NULL)
    {
        QJsonDocument jsonDoc = Utils::QJsonDocumentFromReply(reply);
        delete reply;

        qDebug() << ">>>>>Tepee3D Serveur Response <<" << jsonDoc.toJson() << ">>";

        if (!jsonDoc.isNull() && !jsonDoc.isEmpty() && jsonDoc.isObject())
        {
            // PARSE JSON ARRAY HERE
            // WAITING FOR THE SERVER TO BE READY TO PURSUE
            // DO NOT FORGET TO RESDTORE retrieveOnlinePluginsForCurrentPlatform as private
        }
    }
}

/*!
 * Receives results from the webservice worker.
 */
void Plugins::PluginManager::receiveResultFromHttpRequest(QNetworkReply *reply, int requestId, void *data)
{
    (this->*this->webServicesCallBacks[requestId])(reply, data);
}

/*!
 * Destroys a PluginManager instance.
 */
Plugins::PluginManager::~PluginManager()
{
}

/*!
 *  Returns a singleton instance of the class from a QObject \a parent.
 */
Plugins::PluginManager* Plugins::PluginManager::getInstance(QObject *parent)
{
    if (Plugins::PluginManager::instance == NULL)
        Plugins::PluginManager::instance = new Plugins::PluginManager(parent);
    return Plugins::PluginManager::instance;
}


// REFRESH LOCALLY AVAILABLE PLUGINS ON A REGULAR BASIC TO ALWAYS BE UP TO DATE
/*!
 * Loads all locally available plugins in the static locallyAvailablePluginModel ListModel.
 */
void Plugins::PluginManager::loadLocalPlugins()
{
    PluginLoader::loadWidgetPlugins();
    if (Plugins::PluginManager::locallyAvailablePluginsModel == NULL)
        Plugins::PluginManager::locallyAvailablePluginsModel = new Models::ListModel(new Models::PluginModelItem(NULL, NULL));
    else
        Plugins::PluginManager::locallyAvailablePluginsModel->clear();
    foreach (Plugins::PluginBase*  plugin, PluginLoader::getWidgetPlugins())
    {
        Plugins::PluginManager::locallyAvailablePluginsModel->appendRow(new Models::PluginModelItem(plugin, this));
        // DO PLUGIN CONNECTION TO SIGNAL MAPPER FOR SERVICES HERE
    }
}

/*!
 * Returns a new instance of plugin from \a plugin.
 */
Plugins::PluginBase* Plugins::PluginManager::getNewInstanceOfPlugin(Plugins::PluginBase *plugin)
{
    if (plugin == NULL)
        return NULL;
    return plugin->createNewInstance();
}

/*!
 * Returns a new instance of the plugin identified by \a pluginModelItemId in the locallyAvailablePlugin list.
 */
Plugins::PluginBase* Plugins::PluginManager::getNewInstanceOfPlugin(int pluginModelItemId)
{
    Models::PluginModelItem*   pluginModelItem = NULL;
    Plugins::PluginBase *pluginBase = NULL;
    if ((pluginModelItem = (Models::PluginModelItem*)Plugins::PluginManager::locallyAvailablePluginsModel->find(pluginModelItemId)) != NULL)
        pluginBase = pluginModelItem->getPlugin();

    return Plugins::PluginManager::getNewInstanceOfPlugin(pluginBase);
}

/*!
 * Initializes \a roomPlugin to all the services a plugin can register to.
 */
void    Plugins::PluginManager::initRoomPlugin(PluginBase *roomPlugin)
{
    // CONNECT OBJECT TO SERVICES
    Services::ServicesManager::connectObjectToServices(roomPlugin);
    // EXPOSE QML CONTENT FROM PLUGIN
    View::QmlViewProperties::exposeContentToQml(roomPlugin);
    // CALL THE INIT METHOD OF THE PLUGIN
    roomPlugin->initPlugin();
}

/*!
 * Performs the necessary cleaning, disconnections of signals from \a roomPlugin
 * so that it can properly be deleted.
 */
void Plugins::PluginManager::cleanPluginBeforeRemoval(Plugins::PluginBase *roomPlugin)
{
    roomPlugin->clearPluginBeforeRemoval();
    Services::ServicesManager::disconnectObjectFromServices(roomPlugin);
}

/*!
 * Exposes to QML Context \a context all Plugins entities required by the Tepee3DEngine.
 */
void    Plugins::PluginManager::exposeContentToQml(QQmlContext *context)
{
    context->setContextProperty("availablePluginsModel", this->locallyAvailablePluginsModel);
    qmlRegisterType<Plugins::PluginEnums>("Plugins", 1, 0, "PluginEnums");
    qmlRegisterType<Plugins::PluginQmlPluginProperties>("Plugins", 1, 0, "PluginProperties");
}

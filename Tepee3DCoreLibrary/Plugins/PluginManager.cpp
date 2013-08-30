/****************************************************************************
**
** Copyright (C) Paul Lemire, Tepee3DTeam and/or its subsidiary(-ies).
** Contact: paul.lemire@epitech.eu
** Contact: tepee3d_2014@labeip.epitech.eu
**
** This file is part of the Tepee3D project
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
****************************************************************************/

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
 * Furthermore, it also handles the downloads of new and updated plugins.
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
    this->webServicesCallBacks[GET_PLUGINS_UPDATES] = &Plugins::PluginManager::checkForPluginsUpdatesCallBack;
    this->streamServicesCallBacks[DOWNLOAD_PLUGIN_INDEX] = &Plugins::PluginManager::downloadPluginIndexCallBack;
    this->streamServicesCallBacks[DOWNLOAD_PLUGIN_FILE] = &Plugins::PluginManager::downloadPluginFileCallBack;
    this->loadLocalPlugins();
}


/*!
 * Asks the Tepee3D server for a list of available plugins for the current platform.
 */
void Plugins::PluginManager::retrieveOnlinePluginsForCurrentPlatform()
{
    //TEPEE3D_ONLINE_API + widgets
    emit executeHttpRequest(QNetworkRequest(QUrl(QString(TEPEE3D_ONLINE_API)
                                                 + "widgets/?platforms__name__in="
                                                 + PlatformFactory::getPlatformInitializer()->getPlatformName())),
                            WebServiceUserInterface::Get,
                            NULL,
                            this,
                            GET_ONLINE_PLUGINS);

    qDebug() << "<><><><><><><><><><><><><><><><><>" + QString(TEPEE3D_ONLINE_API)
                + "widgets/?platforms__name__in="
                + PlatformFactory::getPlatformInitializer()->getPlatformName();
}

/*!
 * Asks the server to send the plugin identifier by \a pluginId
 */
void Plugins::PluginManager::downloadPluginFromServer(int pluginId)
{
    // TRY TO RETRIEVE THE index FILE CONTAINING ALL FILES NEEDED TO BE DOWNLOADED BY A WIDGET
    // IF FILE EXISTS, PLUGIN IS AVAILABLE FOR PLATFORM
    // OTHERWISE IT ISN'T

    Models::ListItem* pluginItem = this->onlineAvailablePluginsModel->find(pluginId);
    Models::PluginOnlineModelItem* pluginOnlineItem = reinterpret_cast<Models::PluginOnlineModelItem *>(pluginItem);

    if (pluginOnlineItem != NULL &&
            !pluginOnlineItem->getPluginDownloaded() &&
            !pluginOnlineItem->getPluginDownloading())
    {
        pluginOnlineItem->setPluginDownloadError(false);
        QDir pluginDir = QDir(PlatformFactory::getPlatformInitializer()->getWidgetsResourceDirectory().absoluteFilePath(pluginOnlineItem->getPluginRepoName()));
        qDebug() << pluginDir.absolutePath();
        qDebug() << pluginDir.dirName();
        qDebug() << "Repo Name " << pluginOnlineItem->getPluginRepoName();
        if (pluginDir.exists() ||
                (!pluginDir.exists() && PlatformFactory::getPlatformInitializer()->getWidgetsResourceDirectory().mkdir(pluginDir.dirName())))
        {
            qDebug() << "Plugin Dir exists";
            QFile *indexFile = new QFile(pluginDir.absoluteFilePath("index"));
            if (indexFile->open(QIODevice::ReadWrite))
            {
                emit executeFileDownloader(QNetworkRequest(QUrl(QString(TEPEE3D_WIDGETS_STORE)
                                                                + PlatformFactory::getPlatformInitializer()->getPlatformName()
                                                                + "/"
                                                                + pluginOnlineItem->getPluginRepoName()
                                                                + "/index")),
                                           Services::FileDownloaderServiceUserInterface::Get,
                                           NULL,
                                           indexFile,
                                           this,
                                           DOWNLOAD_PLUGIN_INDEX,
                                           pluginOnlineItem);
            }
        }
    }
}


/*!
 * Sends a list of the plugins currently installed and asking the server if any was updated.
 */
void Plugins::PluginManager::checkForPluginsUpdates()
{
    foreach (Models::ListItem *pluginItem, this->locallyAvailablePluginsModel->toList())
    {
        Plugins::PluginBase *plugin = reinterpret_cast<Models::PluginModelItem *>(pluginItem)->getPlugin();

        // EXECUTE THE REQUEST
        emit executeHttpRequest(QNetworkRequest(QUrl(QString(TEPEE3D_ONLINE_API)
                                                     + "widgets/"
                                                     + QString::number(plugin->getPluginId())
                                                     + "/")),
                                WebServiceUserInterface::Get,
                                NULL,
                                this,
                                GET_PLUGINS_UPDATES,
                                plugin);

        qDebug() << "<<<<<<<<<<<<<<<<<<<<< " + QString(TEPEE3D_ONLINE_API)
                    + "widgets/"
                    + QString::number(plugin->getPluginId());
    }
}

/*!
 * Returns the model containing widgets already downloaded by the application.
 */

Models::ListModel *Plugins::PluginManager::getLocallyAvailablePlugins() const
{
    return Plugins::PluginManager::locallyAvailablePluginsModel;
}

/*!
 * Returns a model containing a list of widgets available to download for the application on the platforms on whichi it runs.
 * If the models has not been initialized, it is done here.
 */

Models::ListModel *Plugins::PluginManager::getOnlineAvailablePlugins() const
{
    if (Plugins::PluginManager::onlineAvailablePluginsModel == NULL)
        Plugins::PluginManager::onlineAvailablePluginsModel = new Models::ListModel(new Models::PluginOnlineModelItem(-1));
    return Plugins::PluginManager::onlineAvailablePluginsModel;
}

/*!
 * Removes all the qml files, libraries, resources and databases associated with the downloaded plugin of id \a pluginId.
 */
void Plugins::PluginManager::removeDownloadedPlugin(int pluginId)
{
    Models::ListItem *pluginItem = this->locallyAvailablePluginsModel->find(pluginId);
    if (pluginItem != NULL)
    {
        Models::PluginOnlineModelItem *pluginOnlineItem = reinterpret_cast<Models::PluginOnlineModelItem *>(pluginItem);

        // NEEDS TO BE REMOVED FROM ALL ROOMS PRIOR TO THIS

        // REMOVE QML & RESOURCES DIR
        QDir qmlDir = QDir(PlatformFactory::getPlatformInitializer()->getWidgetsResourceDirectory().absoluteFilePath(pluginOnlineItem->getPluginRepoName()));
        qDebug() << "removing " << qmlDir.absolutePath();
        qmlDir.removeRecursively();
        // REMOVE LIBRARY
        QFile libFileUnix(PlatformFactory::getPlatformInitializer()->getWidgetSharedLibrariesDirectory().absoluteFilePath("lib" + pluginOnlineItem->getPluginRepoName() + ".so"));
        if (libFileUnix.exists())
            libFileUnix.remove();
        QFile libFileWin(PlatformFactory::getPlatformInitializer()->getWidgetSharedLibrariesDirectory().absoluteFilePath("lib" + pluginOnlineItem->getPluginRepoName() + ".dll"));
        if (libFileWin.exists())
            libFileWin.remove();
        // REMOVE DATABASES
        QFile dbFile(PlatformFactory::getPlatformInitializer()->getDatabaseDirectory().absoluteFilePath(pluginOnlineItem->getPluginRepoName() + ".sql"));
        if (dbFile.exists())
            dbFile.remove();
    }
}

/*!
 * Parses the json list of plugins returned by the Tepee3D server that are available for the current platform.
 */
void Plugins::PluginManager::retrieveOnlinePluginsForCurrentPlatformCallBack(QNetworkReply *reply, void *data)
{
    Q_UNUSED(data)
    if (reply != NULL)
    {
        QJsonDocument jsonDoc = Utils::QJsonDocumentFromReply(reply);
        delete reply;
        if (!jsonDoc.isNull() && !jsonDoc.isEmpty() && jsonDoc.isObject())
        {
            QJsonObject resultObj = jsonDoc.object();
            if (resultObj.contains("objects"))
            {
                QJsonArray pluginsArray = resultObj.value("objects").toArray();
                if (!pluginsArray.isEmpty())
                {
                    this->getOnlineAvailablePlugins()->clear();
                    foreach (QJsonValue pluginValue, pluginsArray)
                    {
                        QJsonObject pluginObj = pluginValue.toObject();
                        Models::PluginOnlineModelItem *pluginOnlineItem = new Models::PluginOnlineModelItem(pluginObj.value("widget_id").toDouble());
                        pluginOnlineItem->setPluginName(pluginObj.value("name").toString());
                        pluginOnlineItem->setPluginDescription(pluginObj.value("description").toString());
                        pluginOnlineItem->setPluginRepoName(pluginObj.value("repo_name").toString());
                        if (Plugins::PluginManager::locallyAvailablePluginsModel->find(pluginOnlineItem->id()) != NULL)
                            pluginOnlineItem->setPluginDownloaded(true);
                        this->getOnlineAvailablePlugins()->appendRow(pluginOnlineItem);
                    }
                }
            }
        }
    }
}

/*!
 * Callback triggered when checking if downloaded plugins are up to date.
 */
void Plugins::PluginManager::checkForPluginsUpdatesCallBack(QNetworkReply *reply, void *data)
{
    if (reply != NULL && data != NULL)
    {
        QJsonDocument jsonDoc = Utils::QJsonDocumentFromReply(reply);
        delete reply;

        if (!jsonDoc.isNull() && !jsonDoc.isEmpty() && jsonDoc.isObject())
        {
            QJsonObject pluginObj = jsonDoc.object();
            if (pluginObj.contains("version"))
            {
                QString onlineVersion = pluginObj.value("version").toString();
                Plugins::PluginBase *localInstance = reinterpret_cast<Plugins::PluginBase *>(data);
                qDebug() << "Online version = " << onlineVersion;
                if (onlineVersion.compare(localInstance->getPluginVersion()) != 0)
                {
                    // SEND REQUEST TO DOWNLOAD PLUGIN UPDATE
                    ;
                }
            }
        }
    }
}

/*!
 * Triggered when the download of the index \a file for a plugin is complete.
 * The corresponding model item is transmitted in the \a data parameter.
 * The index file is then read, so that each of the files required by the plugin can be downloaded.
 */

void Plugins::PluginManager::downloadPluginIndexCallBack(QFile *file, void *data, bool error)
{
    if (file != NULL && data != NULL)
    {
        Models::PluginOnlineModelItem *pluginOnlineItem = reinterpret_cast<Models::PluginOnlineModelItem *>(data);
        if (error)
        {
            pluginOnlineItem->setPluginDownloadError(error);
            return ;
        }
        if (pluginOnlineItem->getPluginDownloadError())
        {
            file->close();
            qWarning() << "Error while trying to dowload plugin File file";
            qWarning() << "Removing Plugin Directory";
            QDir pluginDir = QDir(PlatformFactory::getPlatformInitializer()->
                                  getWidgetsResourceDirectory().absoluteFilePath(
                                      pluginOnlineItem->getPluginRepoName()));
            pluginDir.removeRecursively();
            return ;
        }
        qDebug() << "File Index downloaded";
        file->reset();
        pluginOnlineItem->setPluginDownloading(true);
        while (!file->atEnd())
        {
            QString fileName = file->readLine();
            fileName.chop(1);
            QFile *itemFile;
            QDir pluginDir = QDir(PlatformFactory::getPlatformInitializer()->
                                  getWidgetsResourceDirectory().absoluteFilePath(
                                      pluginOnlineItem->getPluginRepoName()));
            qDebug() << pluginDir.absolutePath();
            if (fileName.compare(pluginOnlineItem->getPluginRepoName() + ".sql") == 0) // WE HAVE A DATABASE FILE
                itemFile = new QFile(PlatformFactory::getPlatformInitializer()->
                                     getDatabaseDirectory().absoluteFilePath(fileName));
            else if (fileName.endsWith(".so") || fileName.endsWith(".ddl")) // WE HAVE THE PLUGIN LIBRARY
                itemFile = new QFile(PlatformFactory::getPlatformInitializer()->
                                     getWidgetSharedLibrariesDirectory().absoluteFilePath(fileName));
            else
                itemFile = new QFile(pluginDir.absoluteFilePath(fileName));
            if (itemFile->open(QIODevice::WriteOnly))
            {
                qDebug() << itemFile->fileName();
                pluginOnlineItem->setPluginFileToDownloadCount(pluginOnlineItem->getPluginFileToDownload() + 1);
                emit executeFileDownloader(QNetworkRequest(QUrl(QString(TEPEE3D_WIDGETS_STORE)
                                                                + PlatformFactory::getPlatformInitializer()->getPlatformName()
                                                                + "/"
                                                                + pluginOnlineItem->getPluginRepoName()
                                                                + "/"
                                                                + fileName)),
                                           Services::FileDownloaderServiceUserInterface::Get,
                                           NULL,
                                           itemFile,
                                           this,
                                           DOWNLOAD_PLUGIN_FILE,
                                           pluginOnlineItem);
            }
        }
        qDebug() << "Reading done";
    }
}

/*!
 * Called after a plugin \a file has been downloaded. The \a data parameters which is a plugin online model instance is
 * then updated to reflect the count of downloaded files. If \a error is true, an error occured in the download process and the
 * plugin will be marked as so.
 */
void Plugins::PluginManager::downloadPluginFileCallBack(QFile *file, void *data, bool error)
{
    if (file != NULL && data != NULL)
    {
        Models::PluginOnlineModelItem* pluginOnlineItem = reinterpret_cast<Models::PluginOnlineModelItem *>(data);
        if (error)
        {
            pluginOnlineItem->setPluginDownloadError(error);
            return ;
        }
        pluginOnlineItem->setPluginFileToDownloadCount(pluginOnlineItem->getPluginFileToDownload() - 1);
        qDebug() << pluginOnlineItem->getPluginFileToDownload() << " Files Remaining";
        if (pluginOnlineItem->getPluginFileToDownload() == 0)
        {
            if (pluginOnlineItem->getPluginDownloadError())
            {
                file->close();
                qWarning() << "Error while trying to dowload plugin File file";
                qWarning() << "Removing Plugin Directory";
                QDir pluginDir = QDir(PlatformFactory::getPlatformInitializer()->
                                      getWidgetsResourceDirectory().absoluteFilePath(
                                          pluginOnlineItem->getPluginRepoName()));
                pluginDir.removeRecursively();
                pluginOnlineItem->setPluginDownloaded(false);
                pluginOnlineItem->setPluginDownloading(false);
                return ;
            }
            qDebug() << "Plugin Downloaded, reloading models";
            pluginOnlineItem->setPluginDownloading(false);
            pluginOnlineItem->setPluginDownloaded(true);
            this->loadLocalPlugins();
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

void Plugins::PluginManager::onDownloadFinished(QFile *file, int requestId, void *data)
{
    qDebug() << ">> download Finished";
    (this->*this->streamServicesCallBacks[requestId])(file, data, false);
    file->close();
}

void Plugins::PluginManager::onDownloadProgress(QFile *, int , int , void *)
{
}

void Plugins::PluginManager::onDownloadStarted(QFile *, int , void *)
{
}

void Plugins::PluginManager::onDownloadError(QFile *file, int requestId, void *data)
{
    qDebug() << ">> in onDownloadError";
    (this->*this->streamServicesCallBacks[requestId])(file, data, true);
}

/*!
 * Destroys a PluginManager instance.
 */
Plugins::PluginManager::~PluginManager()
{
    delete this->locallyAvailablePluginsModel;
    delete this->onlineAvailablePluginsModel;
    Plugins::PluginManager::locallyAvailablePluginsModel = NULL;
    Plugins::PluginManager::onlineAvailablePluginsModel = NULL;
    Plugins::PluginManager::instance = NULL;
    Plugins::PluginLoader::unloadPlugins();
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
    if (Plugins::PluginManager::locallyAvailablePluginsModel == NULL)
        Plugins::PluginManager::locallyAvailablePluginsModel = new Models::ListModel(new Models::PluginModelItem(NULL, NULL));
    else
        Plugins::PluginManager::locallyAvailablePluginsModel->clear();
    PluginLoader::loadWidgetPlugins();
    foreach (Plugins::PluginBase*  plugin, PluginLoader::getWidgetPlugins())
    {
        qDebug() << "Adding available plugin item";
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
    if (roomPlugin == NULL)
        return ;
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
    if (roomPlugin == NULL)
        return ;
    roomPlugin->clearPluginBeforeRemoval();
    Services::ServicesManager::disconnectObjectFromServices(roomPlugin);
}

/*!
 * Exposes to QML Context \a context all Plugins entities required by the Tepee3DEngine.
 */
void    Plugins::PluginManager::exposeContentToQml(QQmlContext *context)
{
    context->setContextProperty("availablePluginsModel", this->getLocallyAvailablePlugins());
    context->setContextProperty("onlinePluginsModel", this->getOnlineAvailablePlugins());
    context->setContextProperty("pluginManager", this);
    qmlRegisterType<Plugins::PluginEnums>("Plugins", 1, 0, "PluginEnums");
    qmlRegisterType<Plugins::PluginQmlPluginProperties>("Plugins", 1, 0, "PluginProperties");
}

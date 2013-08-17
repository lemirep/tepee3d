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
    this->webServicesCallBacks[DOWNLOAD_PLUGIN] = &Plugins::PluginManager::downloadPluginFromServerCallback;
    this->webServicesCallBacks[GET_PLUGINS_UPDATES] = &Plugins::PluginManager::checkForPluginsUpdatesCallBack;
    this->loadLocalPlugins();
}


void Plugins::PluginManager::downloadFileFromServer(QString file)
{
    qDebug() << "in DownFILE";
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart httpPart;
    httpPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    httpPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"json\""));

    QJsonObject requestObj;
    QJsonObject commandObj;

    commandObj.insert("command", QJsonValue(QString("downloadFile")));
    commandObj.insert("file", file);
    requestObj.insert("request", QJsonValue(commandObj));

    httpPart.setBody(QJsonDocument(requestObj).toJson());
    multiPart->append(httpPart);
    QFile *test = new QFile("./test");
    test->open(QIODevice::WriteOnly);
    if (test->isOpen())
    {
        qDebug() << "Test file is open";
        emit executeFileDownloader(QNetworkRequest(QUrl("http://tepee3d.dyndns.org:3000")),
                                   FileDownloaderServiceUserInterface::Post,
                                   multiPart,
                                   test,
                                   this,
                                   DOWNLOAD_FILE);

        //        emit executeFileDownloader(QNetworkRequest(QUrl("http://1584.ci")),
        //                                   FileDownloaderServiceUserInterface::Get,
        //                                   NULL,
        //                                   test,
        //                                   this,
        //                                   DOWNLOAD_FILE);
    }
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
    // CREATE A JSON FOR THE REQUEST
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart httpPart;
    httpPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    httpPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"json\""));

    QJsonObject requestObj;
    QJsonObject commandObj;
    QJsonObject pluginObj;
    Models::PluginModelItem *pluginItem = reinterpret_cast<Models::PluginModelItem*>(this->locallyAvailablePluginsModel->find(pluginId));
    Plugins::PluginBase *oldPlugin = NULL;

    if (pluginItem == NULL || (oldPlugin = pluginItem->getPlugin()) == NULL)
        return;
    pluginObj = oldPlugin->toJsonRepresentation();
    pluginObj.remove("description");
    pluginObj.insert("plateform", QJsonValue(PlatformFactory::getPlatformInitializer()->getPlatformName()));

    commandObj.insert("command", QJsonValue(QString("downloadPlugin")));
    commandObj.insert("plugin", QJsonValue(pluginObj));
    requestObj.insert("request", QJsonValue(commandObj));

    httpPart.setBody(QJsonDocument(requestObj).toJson());
    multiPart->append(httpPart);

    // EXECUTE THE REQUEST
    emit executeHttpRequest(QNetworkRequest(QUrl("http://tepee3d.dyndns.org:3000")),
                            WebServiceUserInterface::Post,
                            multiPart,
                            this,
                            DOWNLOAD_PLUGIN);
    // QDataStream *content = new QDataStream();
    //emit executeStreamRequest(QNetworkRequest(QUrl("http://tepee3d.dyndns.org:3000")),
    //                        1,
    //                      content,
    //                    this,
    //                  STREAM_PLUGIN);
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

Models::ListModel *Plugins::PluginManager::getLocallyAvailablePlugins() const
{
    return Plugins::PluginManager::locallyAvailablePluginsModel;
}

Models::ListModel *Plugins::PluginManager::getOnlineAvailablePlugins()
{
    if (Plugins::PluginManager::onlineAvailablePluginsModel == NULL)
        Plugins::PluginManager::onlineAvailablePluginsModel = new Models::ListModel(new Models::PluginOnlineModelItem(-1));
    if (Plugins::PluginManager::onlineAvailablePluginsModel->rowCount() == 0)
        this->retrieveOnlinePluginsForCurrentPlatform();
    return Plugins::PluginManager::onlineAvailablePluginsModel;
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
        if (!jsonDoc.isNull() && !jsonDoc.isEmpty() && jsonDoc.isObject())
        {
            QJsonObject resultObj = jsonDoc.object();
            if (resultObj.contains("objects"))
            {
                QJsonArray pluginsArray = resultObj.value("objects").toArray();
                if (!pluginsArray.isEmpty())
                {
                    Plugins::PluginManager::onlineAvailablePluginsModel->clear();
                    foreach (QJsonValue pluginValue, pluginsArray)
                    {
                        QJsonObject pluginObj = pluginValue.toObject();
                        qDebug() << "asdasd " <<  QJsonDocument(pluginObj).toJson();
                        Models::PluginOnlineModelItem *pluginOnlineItem = new Models::PluginOnlineModelItem(pluginObj.value("widget_id").toDouble());
                        pluginOnlineItem->setPluginName(pluginObj.value("name").toString());
                        pluginOnlineItem->setPluginDescription(pluginObj.value("description").toString());
                        if (Plugins::PluginManager::locallyAvailablePluginsModel != NULL &&
                                Plugins::PluginManager::locallyAvailablePluginsModel->find(pluginOnlineItem->id()) != NULL)
                            pluginOnlineItem->setPluginDownloaded(true);
                        Plugins::PluginManager::onlineAvailablePluginsModel->appendRow(pluginOnlineItem);
                    }
                    // PARSE JSON ARRAY HERE
                    // WAITING FOR THE SERVER TO BE READY TO PURSUE
                    // DO NOT FORGET TO RESDTORE retrieveOnlinePluginsForCurrentPlatform as private
                }
            }
        }
    }
}

/*!
 * Callback that contains the \a reply of the server concerning the request to download a plugin.
 */
void Plugins::PluginManager::downloadPluginFromServerCallback(QNetworkReply *reply, void *data)
{
    if (reply != NULL)
    {
        QJsonDocument jsonDoc = Utils::QJsonDocumentFromReply(reply);
        delete reply;
        qDebug() << ">>>>>Tepee3D Serveur Response <<" << jsonDoc.toJson() << ">>";

        if (!jsonDoc.isNull() && !jsonDoc.isEmpty() && jsonDoc.isObject())
        {
            QJsonObject mainObjet = jsonDoc.object();
            QString re =   mainObjet.value("file").toString();
            QByteArray by = QByteArray::fromBase64(re.toLocal8Bit());
            QFile file(mainObjet.value("libname").toString());
            if(file.open(QIODevice::WriteOnly))
            {
                file.write(by);
                file.close();
            }
            qDebug() << "json valid";

        }
        else
            qDebug() << "json problem";
    }
    else
        qDebug() << "reply NULL";
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
 * Receives results from the webservice worker.
 */
void Plugins::PluginManager::receiveResultFromHttpRequest(QNetworkReply *reply, int requestId, void *data)
{
    (this->*this->webServicesCallBacks[requestId])(reply, data);
}

void Plugins::PluginManager::onDownloadFinished(QFile *file, int requestId, void *data)
{
    qDebug() << ">> download Finished";
    file->close();
}

void Plugins::PluginManager::onDownloadProgress(QFile *, int progress, int requestId, void *data)
{
    qDebug() << ">> download Progress " << progress;
}

void Plugins::PluginManager::onDownloadStarted(QFile *, int requestId, void *data)
{
    qDebug() << ">> download Started";
}

void Plugins::PluginManager::onDownloadError(QFile *, int requestId, void *data)
{
    qDebug() << ">> in onDownloadError";
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
    qmlRegisterType<Plugins::PluginEnums>("Plugins", 1, 0, "PluginEnums");
    qmlRegisterType<Plugins::PluginQmlPluginProperties>("Plugins", 1, 0, "PluginProperties");
}

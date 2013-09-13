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

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QSignalMapper>
#include <QHash>
#include <PluginBase.h>
#include <QmlContentExposerInterface.h>
#include <WebServiceUserInterface.h>
#include <FileDownloaderServiceUserInterface.h>
#include <ListModel.h>
#include <PluginModelItem.h>
#include <PluginOnlineModelItem.h>
#include <ListItem.h>
#include <PluginDownloader.h>
#include <PluginLoader.h>
#include <PluginQmlPluginProperties.h>
#include <QmlViewProperties.h>
#include <ServicesManager.h>


// PLUGINS IN THE LOCAL DIRECTORY ARE ALL LOADED ON STARTUP
// WHEN ADDING A PLUGIN TO ROOM : -> NEW PLUGIN OF A GIVEN INSTANCE IS CREATED
// ADD TO ROOM'S PLUGINS LIST THE NEW INSTANCE
// RETRIEVE ROOM'S QQUICKITEM
// INSERT ITEM IN THE ROOM'S QQUICKITEM

// LATER ROOM POSITIONING MENU TO EASILY SCALE ROTATE AND PLACE QML ITEM


// THE WEB STORE WITH A RESTFUL API WILL PROVIDE INFORMATION ABOUT PLUGINS AVAILABLE
// THEY INFORMATION PROVIDED BY THE STREAM WILL BE USED TO BUILD A MODEL OF PLUGINS

//class View::QmlViewProperties;

#define GET_ONLINE_PLUGINS 0
#define GET_PLUGINS_UPDATES 1
#define STREAM_PLUGIN 3
#define DOWNLOAD_FILE 4
#define TEPEE3D_ONLINE_API "http://tepee3d.dyndns.org/api/v1/"
#define PLUGINS_QML_DIR "plugin_qml"

namespace Plugins
{
class PluginManager : public QObject,
        public View::QmlContentExposerInterface,
        public Services::WebServiceUserInterface
{
    Q_OBJECT
    Q_INTERFACES(View::QmlContentExposerInterface)
    Q_INTERFACES(Services::WebServiceUserInterface)

public:
    ~PluginManager();

    void                        exposeContentToQml(QQmlContext *context);

    static PluginManager*       getInstance(QObject *parent = 0);
    static PluginBase*          getNewInstanceOfPlugin(int pluginModelItemId);
    static PluginBase*          getNewInstanceOfPlugin(PluginBase* plugin);
    static void                 initRoomPlugin(PluginBase* roomPlugin);
    static void                 cleanPluginBeforeRemoval(PluginBase *roomPlugin);

    // WEB SERVICES
    void                        retrieveOnlinePluginsForCurrentPlatform();
    void                        checkForPluginsUpdates();

    Q_INVOKABLE void            downloadPluginFromServer(int pluginId);

    //MODELS
    Models::ListModel*          getLocallyAvailablePlugins() const;
    Models::ListModel*          getOnlineAvailablePlugins() const;

    // UTILITY METHOD
    Q_INVOKABLE void            removeDownloadedPlugin(int pluginId);

public slots:
    void                        loadLocalPlugins();

private:

    explicit PluginManager(QObject *parent = 0);
    static PluginManager*               instance;
    static Models::ListModel*           locallyAvailablePluginsModel;
    static Models::ListModel*           onlineAvailablePluginsModel;

    PluginDownloader* pluginDownloader;

    QHash<int, void (PluginManager::*)(QNetworkReply *,QPointer<QObject>)>    webServicesCallBacks;

    void  receiveResultFromHttpRequest(QNetworkReply *reply, int requestId, QPointer<QObject> data);

    // CALLBACKS
    void retrieveOnlinePluginsForCurrentPlatformCallBack(QNetworkReply *reply, QPointer<QObject> data);
    void checkForPluginsUpdatesCallBack(QNetworkReply *reply, QPointer<QObject> data);

signals :
    void executeHttpRequest(const QNetworkRequest&,
                            Services::WebServiceUserInterface::WebServiceRequestType,
                            QHttpMultiPart*,
                            QPointer<QObject> sender,
                            int requestId,
                            QPointer<QObject> data = QPointer<QObject>());

};
}

#endif // PLUGINMANAGER_H

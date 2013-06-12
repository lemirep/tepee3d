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
#include <ListModel.h>
#include <PluginModelItem.h>
#include <ListItem.h>
#include "PluginLoader.h"
#include "PluginQmlPluginProperties.h"
#include "QmlViewProperties.h"
#include "ServicesManager.h"


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
#define DOWNLOAD_PLUGIN 2

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

    void                        loadLocalPlugins();
    void                        exposeContentToQml(QQmlContext *context);

    static PluginManager*       getInstance(QObject *parent = 0);
    static PluginBase*          getNewInstanceOfPlugin(int pluginModelItemId);
    static PluginBase*          getNewInstanceOfPlugin(PluginBase* plugin);
    static void                 initRoomPlugin(PluginBase* roomPlugin);
    static void                 cleanPluginBeforeRemoval(PluginBase *roomPlugin);

    // WEB SERVICES
    void                        retrieveOnlinePluginsForCurrentPlatform();
    void                        downloadPluginFromServer(int pluginId);
    void                        checkForPluginsUpdates();
private:

    explicit PluginManager(QObject *parent = 0);
    static PluginManager*               instance;
    static Models::ListModel*           locallyAvailablePluginsModel;
    static Models::ListModel*           onlineAvailablePluginsModel;
    QHash<int, void (PluginManager::*)(QNetworkReply *, void *data)>    webServicesCallBacks;

    void                        receiveResultFromHttpRequest(QNetworkReply *reply, int requestId, void *data);
    // CALLBACKS
    void                        retrieveOnlinePluginsForCurrentPlatformCallBack(QNetworkReply *reply, void *data);
    void                        downloadPluginFromServerCallback(QNetworkReply *reply, void *data);
    void                        checkForPluginsUpdatesCallBack(QNetworkReply *reply, void *data);

signals :
    void executeHttpRequest(const QNetworkRequest&, int, QHttpMultiPart*, QObject* sender, int, void *data = NULL);
};
}

#endif // PLUGINMANAGER_H

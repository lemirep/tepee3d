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
#include "PluginQmlPluginProperties.h"
#include "QmlViewProperties.h"
#include "ServicesManager.h"
#include "WebServiceUserInterface.h"


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

private:

    explicit PluginManager(QObject *parent = 0);
    static PluginManager*               instance;
    static Models::ListModel*           locallyAvailablePluginsModel;
    static Models::ListModel*           onlineAvailablePluginsModel;
    QHash<int, void (PluginManager::*)(QNetworkReply *, void *data)>    webServicesCallBacks;

    void                        retrieveOnlinePluginsForCurrentPlatform();
    void                        retrieveOnlinePlugindForCurrentPlatformCallBack(QNetworkReply *reply, void *data);
    void                        receiveResultFromHttpRequest(QNetworkReply *reply, int requestId, void *data);
signals :
    void executeHttpRequest(const QNetworkRequest&, int, QHttpMultiPart*, QObject* sender, int, void *data = NULL);
};
}

#endif // PLUGINMANAGER_H

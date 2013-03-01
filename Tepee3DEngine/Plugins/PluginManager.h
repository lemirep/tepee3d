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
#include "DatabaseServiceUserInterface.h"
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


namespace Plugins
{
class PluginManager : public QObject, public View::QmlContentExposerInterface, public Services::DatabaseServiceUserInterface
{
    Q_OBJECT
public:
    ~PluginManager();

    void                        loadLocalPlugins();
    void                        exposeContentToQml(QQmlContext *context);
    void                        receiveResultFromSQLQuery(QList<QSqlRecord> result, int);

    static PluginManager*       getInstance(QObject *parent = 0);
    static PluginBase*          getNewInstanceOfPlugin(int pluginModelItemId);
    static PluginBase*          getNewInstanceOfPlugin(PluginBase* plugin);
    static void                 initRoomPlugin(PluginBase* roomPlugin);

private:
    static PluginManager*       instance;
    static ListModel*           locallyAvailablePluginsModel;
    static ListModel*           onlineAvailablePluginsModel;
    explicit PluginManager(QObject *parent = 0);

//    QSignalMapper              *signalMapper;
signals :
    void                        executeSQLQuery(const QString &query, QObject *sender, int id);
};
}

#endif // PLUGINMANAGER_H

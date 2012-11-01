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
#include "DatabaseServiceUserInterface.h"

// PLUGINS IN THE LOCAL DIRECTORY ARE ALL LOADED ON STARTUP
// WHEN ADDING A PLUGIN TO ROOM : -> NEW PLUGIN OF A GIVEN INSTANCE IS CREATED
// ADD TO ROOM'S PLUGINS LIST THE NEW INSTANCE
// RETRIEVE ROOM'S QQUICKITEM
// INSERT ITEM IN THE ROOM'S QQUICKITEM

// LATER ROOM POSITIONING MENU TO EASILY SCALE ROTATE AND PLACE QML ITEM


namespace Plugins
{
class PluginManager : public QObject, public QmlContentExposerInterface, public DatabaseServiceUserInterface
{
    Q_OBJECT
public:
    explicit PluginManager(QObject *parent = 0);
    ~PluginManager();

    void                       loadLocalPlugins();
    void                       exposeContentToQml(QQmlContext *context);
    void                       receiveResultFromSQLQuery(const QList<QSqlRecord> &result);

    static PluginBase*         getNewInstanceOfPlugin(int pluginModelItemId);
    static PluginBase*         getNewInstanceOfPlugin(PluginBase* plugin);

private:
    QSignalMapper              *signalMapper;
    static ListModel*           availablePluginsModel;
signals :
    void executeSQLQuery(const QString &query, QObject *sender);
};
}

#endif // PLUGINMANAGER_H

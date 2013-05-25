#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QList>
#include <QCoreApplication>
#include <QPluginLoader>
#include <QQmlExtensionPlugin>
#include <QDir>
#include <DatabaseServiceUserInterface.h>
#include "PluginInterface.h"
#include "PluginBase.h"
#include <PluginManager.h>
#include <RoomBase.h>

#define PLUGIN_LOADED 1
#define DB_NAME "Tepee3D.sql"

namespace Plugins
{

class PluginLoader :  public QObject
{
    Q_OBJECT

private :
    PluginLoader(QObject *parent = 0); // PRIVATE SO THAT IT CANNOT  BE CALLED
    static QList<PluginBase *>      widgetPlugins; //LIST CONTAINING ALL THE PLUGINS
    static      PluginLoader*       instance;
public :
    ~PluginLoader();
    static void                     loadWidgetPlugins(); //TRIES TO LOAD EVERY PLUGIN IN DIR AND RETURN FALSE IF ERROR OCCURS
    static QList<PluginBase *>      getWidgetPlugins(); // RETURN LIST CONTAINING ALL THE LOADED PLUGINS
    static PluginLoader*            getInstance(QObject *parent = 0);
    static void                     addPluginToRoom(Plugins::PluginBase *plugin, Room::RoomBase *room);
    static QString                  loadAllPluginForRoom(Room::RoomBase *room);
    static QString                  addOrReplacePluginImpl(Plugins::PluginBase *plugin, Room::RoomBase *room);
    static QString                  removeAllPluginsFromRoom(Room::RoomBase *room);
signals :

};

}
#endif // PLUGINLOADER_H

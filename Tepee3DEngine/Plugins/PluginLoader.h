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

#define WIDGET_PLUGIN_DIRECTORY "libraries/widget_libraries"

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
    static QString                  loadAllPluginForRoom(Room::RoomBase *room);
    static QString                  addPluginImpl(PluginBase *plugin, Room::RoomBase *room, int idUser, const QVector3D &scale, const QVector3D &pos);
    static QString                  addNewPlugin(PluginBase *plugin);
    static QString                  loadAllPluginForUser(int idUser);
signals :

};

}
#endif // PLUGINLOADER_H

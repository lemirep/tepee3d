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

class PluginLoader :  public QObject, public Services::DatabaseServiceUserInterface
{
    Q_OBJECT
    Q_INTERFACES(Services::DatabaseServiceUserInterface)

    QHash<int, void (PluginLoader::*)(QList<QSqlRecord> result)>   pFunc;
    private :
      PluginLoader(QObject *parent = 0); // PRIVATE SO THAT IT CANNOT  BE CALLED
      static QList<PluginBase *>     widgetPlugins; //LIST CONTAINING ALL THE PLUGINS

       static      PluginLoader*     instance;
    public :
      ~PluginLoader();
      static void                loadWidgetPlugins(); //TRIES TO LOAD EVERY PLUGIN IN DIR AND RETURN FALSE IF ERROR OCCURS
      static QList<PluginBase *> getWidgetPlugins(); // RETURN LIST CONTAINING ALL THE LOADED PLUGINS

      void                       genericResultCallback(QList<QSqlRecord> result);
      void                       loadPluginsCallback(QList<QSqlRecord> result);
    public :
          static PluginLoader*   getInstance(QObject *parent = 0);

          void                   loadAllPluginForRoom(Room::RoomBase &room);
          void                   loadAllPluginForUser(int &idUser); // Change int by user class later
          void                   addPluginImpl(PluginBase &plugin, Room::RoomBase &room, int &idUser, QVector3D &scale, QVector3D &pos);
          void                   addNewPlugin(PluginBase &plugin);

          void                   receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, void *data);
    signals :
      void                       executeSQLQuery(const QString &query, QObject *sender, int id, const QString &dbName, void *data);

};

}
#endif // PLUGINLOADER_H

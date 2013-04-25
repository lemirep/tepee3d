#ifndef ROOMLOADER_H
#define ROOMLOADER_H



#include <QHash>
#include <RoomBase.h>
#include <RoomManager.h>
#include <QTextStream>
#include <DatabaseServiceUserInterface.h>


#define FILEHEADER  "__ROOMFILE__"
#define ROOMFILEDIR "./RoomFile/"

#define SEARCH_FOR_ROOM 1
#define GENERIC_RESULT 2
#define RESTORE_ROOMS 3
#define RESTORE_PLUGINS_TO_ROOM 4
#define DB_NAME "Tepee3D.sql"

 namespace Room
 {
    class RoomManager;

    class RoomLoader : public QObject, public Services::DatabaseServiceUserInterface
    {
        Q_OBJECT
        Q_INTERFACES(Services::DatabaseServiceUserInterface)

    private:
        RoomLoader(QObject *parent = 0);


        static      RoomLoader*     instance;

        void                        updateExistingRoom(RoomBase *room);
        void                        insertNewRoom(RoomBase *room);
        void                        insertOrReplacePluginsForRoom(RoomBase *room);
        void                        deleteRoom(RoomBase *room);
        void                        saveRoom(RoomBase *room);
        void                        restoreRooms();

        void                        searchForRoomEditUpdateCallback(QList<QSqlRecord> result, void *data);
        void                        restoreRoomsCallback(QList<QSqlRecord> result, void *data);
        void                        genericResultCallback(QList<QSqlRecord> result, void *data);
        void                        restoreWidgetsForRoomCallback(QList<QSqlRecord> result, void *data);

        QHash<int, void (RoomLoader::*)(QList<QSqlRecord> result, void *data)>   pFunc;

    public :
        static RoomLoader*          getInstance(QObject *parent = 0);
        ~RoomLoader();

         static void                saveRoomToDatabase(Room::RoomBase *room);
         static void                deleteRoomFromDatabase(Room::RoomBase *room);
         static void                restoreRoomsFromDatabase();
         static void                addNewPluginToDatabase(Plugins::PluginBase *plugin);

         void                       receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, void *data);

    signals :
         void                       executeSQLQuery(const QString &query, QObject *sender, int id, const QString &dbName, void *data = NULL);
    };
 }

#endif // ROOMLOADER_H

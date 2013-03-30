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
#define DB_NAME "Tepee3D.sql"

 namespace Room
 {
    class RoomManager;

    class RoomLoader : public QObject, public Services::DatabaseServiceUserInterface
    {
        Q_OBJECT

    private:
        RoomLoader(QObject *parent = 0);


        static      RoomLoader*     instance;

        static void                 addParamToRoom(Room::RoomBase *room, QString attr, QString value);
        static void                 addParamToRoom(Room::RoomBase *room, int id, QString value);
        static bool                 parseLine(std::string line, bool &header, Room::RoomBase *newroom);

        void                        updateExistingRoom(RoomBase *room);
        void                        insertNewRoom(RoomBase *room);
        void                        deleteRoom(RoomBase *room);
        void                        saveRoom(RoomBase *room);
        void                        restoreRooms();

        void                        searchForRoomEditUpdateCallback(QList<QSqlRecord> result);
        void                        restoreRoomsCallback(QList<QSqlRecord> result);
        void                        genericResultCallback(QList<QSqlRecord> result);

        RoomBase*                   roomToSave;
        QHash<int, void (RoomLoader::*)(QList<QSqlRecord> result)>   pFunc;

    public :
        static RoomLoader*          getInstance(QObject *parent = 0);
        ~RoomLoader();

//         static bool                loadRoomFromFile(QString name);
         static bool                saveRoomFile(Room::RoomBase *room);

         static void                saveRoomToDatabase(Room::RoomBase *room);
         static void                deleteRoomFromDatabase(Room::RoomBase *room);
         static void                restoreRoomsFromDatabase();

         void                       receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, void *data);

    signals :
         void                       executeSQLQuery(const QString &query, QObject *sender, int id, const QString &dbName, void *data);
    };
 }

#endif // ROOMLOADER_H

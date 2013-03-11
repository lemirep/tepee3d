#ifndef ROOMLOADER_H
#define ROOMLOADER_H

#include <iostream>
#include <RoomManager.h>

#define ROOMFILEDIR "./RoomFile/"



 namespace Room
 {
    class RoomLoader
    {
        private:
        static void addParamToRoom(Room::RoomBase *room, QString attr, QString value);
        static void addParamToRoom(Room::RoomBase *room, int id, QString value);
        static bool parseLine(std::string line, bool &header, Room::RoomBase *newroom);
        static bool onLoadingRequestFinished(Room::RoomManager *roommanager, QList<QSqlRecord> result);
        static bool onSearchingRequestFinished(Room::RoomManager *roommanger, QList<QSqlRecord> result);

        public:
         static int                 lastCalled;
         static Room::RoomBase      *roomDataSave;

         static bool loadRoomFromFile(QString name, Room::RoomManager *roommanager);
         static void loadRoomFromDatabase(QString name, Room::RoomManager *roommanager);
         static bool saveRoomFile(Room::RoomBase *room);
         static void saveRoomDatabase(Room::RoomBase *room, Room::RoomManager *roommanager);
         static bool onRequestFinished(Room::RoomManager *roommanger, QList<QSqlRecord> result);
    };
 }

#endif // ROOMLOADER_H

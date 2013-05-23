#include "RoomLoader.h"

/*!
 * \class Room::RoomLoader
 * \brief The RoomLoader class is a group a static functions aimed
 * to load or save room in databases and files format.
 *
 * \inmodule Tepee3D
 */

Room::RoomLoader*   Room::RoomLoader::instance = NULL;

Room::RoomLoader::RoomLoader(QObject *parent) : QObject(parent)
{
    // CONNECT TO DATABASE SERVICE
    Services::ServicesManager::connectObjectToServices(this);
    // DATABASE CALLBACKS
    this->pFunc[SEARCH_FOR_ROOM] = &Room::RoomLoader::searchForRoomEditUpdateCallback;
    this->pFunc[GENERIC_RESULT] = &Room::RoomLoader::genericResultCallback;
    this->pFunc[RESTORE_ROOMS] = &Room::RoomLoader::restoreRoomsCallback;
    this->pFunc[RESTORE_PLUGINS_TO_ROOM] = &Room::RoomLoader::restoreWidgetsForRoomCallback;
}

Room::RoomLoader::~RoomLoader()
{
    Services::ServicesManager::disconnectObjectFromServices(this);
}

Room::RoomLoader*   Room::RoomLoader::getInstance(QObject *parent)
{
    if (Room::RoomLoader::instance == NULL)
        Room::RoomLoader::instance = new Room::RoomLoader(parent);
    return Room::RoomLoader::instance;
}

////////////////// STATIC METHODS CALLBED BY ROOM MANAGER ///////////////////

/*!
 * \brief RoomLoader::saveRoomDatabase Save a room to the database, the room is updated or inserted depending if the room was already present.
 * The requests are asynchronous and this function only sends the request. Does not return.
 */
void    Room::RoomLoader::saveRoomToDatabase(Room::RoomBase *room)
{
    Room::RoomLoader::getInstance()->saveRoom(room);
}

void    Room::RoomLoader::deleteRoomFromDatabase(Room::RoomBase *room)
{
    Room::RoomLoader::getInstance()->deleteRoom(room);
}

void    Room::RoomLoader::restoreRoomsFromDatabase()
{
    Room::RoomLoader::getInstance()->restoreRooms();
}

//////////////// CALLBACKS /////////////////////

void    Room::RoomLoader::receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, void *data)
{
    (this->*this->pFunc[id])(result, data);
}

void    Room::RoomLoader::genericResultCallback(QList<QSqlRecord> result, void *data)
{
    Q_UNUSED(result)
    Q_UNUSED(data)
}

void Room::RoomLoader::restoreWidgetsForRoomCallback(QList<QSqlRecord> result, void *data)
{
    if (result.size() > 1 && data != NULL)
    {
        Room::RoomBase *room = reinterpret_cast<Room::RoomBase*>(data);
        result.pop_front();
        foreach (QSqlRecord record, result)
        {
            qDebug() << "************************RESTORING WIDGET*****************************";
            Plugins::PluginBase *plugin = Plugins::PluginManager::getNewInstanceOfPlugin(record.value(0).toDouble());
            if (plugin != NULL)
            {
                plugin->setPluginPosition(QVector3D(record.value(1).toDouble(),
                                                    record.value(2).toDouble(),
                                                    record.value(3).toDouble()));
                Plugins::PluginLoader::addPluginToRoom(plugin, room);
            }
        }
    }
}

void    Room::RoomLoader::searchForRoomEditUpdateCallback(QList<QSqlRecord> result, void *data)
{
    if (result.size() > 2)
        this->updateExistingRoom(reinterpret_cast<Room::RoomBase*>(data));
    else
        this->insertNewRoom(reinterpret_cast<Room::RoomBase*>(data));
}

void    Room::RoomLoader::restoreRoomsCallback(QList<QSqlRecord> result, void *data)
{
    Q_UNUSED(data)
    if (result.size() > 1) // FIRST RECORD IS STATUS COUNT OF RECORDINGS
    {
        result.pop_front();
        foreach (QSqlRecord record, result)
        {
            Room::RoomBase *newroom = Room::RoomManager::getNewRoomInstance();
            newroom->setRoomQmlFile(record.value(2).toString());
            newroom->setRoomName(record.value(1).toString());
            newroom->setPosition(QVector3D(record.value(3).toDouble(),
                                           record.value(4).toDouble(),
                                           record.value(5).toDouble()));
            newroom->setScale(QVector3D(record.value(6).toDouble(),
                                        record.value(7).toDouble(),
                                        record.value(8).toDouble()));
            qDebug() << "NEW ROOM : " << newroom->getRoomName() << " " << newroom->getPosition() << " " << newroom->getScale();
            Room::RoomManager::addRoomToModel(newroom);
            // ADD ALL PLUGINS OF THE ROOM
            emit executeSQLQuery(Plugins::PluginLoader::loadAllPluginForRoom(newroom),
                                 this, RESTORE_PLUGINS_TO_ROOM, DB_NAME, (void *)newroom);
        }
    }
}

/////////////// QUERIES ///////////////////////

void    Room::RoomLoader::saveRoom(Room::RoomBase *room)
{
    QString request = QString("SELECT * FROM room WHERE name= '%1';")
            .arg(Utils::escapeSqlQuery(room->getRoomName()));
    emit executeSQLQuery(request, this, SEARCH_FOR_ROOM, DB_NAME, (void *)room);
}

void    Room::RoomLoader::updateExistingRoom(Room::RoomBase *room)
{
    if (room == NULL)
        return;
    QString request = QString("UPDATE room SET name = '%1', modelFile = '%2', "
                              "posX = %3, posY = %4, posZ = %5,"
                              "scaleX = %6, scaleY = %7, scaleZ = %8 "
                              "WHERE name = '%9';")
            .arg(Utils::escapeSqlQuery(room->getRoomName()),
                 room->getRoomQmlFile(),
                 QString::number(room->getPosition().x()),
                 QString::number(room->getPosition().y()),
                 QString::number(room->getPosition().z()),
                 QString::number(room->getScale().x()),
                 QString::number(room->getScale().y()),
                 QString::number(room->getScale().z()),
                 Utils::escapeSqlQuery(room->getRoomName()));
    emit executeSQLQuery(request, this, GENERIC_RESULT, DB_NAME);
    this->insertOrReplacePluginsForRoom(room);
}

void    Room::RoomLoader::insertNewRoom(Room::RoomBase *room)
{
    if (room == NULL)
        return;
    QString request = QString("INSERT OR REPLACE INTO room "
                              "(name, modelFile, posX, posY, posZ, scaleX, scaleY, scaleZ) "
                              "VALUES ('%1', '%2', %3, %4, %5, %6, %7, %8);")
            .arg(Utils::escapeSqlQuery(room->getRoomName()),
                 Utils::escapeSqlQuery(room->getRoomQmlFile()),
                 QString::number(room->getPosition().x()),
                 QString::number(room->getPosition().y()),
                 QString::number(room->getPosition().z()),
                 QString::number(room->getScale().x()),
                 QString::number(room->getScale().y()),
                 QString::number(room->getScale().z()));
    emit executeSQLQuery(request, this, GENERIC_RESULT, DB_NAME);
    this->insertOrReplacePluginsForRoom(room);
}

void Room::RoomLoader::insertOrReplacePluginsForRoom(Room::RoomBase *room)
{
    emit executeSQLQuery(Plugins::PluginLoader::removeAllPluginsFromRoom(room),
                         this, GENERIC_RESULT, DB_NAME);
    foreach (Models::ListItem *pluginItem, room->getRoomPluginsModel()->toList())
    {
        Plugins::PluginBase *plugin = NULL;
        if ((plugin = reinterpret_cast<Models::PluginModelItem *>
             (pluginItem)->getPlugin()) != NULL)
            emit executeSQLQuery(Plugins::PluginLoader::addOrReplacePluginImpl(
                                     plugin, room), this, GENERIC_RESULT, DB_NAME);
    }
}

void    Room::RoomLoader::restoreRooms()
{
    emit executeSQLQuery("SELECT * FROM room;", this, RESTORE_ROOMS, DB_NAME, NULL);
}

void    Room::RoomLoader::deleteRoom(Room::RoomBase *room)
{
    QString request = QString("DELETE FROM room WHERE name = '%1';")
            .arg(Utils::escapeSqlQuery(room->getRoomName()));
    emit executeSQLQuery(request, this, GENERIC_RESULT, DB_NAME, NULL);
}

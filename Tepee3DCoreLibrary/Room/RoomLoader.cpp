/****************************************************************************
**
** Copyright (C) Paul Lemire, Tepee3DTeam and/or its subsidiary(-ies).
** Contact: paul.lemire@epitech.eu
** Contact: tepee3d_2014@labeip.epitech.eu
**
** This file is part of the Tepee3D project
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
****************************************************************************/

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
    this->pFunc[RESTORE_SKYBOX] = &Room::RoomLoader::restoreSkyboxPathCallBack;
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

void Room::RoomLoader::restoreSkyboxPathFromDatabase()
{
    Room::RoomLoader::getInstance()->restoreSkyboxPath();
}

void Room::RoomLoader::updateSkyboxPathToDatabase(const QString &skyboxPath)
{
    Room::RoomLoader::getInstance()->saveSkyboxPath(skyboxPath);
}

//////////////// CALLBACKS /////////////////////

void    Room::RoomLoader::receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, QPointer<QObject> data)
{
    (this->*this->pFunc[id])(result, data);
}

void    Room::RoomLoader::genericResultCallback(QList<QSqlRecord> result, QPointer<QObject> data)
{
    Q_UNUSED(result)
    Q_UNUSED(data)
}

void Room::RoomLoader::restoreWidgetsForRoomCallback(QList<QSqlRecord> result, QPointer<QObject> data)
{
    if (result.size() > 1 && !data.isNull())
    {
        Room::RoomBase *room = reinterpret_cast<Room::RoomBase*>(data.data());
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

void Room::RoomLoader::restoreSkyboxPathCallBack(QList<QSqlRecord> result, QPointer<QObject> data)
{
    if (result.size() > 1)
    {
        result.pop_front();
        QSqlRecord record = result.first();
        Room::RoomManager::getInstance()->setSkyboxPath(record.value(0).toString());
    }
}

void    Room::RoomLoader::searchForRoomEditUpdateCallback(QList<QSqlRecord> result,QPointer<QObject> data)
{
    if (data.isNull())
        return ;
    if (result.size() > 2)
        this->updateExistingRoom(reinterpret_cast<Room::RoomBase*>(data.data()));
    else
        this->insertNewRoom(reinterpret_cast<Room::RoomBase*>(data.data()));
}

void    Room::RoomLoader::restoreRoomsCallback(QList<QSqlRecord> result, QPointer<QObject> data)
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
//            newroom->setScale(QVector3D(60, 50, 60));
            qDebug() << "NEW ROOM : " << newroom->getRoomName() << " " << newroom->getPosition() << " " << newroom->getScale();
            Room::RoomManager::addRoomToModel(newroom);
            // ADD ALL PLUGINS OF THE ROOM
            emit executeSQLQuery(Plugins::PluginLoader::loadAllPluginForRoom(newroom),
                                 this, RESTORE_PLUGINS_TO_ROOM, DB_NAME, QPointer<QObject>(newroom));
        }
    }
}

/////////////// QUERIES ///////////////////////

void    Room::RoomLoader::saveRoom(Room::RoomBase *room)
{
    QString request = QString("SELECT * FROM room WHERE name= '%1';")
            .arg(Utils::escapeSqlQuery(room->getRoomName()));
    emit executeSQLQuery(request, this, SEARCH_FOR_ROOM, DB_NAME, QPointer<QObject>(room));
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

void Room::RoomLoader::restoreSkyboxPath()
{
    emit executeSQLQuery("SELECT skybox_path FROM skybox_properties WHERE id=0;", this, RESTORE_SKYBOX, DB_NAME, NULL);
}

void Room::RoomLoader::saveSkyboxPath(const QString &skyboxPath)
{
    QString query = QString("INSERT OR REPLACE INTO skybox_properties (id, skybox_path) VALUES (%1, '%2');")
            .arg(QString::number(0),
                 skyboxPath);
    emit executeSQLQuery(query, this, GENERIC_RESULT, DB_NAME);
}

void    Room::RoomLoader::deleteRoom(Room::RoomBase *room)
{
    QString request = QString("DELETE FROM room WHERE name = '%1';")
            .arg(Utils::escapeSqlQuery(room->getRoomName()));
    emit executeSQLQuery(request, this, GENERIC_RESULT, DB_NAME, NULL);
}

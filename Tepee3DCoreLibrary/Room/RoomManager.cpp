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

#include "RoomManager.h"
// DEBUG
#include <QDebug>

/*!
 * \namespace Room
 *
 * \brief The Room namespace holds all the classes that deal with
 * Rooms and their management.
 *
 * \inmodule Tepee3D
 */

/*!
 * \class Room::RoomInterface
 * \code
 * #include <RoomInterface.h>
 * \endcode
 *
 * \brief Has to be implemented by Room::RoomBase instances in order to ensure
 * they are proper room libraries.
 *
 * \inmodule Tepee3D
 */

/*!
 * \fn Room::RoomBase*   Room::RoomInterface::getRoomBase()
 *
 * Returns a new Room::RoomBase instance.
 */


/*!
 * \class Room::RoomManager
 *
 * \code
 * #include <RoomManager.h>
 * \endcode
 *
 * \brief The Room::RoomManager class is responsible for managing all the
 * rooms ofthe Tepee3D application. It restores the rooms and their plugins
 * on startup, creates the model for the room selector menu, places rooms in
 * space. In addition, this is where new plugins are added to a room.
 *
 * \sa Room::RoomBase
 *
 * \inmodule Tepee3D
 */

Room::RoomManager* Room::RoomManager::instance = NULL;
int                Room::RoomManager::roomInstances = 0;

// ASSIGN A UNIQUE ID FOR EACH PLUGIN TYPE (Ex TestPlugin = 1)
// THAT WAY WHEN RELOADING FROM THE DATABASE WE KNOW WE HAVE LOADED THE RIGHT PLUGIN
\
/*!
 * Constructs a new RoomManager instance. \a parent is optional.
 */

Room::RoomManager::RoomManager(QObject *parent) : QObject(parent)
{
    this->currentRoom = NULL;
    this->roomPrototype = NULL;
    this->roomUpdateTimer = new QTimer();
    this->roomModel = new Models::SubListedListModel(new Models::RoomModelItem(NULL, NULL));
    this->loadRoomLibrary();
}

/*!
 * Returns the singleton instance of the class, needs a QObject \a parent in paremeter.
 */
Room::RoomManager* Room::RoomManager::getInstance(QObject *parent)
{
    if (Room::RoomManager::instance == NULL)
        Room::RoomManager::instance = new Room::RoomManager(parent);
    return Room::RoomManager::instance;
}

/*!
 * Returns a new Room::RoomBase instance base on the roomPrototype instance.
 */
Room::RoomBase* Room::RoomManager::getNewRoomInstance()
{
    return Room::RoomManager::getInstance()->roomPrototype->createNewInstance();
}

/*!
 * Restores Room that were saved in the Database.
 */
void Room::RoomManager::restoreRooms()
{
    qDebug() << "RoomManager::Restoring Rooms";
    Room::RoomLoader::restoreRoomsFromDatabase();
}

/*!
 * Destroys the RoomManager instance.
 */
Room::RoomManager::~RoomManager()
{
    delete this->roomModel;
}

/*!
 * Exposes to the QML context \a context the various entities needed by the class.
 */
void    Room::RoomManager::exposeContentToQml(QQmlContext *context)
{
    context->setContextProperty("roomModel", this->roomModel);
    context->setContextProperty("roomManager", this);
}

/*!
 * Returns the model containing the rooms.
 */
Models::ListModel*  Room::RoomManager::getRoomModel() const
{
    return this->roomModel;
}

/*!
 * Returns the instance of the currently selected room.
 */
Room::RoomBase*  Room::RoomManager::getCurrentRoom()   const
{
    return this->currentRoom;
}


/*!
 * Returns the plugin identified by \a pluginId from the room identified by \a roomId.
 */
Plugins::PluginBase*    Room::RoomManager::getPluginFromRoom(int roomId, int pluginId) const
{
    Models::RoomModelItem *roomItem = NULL;
    Room::RoomBase *room = NULL;

    if ((roomItem = (Models::RoomModelItem*)this->getRoomModel()->find(roomId)) != NULL
            && (room = roomItem->getRoom()) != NULL)
        return room->getPluginFromRoom(pluginId);
    return NULL;
}

/*!
 * Places Rooms in space in a circular manner. The radius of the produced circle
 * is computed according to the largest room. Every time a new Room is added or its size
 * modified, this method is called.
 */

void        Room::RoomManager::placeNewRoomInSpace()
{
    int     idx = 0;
    qreal   posAngle = (2 * M_PI / this->roomModel->rowCount());
    qreal   radius = 100 * ((this->roomModel->rowCount() / 10) + 1);
    const QList<Models::ListItem*> roomItemList = this->roomModel->toList();

    foreach (Models::ListItem *item, roomItemList)
    {
        qreal roomPosAngle = posAngle * idx++;
        Room::RoomBase* room = reinterpret_cast<Models::RoomModelItem *>(item)->getRoom();
        room->setPosition(QVector3D(qCos(roomPosAngle) * radius,
                                    qCos(M_PI * idx) * 10,
                                    qSin(roomPosAngle) * radius));
        // UPDATE ITEM IN MODEL TO REFLECT CHANGES
        item->triggerItemUpdate();
    }
    qDebug() << "Placing room in space";
}

/*!
 * Sets \a room as the currently selected room. It triggers its refresh method by connecting
 * the update timer timeout signal to the room.
 */

void        Room::RoomManager::setCurrentRoom(Room::RoomBase *room)
{
    if (room == this->currentRoom)
        return ;
    this->roomUpdateTimer->stop();
    if (this->currentRoom != NULL)
    {
        QObject::disconnect(this->roomUpdateTimer, SIGNAL(timeout()), this->currentRoom, SLOT(updateRoom()));
        this->currentRoom->leaveRoom();
        // WHEN CHANGING ROOM WE MAKE SUR ALL PLUGIN GO BACK TO IDLE
        this->unsetFocusPluginsFromRoom();
    }
    this->currentRoom = room;
    if (this->currentRoom != NULL)
    {
        this->currentRoom->enterRoom();
        QObject::connect(this->roomUpdateTimer, SIGNAL(timeout()), this->currentRoom, SLOT(updateRoom()));
        this->roomUpdateTimer->start(ROOM_UPDATE_TIME);
    }
}

/*!
 * Sets the room specified by \a roomId as the current room
 *
 * \sa setCurrentRoom(Room::RoomBase *room)
 */
void        Room::RoomManager::setCurrentRoom(int roomId)
{
    Models::RoomModelItem *roomItem = NULL;
    Room::RoomBase *room = NULL;
    if ((roomItem = (Models::RoomModelItem *)this->roomModel->find(roomId)))
        room = roomItem->getRoom();
    // IN ANY CASE WE SET IT SO THAT WE STOP UPDATING IF ROOM IS NULL
    this->setCurrentRoom(room);
}

/*!
 * Adds a new room with the name specified by \a roomName inside the 3D space
 */
void        Room::RoomManager::addNewRoom(QString roomName)
{
    qDebug() << "Adding New Room";

    Room::RoomBase *room = this->roomPrototype->createNewInstance();
    room->setRoomName(roomName + QString::number(Room::RoomManager::roomInstances++));
    room->setParent(NULL);
    room->setPosition(QVector3D(0, 0, 0));
    room->setScale(QVector3D(30, 20, 30));

    qDebug() << room->getRoomName();

    this->roomModel->appendRow(new Models::RoomModelItem(room));
    this->placeNewRoomInSpace();

    //SAVE ROOM IN DATABASE
    Room::RoomLoader::saveRoomToDatabase(room);

    // ADD DEFAULT EMPTY ROOM IN THE MODEL
    // ROOM IS CREATED AT A COMPUTED LOCATION WHERE IT DOESN'T CONFLICT WITH ANY OTHER ROOM AND HAS A DEFAULT SIZE (1) AND IS SQUARED
    // WHEN ITS ATTRIBUTES ARE MODIFIED, VIRTUAL LOCATION IS AUTOMATICALLY ADJUSTED IF NECESSARY
}

/*!
 * Removes the room specified by \a roomModelId from the Tepee3D engine.
 */
void        Room::RoomManager::deleteRoom(int roomModelId)
{
    if (this->currentRoom != NULL && this->currentRoom->getRoomId() == roomModelId)
        this->setCurrentRoom((Room::RoomBase *)NULL);

    Models::RoomModelItem* roomItem = (Models::RoomModelItem *)(this->roomModel->find(roomModelId));
    Room::RoomBase* deletedRoom = (roomItem != NULL) ? roomItem->getRoom() : NULL;
    this->roomModel->removeRow(this->roomModel->getRowFromItem(roomItem), QModelIndex());
    if (deletedRoom != NULL)
    {
        Room::RoomManager::roomInstances--;
        // CLEAR ALL THE ROOM'S CONTENT BEFORE DELETING IT

        // REMOVE ROOM FROM DATABSE
        Room::RoomLoader::deleteRoomFromDatabase(deletedRoom);
        delete deletedRoom;
        // REPLACE ALL THE ROOMS IF NECESSARY
        placeNewRoomInSpace();
    }
}

/*!
 * Edits the room identified by \a roomModelId with the name \a roomName, the position \a roomPosition and the scale \a roomScale.
 */
void        Room::RoomManager::editRoom(int roomModelId, QString roomName, QVector3D roomPosition, QVector3D roomScale)
{
    // UPDATES ROOM LOGICALLY -> UPDATE HAS ALREADY BEEN APPLIED TO QML ROOM
    Models::RoomModelItem* roomItem = (Models::RoomModelItem *)(this->roomModel->find(roomModelId));
    Room::RoomBase* editedRoom = (roomItem != NULL) ? roomItem->getRoom() : NULL;

    if (editedRoom != NULL)
    {
        editedRoom->setRoomName(roomName);
        editedRoom->setPosition(roomPosition);
        editedRoom->setScale(roomScale);
        // UPDATE ROOM ITEM IN MODEL FOR QML UPDATE
        roomItem->triggerItemUpdate();
        Room::RoomLoader::saveRoomToDatabase(editedRoom);
    }
}

/*!
 * Finds the plugin in the current room identified by \a pluginId.
 * If the plugin is found, a request is made to the room in which it lives
 * to have the focusState of the plugin changed fot the corresponding \a focusState.
 */
void Room::RoomManager::askFocusStateForPlugin(int pluginId, int focusState)
{
    if (this->currentRoom == NULL)
        return ;
    Models::PluginModelItem *pluginItem = reinterpret_cast<Models::PluginModelItem *>(this->currentRoom->getRoomPluginsModel()->find(pluginId));
    Plugins::PluginBase *pluginInstance = NULL;
    if (pluginItem != NULL && (pluginInstance = pluginItem->getPlugin()) != NULL)
    {
        pluginInstance->askForFocusState(Plugins::PluginEnums::valueOf(focusState));
    }
}

/*!
 * Sets the focus state of all plugins of the current room to idle, used when a change of view occurs and the plugins
 * should'nt keep the focus
 */
void        Room::RoomManager::unsetFocusPluginsFromRoom()
{
    if (this->currentRoom == NULL)
        return ;

    QList<Models::ListItem*> roomPlugins = this->currentRoom->getRoomPluginsModel()->toList();

    foreach (Models::ListItem *pluginItem, roomPlugins)
    {
        Plugins::PluginBase* plugin = ((Models::PluginModelItem *)(pluginItem))->getPlugin();
        plugin->setFocusState(Plugins::PluginEnums::pluginIdleState);
    }
}

/*!
 * Adds a new plugin instance to the current room´s model. The plugin instance is a new clean
 * instance of the plugin defined by \a pluginModelId ensuring it behaves only in the room´s
 * scope.
 */
void        Room::RoomManager::addNewPluginToCurrentRoom(int pluginModelId)
{
    if (this->currentRoom == NULL)
    {
        qWarning() << "Current Room is Null";
        return ;
    }
    // IF PLUGIN ALLREADY IN THE ROOM
    if (this->currentRoom->getPluginFromRoom(pluginModelId) != NULL)
        return;

    Plugins::PluginBase*    newPlugin = Plugins::PluginManager::getNewInstanceOfPlugin(pluginModelId);
    if (newPlugin != NULL)
    {
        // INITIALIZE PLUGIN SERVICES ...
        Plugins::PluginLoader::addPluginToRoom(newPlugin, this->currentRoom);
        qDebug() << "<<<<<<<<<<<<<<<<<SAVING WIDGET IN ROOM>>>>>>>>>>>>>>>>>>>>>>>";
        Room::RoomLoader::saveRoomToDatabase(this->currentRoom);
    }
    else
        qWarning() << "plugin Instance is NULL, cannot be added to room";
}

/*!
 * Removes the plugin specified by \a pluginModelId from the current room.
 */
void        Room::RoomManager::removePluginFromCurrentRoom(int pluginModelId)
{
    Models::PluginModelItem* pluginItem = (Models::PluginModelItem*)this->currentRoom->getRoomPluginsModel()->find(pluginModelId);

    if (pluginItem != NULL)
    {
        Plugins::PluginManager::cleanPluginBeforeRemoval(pluginItem->getPlugin());
        this->currentRoom->removeWidgetFromRoom(pluginItem);
        Room::RoomLoader::saveRoomToDatabase(this->currentRoom);
    }
}

/*!
 * This method loads the room library to be used as the room logic for room management.
 * Using a library allow for future enhancement and eventual changes in shape without having
 * to change the logic employed. The library is loaded from a path relative to the application path.
 */
void        Room::RoomManager::loadRoomLibrary()
{
    QDir    roomDirectory = PlatformFactory::getPlatformInitializer()->getRoomSharedLibraryDirectory();

    qDebug() << "ROOM DIR " << roomDirectory.absolutePath();

    // LOAD ROOM LIBRARY
    foreach (const QString &filename, roomDirectory.entryList(QDir::Files))
    {
        qDebug() << roomDirectory.absoluteFilePath(filename);
        QPluginLoader loader(roomDirectory.absoluteFilePath(filename));
        RoomInterface* roomInt = qobject_cast<RoomInterface *>(loader.instance());
        if (roomInt)
        {
            this->roomPrototype = roomInt->getRoomBase();
            qDebug() << "ROOM LIBRARY INITIALIZED";
            break;
        }
        else
        {
            qWarning() << "FAILED TO LOAD ROOM LIBRARY" << loader.errorString();
            loader.unload();
        }
    }
}

/*!
 * Adds \a room the the room model. Rooms can then be restored from the database and
 * added on startup right here.
 */

void        Room::RoomManager::addRoomToModel(Room::RoomBase *room)
{
    // ROOMS ARE RESTORED FROM DATABASE HERE
    qDebug() << "ROOM ADDED TO MODEL";
    Room::RoomManager::getInstance()->roomModel->appendRow(new Models::RoomModelItem(room));
    Room::RoomManager::getInstance()->placeNewRoomInSpace();
    Room::RoomManager::roomInstances++;
}

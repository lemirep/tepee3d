#include "RoomManager.h"
// DEBUG
#include <QDebug>
#include <roomloader.h>

/*!
 * \namespace Room
 *
 * \brief The Room namespace holds all the classes that deal with
 * Rooms and their management.
 */

/*!
 * \class Room::RoomManager
 * \brief The Room::RoomManager class is responsible for managing all the
 * rooms ofthe Tepee3D application. It restores the rooms and their plugins
 * on startup, creates the model for the room selector menu, places rooms in
 * space. In addition, this where new plugins are added to a room.
 *
 * \sa Room::RoomBase
 */

Room::RoomManager* Room::RoomManager::instance = NULL;
int                Room::RoomManager::roomInstances = 0;

QString            Room::RoomManager::selectRoomsQuery = "";
QString            Room::RoomManager::insertRoomQuery = "";
QString            Room::RoomManager::updateRoomQuery = "";
QString            Room::RoomManager::deleteRoomQuery = "";

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
    this->roomModel = new SubListedListModel(new Room::RoomModelItem(NULL, NULL));
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
    qDebug() << " RoomManager Exposing Content >>>>>>>>>>>>";
    context->setContextProperty("roomModel", this->roomModel);
    context->setContextProperty("roomManager", this);
}

void    Room::RoomManager::receiveResultFromSQLQuery(QList<QSqlRecord> list, int id)
{
    qDebug() << "RoomManager received SQL Result";

    if (RoomLoader::lastCalled != 0)
    {
        RoomLoader::onRequestFinished(this, list);
    }
}

/*!
 * Returns the model containing the rooms.
 */
ListModel*  Room::RoomManager::getRoomModel() const
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
    Room::RoomModelItem *roomItem = NULL;
    Room::RoomBase *room = NULL;

    if ((roomItem = (Room::RoomModelItem*)this->getRoomModel()->find(roomId)) != NULL
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
    const QList<ListItem*> roomItemList = this->roomModel->toList();

    foreach (ListItem *item, roomItemList)
    {
        qreal roomPosAngle = posAngle * idx++;
        Room::RoomBase* room = ((Room::RoomModelItem *)(item))->getRoom();
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
 * \sa void        Room::RoomManager::setCurrentRoom(Room::RoomBase *room)
 */

void        Room::RoomManager::setCurrentRoom(int roomId)
{
    Room::RoomModelItem *roomItem = NULL;
    Room::RoomBase *room = NULL;
    if ((roomItem = (Room::RoomModelItem *)this->roomModel->find(roomId)))
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

    this->roomModel->appendRow(new Room::RoomModelItem(room));
    this->placeNewRoomInSpace();
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
    Room::RoomModelItem* roomItem = (Room::RoomModelItem *)(this->roomModel->find(roomModelId));
    Room::RoomBase* deletedRoom = (roomItem != NULL) ? roomItem->getRoom() : NULL;
    this->roomModel->removeRow(this->roomModel->getRowFromItem(roomItem), QModelIndex());
    if (deletedRoom != NULL)
    {
        Room::RoomManager::roomInstances--;
        // CLEAR ALL THE ROOM'S CONTENT BEFORE DELETING IT
        // REPLACE ALL THE ROOMS IF NECESSARY
    }
}

/*!
 * Edits the room identified by \a roomModelId with the name \a roomName, the position \a roomPosition and the scale \a roomScale.
 */
void        Room::RoomManager::editRoom(int roomModelId, QString roomName, QVector3D roomPosition, QVector3D roomScale)
{
    // UPDATES ROOM LOGICALLY -> UPDATE HAS ALREADY BEEN APPLIED TO QML ROOM
    Room::RoomModelItem* roomItem = (Room::RoomModelItem *)(this->roomModel->find(roomModelId));
    Room::RoomBase* editedRoom = (roomItem != NULL) ? roomItem->getRoom() : NULL;

    if (editedRoom != NULL)
    {
        editedRoom->setRoomName(roomName);
        editedRoom->setPosition(roomPosition);
        editedRoom->setScale(roomScale);
        // UPDATE ROOM ITEM IN MODEL FOR QML UPDATE
        roomItem->triggerItemUpdate();
    }
}

/*!
 * Adds a new plugin instance to the current room´s model. The plugin instance is a new clean
 * instance of the plugin defined by \a pluginModelId ensuring it behaves only in the room´s
 * scope.
 */

void        Room::RoomManager::addNewPluginToCurrentRoom(int pluginModelId)
{
    Plugins::PluginBase*    newPlugin = Plugins::PluginManager::getNewInstanceOfPlugin(pluginModelId);
    if (this->currentRoom == NULL)
        qWarning() << "Current Room is Null";
    if (newPlugin != NULL && this->currentRoom != NULL)
    {
        qDebug() << "Adding new plugin to Room";
        // INITIALIZE PLUGIN SERVICES ...
        Plugins::PluginManager::initRoomPlugin(newPlugin);
        this->currentRoom->addWidgetToRoom(newPlugin);
    }
    else
        qWarning() << "plugin Instance is NULL, cannot be added to room";
}

/*!
 * Removes the plugin specified by \a pluginModelId from the current room.
 */

void        Room::RoomManager::removePluginFromCurrentRoom(int pluginModelId)
{
    Plugins::PluginModelItem* pluginItem = (Plugins::PluginModelItem*)this->currentRoom->getRoomPluginsModel()->find(pluginModelId);

    if (pluginItem != NULL)
    {
        Plugins::PluginBase* plugin = pluginItem->getPlugin();
        Services::ServicesManager::disconnectObjectFromServices(plugin);
        this->currentRoom->getRoomPluginsModel()->removeRow(this->currentRoom->getRoomPluginsModel()->getRowFromItem(pluginItem));
        delete plugin;
    }
}

/*!
 * This method loads the room library to be used as the room logic for room management.
 * Using a library allow for future enhancement and eventual changes in shape without having
 * to change the logic employed. The library is loaded from a path relative to the application path.
 */

void        Room::RoomManager::loadRoomLibrary()
{
    QDir    roomDirectory = QApplication::applicationDirPath();

    // GO TO ROOM LIB DIRECTORIES
#if defined(Q_OS_WIN)
    if (roomDirectory.dirName().toLower() == "debug" || roomDirectory.dirName().toLower() == "release")
        roomDirectory.cdUp();
#elif defined(Q_OS_MAC)
    if (roomDirectory.dirName() == "MacOS")
    {
        roomDirectory.cdUp();
        roomDirectory.cdUp();
        roomDirectory.cdUp();
    }
#endif
    roomDirectory.cdUp();
    roomDirectory.cd(ROOM_LIBRARY_DIRECTORY);

    qDebug() << "ROOM DIR " << roomDirectory.absolutePath();

    // LOAD ROOM LIBRARY
    foreach (QString filename, roomDirectory.entryList(QDir::Files))
    {
        QPluginLoader loader(roomDirectory.absoluteFilePath(filename));
        RoomInterface* roomInt = qobject_cast<RoomInterface *>(loader.instance());
        if (roomInt)
        {
            this->roomPrototype = roomInt->getRoomBase();
            qDebug() << "ROOM LIBRARY INITIALIZED";
            break;
        }
        else
            qWarning() << "FAILED TO LOAD ROOM LIBRARY" << loader.errorString();
    }
}


/*!
 * Adds rooms the the room model. Rooms can then be restored from the database and
 * added on startup right here.
 */

bool        Room::RoomManager::addRoomToModel()
{
    // ROOMS ARE RESTORED FROM DATABASE HERE

    this->addNewRoom("RoomTest1");
    this->addNewRoom("RoomTest2");
    this->addNewRoom("RoomTest3");
    this->addNewRoom("RoomTest4");

    return true;
}

#include "RoomManager.h"
// DEBUG
#include <QDebug>

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

Room::RoomManager::RoomManager(QObject *parent) : QObject(parent)
{
    this->currentRoom = NULL;
    this->roomPrototype = NULL;
    this->roomUpdateTimer = new QTimer();
    this->roomModel = new SubListedListModel(new Room::RoomModelItem(NULL, NULL));
    this->loadRoomLibrary();
}

Room::RoomManager* Room::RoomManager::getInstance(QObject *parent)
{
    if (Room::RoomManager::instance == NULL)
        Room::RoomManager::instance = new Room::RoomManager(parent);
    return Room::RoomManager::instance;
}

Room::RoomManager::~RoomManager()
{
    delete this->roomModel;
}

void    Room::RoomManager::exposeContentToQml(QQmlContext *context)
{
    qDebug() << " RoomManager Exposing Content >>>>>>>>>>>>";
    context->setContextProperty("roomModel", this->roomModel);
    context->setContextProperty("roomManager", this);
}

void    Room::RoomManager::receiveResultFromSQLQuery(const QList<QSqlRecord> &)
{
    qDebug() << "RoomManager received SQL Result";
}

ListModel*  Room::RoomManager::getRoomModel() const
{
    return this->roomModel;
}

Room::RoomBase*  Room::RoomManager::getCurrentRoom()   const
{
    return this->currentRoom;
}


Plugins::PluginBase*    Room::RoomManager::getPluginFromRoom(int roomId, int pluginId) const
{
    Room::RoomModelItem *roomItem = NULL;
    Room::RoomBase *room = NULL;

    if ((roomItem = (Room::RoomModelItem*)this->getRoomModel()->find(roomId)) != NULL
            && (room = roomItem->getRoom()) != NULL)
        return room->getPluginFromRoom(pluginId);
    return NULL;
}

void        Room::RoomManager::placeNewRoomInSpace(Room::RoomBase *room)
{
    // PLACES THE ROOM IN SPACE SO THAT THEY WON'T COLLIDE ...
    // ROOMS ALREADY LOADED CANNOT BE MOVED SO THE NEW ROOM HAS TO BE ADDED AT THE RIGHT PLACE
    QList<ListItem *> roomModelItems = this->roomModel->toList();
    QList<Room::RoomBase *> rooms;
    foreach (ListItem *item, roomModelItems)
        rooms << ((Room::RoomModelItem*)item)->getRoom();

    // DEFAULT PLACEMENT POSITION
    // SORT ROOMS BY SIZE FROM THE LARGEST TO THE SMALLEST
    // PLACE BIGGEST IN THE CENTER
    // PLACE ALL THE OTHER ROOMS FROM BIGGEST TO SMALLEST ACCORDING THE ROOM IN THE CENTER

    // SORT ROOM BY SIZE
    foreach (Room::RoomBase* roomSaved, rooms)
    {
        Room::RoomBase* lastRoom = rooms.last();
        if (lastRoom > roomSaved)
            rooms.swap(rooms.indexOf(lastRoom), rooms.indexOf(roomSaved));
    }

    // INIT ROOM POSITION
//    room->setPosition(QVector3D(0, 0, 0));
//    foreach (Room::RoomBase* roomSaved, rooms)
//    {
//        if (room->collides(roomSaved))
//        {

//        }
//    }
    qDebug() << "Placing room in space";
}

void        Room::RoomManager::setCurrentRoom(Room::RoomBase *room)
{
    if (room == this->currentRoom)
        return ;
    qDebug() << "SETTING NEW ROOM";
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

void        Room::RoomManager::setCurrentRoom(int roomId)
{
    Room::RoomModelItem *roomItem = NULL;
    Room::RoomBase *room = NULL;
    qDebug() << "CALLING SET ROOM";
    if ((roomItem = (Room::RoomModelItem *)this->roomModel->find(roomId)))
        room = roomItem->getRoom();
    // IN ANY CASE WE SET IT SO THAT WE STOP UPDATING IF ROOM IS NULL
    this->setCurrentRoom(room);
}

void        Room::RoomManager::addNewRoom(QString roomName)
{
    qDebug() << "Adding New Room";

    Room::RoomBase *room = this->roomPrototype->createNewInstance();
    room->setRoomName(roomName + QString::number(Room::RoomManager::roomInstances++));
    room->setParent(NULL);
    room->setPosition(QVector3D(150, 150, 150));
    room->setScale(QVector3D(30, 20, 30));

    qDebug() << room->getRoomName();

    this->placeNewRoomInSpace(room);
    this->roomModel->appendRow(new Room::RoomModelItem(room));
    // ADD DEFAULT EMPTY ROOM IN THE MODEL
    // ROOM IS CREATED AT A COMPUTED LOCATION WHERE IT DOESN'T CONFLICT WITH ANY OTHER ROOM AND HAS A DEFAULT SIZE (1) AND IS SQUARED
    // WHEN ITS ATTRIBUTES ARE MODIFIED, VIRTUAL LOCATION IS AUTOMATICALLY ADJUSTED IF NECESSARY
}

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
    }
}

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
        {
            qWarning() << "ERRORS : "<< loader.errorString();
            qWarning() << "FAILED TO LOAD LIBRARY ROOM";
        }
    }
}

bool        Room::RoomManager::addRoomToModel()
{
    // ROOMS ARE RESTORED FROM DATABASE HERE

    Room::RoomBase *room1 = this->roomPrototype->createNewInstance();
    room1->setRoomName(QString("RoomTest1"));
    room1->setParent(NULL);
    room1->setPosition(QVector3D(0, 0, 150));
    room1->setScale(QVector3D(30, 20, 30));

    Room::RoomBase *room2 = this->roomPrototype->createNewInstance();
    room2->setRoomName("RoomTest2");
    room2->setParent(NULL);
    room2->setPosition(QVector3D(0, 150, 150));
    room2->setScale(QVector3D(30, 20, 30));

    Room::RoomBase *room3 = this->roomPrototype->createNewInstance();
    room3->setRoomName("RoomTest3");
    room3->setParent(NULL);
    room3->setPosition(QVector3D(150, -150, 150));
    room3->setScale(QVector3D(30, 20, 30));

    Room::RoomBase *room4 = this->roomPrototype->createNewInstance();
    room4->setRoomName("RoomTest4");
    room4->setParent(NULL);
    room4->setPosition(QVector3D(150, 150, 150));
    room4->setScale(QVector3D(30, 20, 30));

    this->roomModel->appendRow(new Room::RoomModelItem(room1));
    this->roomModel->appendRow(new Room::RoomModelItem(room2));
    this->roomModel->appendRow(new Room::RoomModelItem(room3));
    this->roomModel->appendRow(new Room::RoomModelItem(room4));

    return true;
}

#include "RoomManager.h"
// DEBUG
#include <QDebug>

Room::RoomManager* Room::RoomManager::instance = NULL;

Room::RoomManager::RoomManager(QObject *parent) : QObject(parent)
{
    this->roomModel = new ListModel(new Room::RoomModelItem(NULL, NULL));
    this->roomUpdateTimer = new QTimer();
    this->currentRoom = NULL;
    this->roomPrototype = NULL;
    this->currentRoomPluginsModel = new ListModel(new Plugins::PluginModelItem(NULL, NULL));
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
    context->setContextProperty("roomModel", this->roomModel);
    context->setContextProperty("roomManager", this);
    context->setContextProperty("currentRoomPluginsModel", this->currentRoomPluginsModel);
}

void    Room::RoomManager::receiveResultFromSQLQuery(const QList<QSqlRecord> &result)
{
    qDebug() << "RoomManager receive SQL Result";
}

ListModel*  Room::RoomManager::getRoomModel() const
{
    return this->roomModel;
}

Room::RoomBase*  Room::RoomManager::getCurrentRoom()   const
{
    return this->currentRoom;
}

void        Room::RoomManager::placeRoomsInSpace()
{
    // PLACES THE ROOM IN SPACE SO THAT THEY WON'T COLLIDE ...
}

void        Room::RoomManager::reloadCurrentRoomPluginsModel()
{
    // LOAD PLUGINS MODEL TO SHOW IN LEFT MENU
    // WE COPY THE PLUGINS OF THE ROOM IN THE LEFT MENU
    this->currentRoomPluginsModel->clear();
    if (this->currentRoom == NULL)
        return ;
    QList<Plugins::PluginBase *> plugins = this->currentRoom->getWidgetsList();
    qDebug() << "Clearing Room Plugins Model";
    foreach (Plugins::PluginBase *plugin, plugins)
    {
        qDebug() << "Appending Plugins Item to Plugins Model";
        this->currentRoomPluginsModel->appendRow(new Plugins::PluginModelItem(plugin));
    }
}

void        Room::RoomManager::setCurrentRoom(Room::RoomBase *room)
{
    if (room == this->currentRoom)
        return ;
    qDebug() << "SETTING NEW ROOM";
    this->roomUpdateTimer->stop();
    if (this->currentRoom != NULL)
        QObject::disconnect(this->roomUpdateTimer, SIGNAL(timeout()), this->currentRoom, SLOT(updateRoom()));

    this->currentRoom = room;
    this->reloadCurrentRoomPluginsModel();

    if (this->currentRoom != NULL)
    {
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

    static int i = 0;
    Room::RoomBase *room4 = this->roomPrototype->createNewInstance();
    room4->setRoomName(roomName + QString::number(i++));
    room4->setParent(NULL);
    room4->setPosition(QVector3D(150, 150, 150));
    room4->setScale(QVector3D(30, 20, 30));

    qDebug() << room4->getRoomName();

    this->roomModel->appendRow(new Room::RoomModelItem(room4));
    this->placeRoomsInSpace();
    // ADD DEFAULT EMPTY ROOM IN THE MODEL
    // ROOM IS CREATED A A COMPUTED LOCATION WHERE IT DOESN'T CONFLICT WITH ANY OTHER ROOM AND HAS A DEFAULT SIZE (1) AND SQUARED
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
        // CLEAR ALL THE ROOM'S CONTENT BEFORE DELETING IT
        // REPLACE ALL THE ROOMS IF NECESSARY
        this->placeRoomsInSpace();
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
    if (newPlugin != NULL)
    {
        // MAKE ALL PLUGINS CONNECTION HERE
        emit connectObjectToServices(newPlugin);
        qDebug() << "Adding new plugin to Room";
        if (this->currentRoom != NULL)
            this->currentRoom->addWidgetToRoom(newPlugin);
        this->reloadCurrentRoomPluginsModel();
    }
    else
        qWarning() << "plugin Instance is NULL, cannot be added to room";
}

void        Room::RoomManager::removePluginFromCurrentRoom(int pluginModelId)
{
    Plugins::PluginModelItem* pluginItem = (Plugins::PluginModelItem*)this->currentRoomPluginsModel->find(pluginModelId);

    if (pluginItem != NULL)
    {
        Plugins::PluginBase* plugin = pluginItem->getPlugin();
        this->currentRoomPluginsModel->removeRow(this->currentRoomPluginsModel->getRowFromItem(pluginItem));
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
            qDebug() << "LIBRARY INITIALIZED";
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
    room1->setPosition(QVector3D(0, 15, 150));
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

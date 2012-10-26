#include "RoomManager.h"
// DEBUG
#include <iostream>

Room::RoomManager::RoomManager(QObject *parent) : QObject(parent)
{
    this->roomModel = new ListModel(new RoomModelItem(NULL, NULL));
    this->roomUpdateTimer = new QTimer();
    this->currentRoom = NULL;
    this->loadRoomLibrary();
    this->addRoomToModel();
}

Room::RoomManager::~RoomManager()
{
    delete this->roomModel;
}

void    Room::RoomManager::exposeContentToQml(QQmlContext *context)
{
    context->setContextProperty("roomModel", this->roomModel);
    context->setContextProperty("roomManager", this);
}

ListModel*  Room::RoomManager::getRoomModel() const
{
    return this->roomModel;
}

Room::RoomBase*  Room::RoomManager::getCurrentRoom()   const
{
    return this->currentRoom;
}

void        Room::RoomManager::setCurrentRoom(Room::RoomBase *room)
{
    if (room == this->currentRoom)
        return ;
    std::cout << "SETTING NEW ROOM" << std::endl;
    this->roomUpdateTimer->stop();
    if (this->currentRoom != NULL)
        QObject::disconnect(this->roomUpdateTimer, SIGNAL(timeout()), this->currentRoom, SLOT(updateRoom()));

    this->currentRoom = room;
    if (this->currentRoom != NULL)
    {
        QObject::connect(this->roomUpdateTimer, SIGNAL(timeout()), this->currentRoom, SLOT(updateRoom()));
        this->roomUpdateTimer->start(ROOM_UPDATE_TIME);
    }
}

void        Room::RoomManager::setCurrentRoom(int roomId)
{
    RoomModelItem *roomItem = NULL;
    Room::RoomBase *room = NULL;
    std::cout << "CALLING SET ROOM" << std::endl;
    if ((roomItem = (RoomModelItem *)this->roomModel->find(roomId)))
        room = roomItem->getRoom();
    // IN ANY CASE WE SET IT SO THAT WE STOP UPDATING IF ROOM IS NULL
    this->setCurrentRoom(room);
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

    std::cout << "ROOM DIR " << roomDirectory.absolutePath().toStdString() << std::endl;

    // LOAD ROOM LIBRARY
    foreach (QString filename, roomDirectory.entryList(QDir::Files))
    {
        QPluginLoader loader(roomDirectory.absoluteFilePath(filename));
        RoomInterface* roomInt = qobject_cast<RoomInterface *>(loader.instance());
        if (roomInt)
        {
            this->roomPrototype = roomInt->getRoomBase();
            std::cout << "LIBRARY INITIALIZED" << std::endl;
            break;
        }
        else
        {
            std::cout << "ERRORS : "<< loader.errorString().toStdString() << std::endl;
            std::cout << "FAILED TO LOAD LIBRARY ROOM" << std::endl;
        }
    }
}

bool        Room::RoomManager::addRoomToModel()
{
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


    this->roomModel->appendRow(new RoomModelItem(room1));
    this->roomModel->appendRow(new RoomModelItem(room2));
    this->roomModel->appendRow(new RoomModelItem(room3));
    this->roomModel->appendRow(new RoomModelItem(room4));
    //    this->roomModel->appendRow(new RoomModelItem(room5));

    return true;
}

#include "RoomManager.h"
// DEBUG
#include <QDebug>


Room::RoomManager::RoomManager(QObject *parent) : QObject(parent)
{
    this->roomModel = new ListModel(new Room::RoomModelItem(NULL, NULL));
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
    emit (executeSQLQuery("SELECT * FROM TATA;", this));
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

void        Room::RoomManager::setCurrentRoom(Room::RoomBase *room)
{
    if (room == this->currentRoom)
        return ;
    qDebug() << "SETTING NEW ROOM";
    this->roomUpdateTimer->stop();
    if (this->currentRoom != NULL)
        QObject::disconnect(this->roomUpdateTimer, SIGNAL(timeout()), this->currentRoom, SLOT(updateRoom()));

    this->currentRoom = room;
    if (this->currentRoom != NULL)
    {
        // LOAD PLUGINS MODEL TO SHOW IN LEFT MENU
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

void        Room::RoomManager::addNewRoom()
{
    qDebug() << "Adding New Room";
    // ADD DEFAULT EMPTY ROOM IN THE MODEL
    // ROOM IS CREATED A A COMPUTED LOCATION WHERE IT DOESN'T CONFLICT WITH ANY OTHER ROOM AND HAS A DEFAULT SIZE (1) AND SQUARED
    // WHEN ITS ATTRIBUTES ARE MODIFIED, VIRTUAL LOCATION IS AUTOMATICALLY ADJUSTED IF NECESSARY
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
    }
    else
        qWarning() << "plugin Instance is NULL, cannot be added to room";
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

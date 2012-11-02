#include "BasicRoom.h"
//DEBUG
#include <QDebug>


BasicRoom::BasicRoom() : RoomBase()
{

}

//BasicRoom::BasicRoom(QQuickItem *parentQmlObject, QQmlEngine *engine,QString roomName, QVector3D position, QVector3D scale)
//    : QObject(),
//      parentQmlItem(parentQmlObject),
//      engine(engine),
//      roomName(roomName),
//      position(position),
//      scale(scale)
//{
//    this->id = BasicRoom::nextId++;
//    this->updateRoomCenter();

////    this->widgets = QList<PluginInterface*>();
////    this->qmlFile = "qml/Tepee3DSampleApp/Room.qml";
////    QQmlComponent *component = new QQmlComponent(engine, qmlFile);
////    this->roomQmlItem = qobject_cast<QQuickItem*>(component->create());
////    if (this->roomQmlItem)
////    {
////        std::cout << " NEW ROOM CREATED" << std::endl;
////        this->roomQmlItem->setParentItem(this->parentQmlItem);
//////        this->roomQmlItem->setProperty("position", QVector3D(0, 0, 8));
////        // SET ROOM QML ITEM'S PROPERTIES HERE
////    }
//}

BasicRoom::~BasicRoom()
{
}

Room::RoomBase*  BasicRoom::createNewInstance()
{
    BasicRoom* room = new BasicRoom();
    room->setRoomQmlFile(BASICROOM_QML_FILE);
    return room;
}


QQuickItem*   BasicRoom::getRoomQmlObject() const
{
    return NULL;
}

QObject*    BasicRoom::getObject()
{
    return this;
}

void    BasicRoom::updateRoom()
{
    qDebug() << "Updating " << this->getRoomName();
    foreach (Plugins::PluginBase* plugin, this->widgets)
    {
        qDebug() << "Updating " << plugin->getPluginName();
    }
}

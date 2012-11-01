#include "BasicRoom.h"
//DEBUG
#include <QDebug>


int BasicRoom::nextId = 0;

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
    return new BasicRoom();
}

QVector3D BasicRoom::getPosition() const
{
    return this->position;
}

void    BasicRoom::setPosition(const QVector3D& position)
{
    this->position = position;
    this->updateRoomCenter();
}


QVector3D BasicRoom::getScale() const
{
    return this->scale;
}

void    BasicRoom::setScale(const QVector3D &scale)
{
    this->scale = scale;
    this->updateRoomCenter();
}

QVector3D BasicRoom::getRoomCenter() const
{
    return this->roomCenter;
}

void    BasicRoom::updateRoomCenter()
{
    this->roomCenter.setX((this->position.x() * this->scale.x()) / 2);
    this->roomCenter.setY((this->position.y() * this->scale.y()) / 2);
    this->roomCenter.setZ((this->position.z() * this->scale.z()) / 2);
}

QString BasicRoom::getRoomName() const
{
    return this->roomName;
}

void    BasicRoom::setRoomName(const QString& name)
{
    this->roomName = name;
}

QString BasicRoom::getRoomQml() const
{
    return this->qmlFile;
}

QList<Plugins::PluginBase*>  BasicRoom::getWidgetsList() const
{
    return this->widgets;
}

QQuickItem*   BasicRoom::getRoomQmlObject() const
{
    return roomQmlItem;
}

QObject*    BasicRoom::getObject()
{
    return this;
}

void    BasicRoom::addWidgetToRoom(Plugins::PluginBase *plugin)
{
    widgets.push_front(plugin);
}

void    BasicRoom::updateRoom()
{
    qDebug() << "Updating " << this->getRoomName();
    foreach (Plugins::PluginBase* plugin, this->widgets)
    {
        qDebug() << "Updating " << plugin->getPluginName();
    }
}

#include "RoomBase.h"
// DEBUG
#include <QDebug>

int Room::RoomBase::nextId = 0;

Room::RoomBase::RoomBase() : QObject()
{
    this->roomId = Room::RoomBase::nextId++;
    this->widgets = QList<Plugins::PluginBase*>();
}

int         Room::RoomBase::getRoomId() const
{
    return this->roomId;
}

Room::RoomBase*   Room::RoomBase::getRoomBase()
{
    return this;
}

QString     Room::RoomBase::getRoomName() const
{
    return this->roomName;
}

QString     Room::RoomBase::getRoomQmlFile() const
{
    return this->roomQmlFile;
}

QVector3D   Room::RoomBase::getPosition() const
{
    return this->position;
}

QVector3D   Room::RoomBase::getScale() const
{
    return this->scale;
}

QVector3D   Room::RoomBase::getRoomNorthWallPosition()  const
{
    QVector3D   northWall = this->position;
    northWall.setZ(northWall.z() + this->scale.z());
    return northWall;
}

QVector3D   Room::RoomBase::getRoomSouthWallPosition()  const
{
    QVector3D   southWall = this->position;
    southWall.setZ(southWall.z() - this->scale.z());
    return southWall;
}

QVector3D   Room::RoomBase::getRoomEastWallPosition()   const
{
    QVector3D   eastWall = this->position;
    eastWall.setX(eastWall.x() + this->scale.x());
    return eastWall;
}

QVector3D   Room::RoomBase::getRoomWestWallPosition()   const
{
    QVector3D   westWall = this->position;
    westWall.setX(westWall.x() - this->scale.x());
    return westWall;
}

QVector3D   Room::RoomBase::getRoomUpWallPosition() const
{
    QVector3D   upWall = this->position;
    upWall.setY(upWall.y() + this->scale.y());
    return upWall;
}

QVector3D   Room::RoomBase::getRoomDownWallPosition()   const
{
    QVector3D   downWall = this->position;
    downWall.setY(downWall.y() - this->scale.y());
    return downWall;
}

void        Room::RoomBase::updateRoomCenter()
{
    this->roomCenter.setX((this->position.x() * this->scale.x()) / 2);
    this->roomCenter.setY((this->position.y() * this->scale.y()) / 2);
    this->roomCenter.setZ((this->position.z() * this->scale.z()) / 2);
}

QVector3D   Room::RoomBase::getRoomCenter() const
{
    return this->roomCenter;
}

void        Room::RoomBase::setScale(const QVector3D &scale)
{
    this->scale = scale;
    this->updateRoomCenter();
}

void        Room::RoomBase::setRoomName(const QString &name)
{
    this->roomName = name;
}

void        Room::RoomBase::setPosition(const QVector3D &position)
{
    this->position = position;
    this->updateRoomCenter();
}

void        Room::RoomBase::setRoomQmlFile(const QString &file)
{
    this->roomQmlFile = file;
}

void        Room::RoomBase::addWidgetToRoom(Plugins::PluginBase *widget)
{
    this->widgets.push_front(widget);
}

QList<Plugins::PluginBase*> Room::RoomBase::getWidgetsList() const
{
    return this->widgets;
}

void        Room::RoomBase::updateRoom()
{
    qDebug() << "Room is updated -> but should you should have implemented this method in the room subclass";
}


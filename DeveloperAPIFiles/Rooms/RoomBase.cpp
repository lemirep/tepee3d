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

QVector3D   Room::RoomBase::getRoomCenter() const
{
    return this->roomCenter;
}

void        Room::RoomBase::setScale(const QVector3D &scale)
{
    this->scale = scale;
}

void        Room::RoomBase::setRoomName(const QString &name)
{
    this->roomName = name;
}

void        Room::RoomBase::setPosition(const QVector3D &position)
{
    this->position = position;
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


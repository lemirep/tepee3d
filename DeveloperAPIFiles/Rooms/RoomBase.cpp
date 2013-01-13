#include "RoomBase.h"
// DEBUG
#include <QDebug>

int Room::RoomBase::nextId = 0;

Room::RoomBase::RoomBase() : QQuickItem()
{
    this->roomId = Room::RoomBase::nextId++;
    this->roomProperties = new Room::RoomProperties(this);
}

int         Room::RoomBase::getRoomId() const
{
    return this->roomId;
}

Room::RoomBase*   Room::RoomBase::getRoomBase()
{
    return this;
}

double            Room::RoomBase::getRoomVolume() const
{
    QVector3D scale = this->getScale();

    return scale.x() * scale.y() * scale.z();
}

bool            Room::RoomBase::operator <(RoomBase *room) const
{
    return this->getRoomVolume() < room->getRoomVolume();
}

bool            Room::RoomBase::operator >(RoomBase *room) const
{
    return this->getRoomVolume() > room->getRoomVolume();
}

QString     Room::RoomBase::getRoomName() const
{
    return this->roomProperties->getRoomName();
}

QString     Room::RoomBase::getRoomQmlFile() const
{
    return this->roomQmlFile;
}

QVector3D   Room::RoomBase::getPosition() const
{
    return this->roomProperties->getPosition();
}

QVector3D   Room::RoomBase::getScale() const
{
    return this->roomProperties->getScale();
}

ListModel*  Room::RoomBase::getRoomPluginsModel()   const
{
    return this->roomProperties->getRoomPluginsModel();
}

void        Room::RoomBase::setScale(const QVector3D &scale)
{
    this->roomProperties->setScale(scale);
}

void        Room::RoomBase::setRoomName(const QString &name)
{
    this->roomProperties->setRoomName(name);
}

void        Room::RoomBase::setPosition(const QVector3D &position)
{
    this->roomProperties->setPosition(position);
}

void        Room::RoomBase::setRoomQmlFile(const QString &file)
{
    this->roomQmlFile = file;
}

void        Room::RoomBase::addWidgetToRoom(Plugins::PluginBase *widget)
{
    this->roomProperties->getRoomPluginsModel()->appendRow(new Plugins::PluginModelItem(widget));
}

void        Room::RoomBase::updateRoom()
{
    qDebug() << "Room is updated -> but should you should have implemented this method in the room subclass";
}

Room::RoomProperties*    Room::RoomBase::getRoomProperties() const
{
    return this->roomProperties;
}

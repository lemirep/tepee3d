#include "RoomBase.h"
// DEBUG
#include <QDebug>

int Room::RoomBase::id = 0;

Room::RoomBase::RoomBase() : QObject()
{
    this->roomId = Room::RoomBase::id++;
}

Room::RoomBase*   Room::RoomBase::getRoomBase()
{
    return this;
}

void        Room::RoomBase::updateRoom()
{
    qDebug() << "Room is updated -> but should you should have implemented this method in the room subclass";
}

int         Room::RoomBase::getRoomId() const
{
    return this->roomId;
}

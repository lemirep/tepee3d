#include "RoomBase.h"
// DEBUG
#include <iostream>

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
    std::cout << "Room is updated" << std::endl;
}

int         Room::RoomBase::getRoomId() const
{
    return this->roomId;
}

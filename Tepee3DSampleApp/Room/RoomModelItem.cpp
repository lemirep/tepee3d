#include "RoomModelItem.h"

Room::RoomModelItem::RoomModelItem(Room::RoomBase *room, QObject *parent) : ListItem(parent)
{
    this->room = room;
}

Room::RoomModelItem::~RoomModelItem()
{
}

int         Room::RoomModelItem::id() const
{
    return this->room->getRoomId();
}

QVariant    Room::RoomModelItem::data(int role) const
{
    switch (role)
    {
    case roomId :
        return this->id();
    case roomName :
        return this->room->getRoomName();
    case roomPosition :
        return this->room->getPosition();
    case roomNorthWallPosition :
        return this->room->getRoomNorthWallPosition();
    case roomSouthWallPosition :
        return this->room->getRoomSouthWallPosition();
    case roomEastWallPosition :
        return this->room->getRoomEastWallPosition();
    case roomWestWallPosition :
        return this->room->getRoomWestWallPosition();
    case roomUpWallPosition :
        return this->room->getRoomUpWallPosition();
    case roomDownWallPosition :
        return this->room->getRoomDownWallPosition();
    case roomScale :
        return this->room->getScale();
    case roomCenter :
        return this->room->getRoomCenter();
    case roomQmlFile :
        return this->room->getRoomQmlFile();
    default :
        return QVariant();
    }
}

QHash<int, QByteArray>  Room::RoomModelItem::roleNames()  const
{
    QHash<int, QByteArray>  roles;

    roles[roomId]       = "roomId";
    roles[roomName]     = "roomName";
    roles[roomScale]    = "roomScale";
    roles[roomCenter]   = "roomCenter";
    roles[roomPosition] = "roomPosition";
    roles[roomQmlFile]  = "roomQmlFile";
    roles[roomNorthWallPosition] = "roomNorthWallPosition";
    roles[roomSouthWallPosition] = "roomSouthWallPosition";
    roles[roomEastWallPosition] = "roomEastWallPosition";
    roles[roomWestWallPosition] = "roomWestWallPosition";
    roles[roomUpWallPosition] = "roomUpWallPosition";
    roles[roomDownWallPosition] = "roomDownWallPosition";

    return roles;
}

Room::RoomBase*   Room::RoomModelItem::getRoom()    const
{
    return this->room;
}

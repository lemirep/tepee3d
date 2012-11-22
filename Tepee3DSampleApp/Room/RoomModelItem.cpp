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

    return roles;
}

Room::RoomBase*   Room::RoomModelItem::getRoom()    const
{
    return this->room;
}

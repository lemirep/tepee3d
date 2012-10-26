#include "RoomModelItem.h"

RoomModelItem::RoomModelItem(Room::RoomBase *room, QObject *parent) : ListItem(parent)
{
    this->room = room;
}

RoomModelItem::~RoomModelItem()
{
}

int         RoomModelItem::id() const
{
    return this->room->getRoomId();
}

QVariant    RoomModelItem::data(int role) const
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
    default :
        return QVariant();
    }
}

QHash<int, QByteArray>  RoomModelItem::roleNames()  const
{
    QHash<int, QByteArray>  roles;

    roles[roomId]       = "roomId";
    roles[roomName]     = "roomName";
    roles[roomScale]    = "roomScale";
    roles[roomCenter]   = "roomCenter";
    roles[roomPosition] = "roomPosition";

    return roles;
}

Room::RoomBase*   RoomModelItem::getRoom()    const
{
    return this->room;
}

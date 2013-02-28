#include "RoomModelItem.h"

/*!
 * \class Room::RoomModelItem
 *
 * \brief The Room::RoomModelItem class represent a room item for the rooms model.
 * It contains a brief description of each room that can be seen in the room selector
 * menu.
 */


Room::RoomModelItem::RoomModelItem(Room::RoomBase *room, QObject *parent) : SubListedListItem(parent)
{
    this->room = room;
}

Room::RoomModelItem::~RoomModelItem()
{
}

/*!
 * Returns the id of the RoomModelItem.
 */
int         Room::RoomModelItem::id() const
{
    return this->room->getRoomId();
}

/*!
 * Returns a QVariant containing the data for the role role.
 */
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
    case roomQmlFile :
        return this->room->getRoomQmlFile();
    default :
        return QVariant();
    }
}

/*!
 * Returns a hash containg the various role names of a RoomModelItem.
 */
QHash<int, QByteArray>  Room::RoomModelItem::roleNames()  const
{
    QHash<int, QByteArray>  roles;

    roles[roomId]       = "roomId";
    roles[roomName]     = "roomName";
    roles[roomScale]    = "roomScale";
    roles[roomPosition] = "roomPosition";
    roles[roomQmlFile]  = "roomQmlFile";

    return roles;
}

/*!
 * Returns the actual instance of the room the RoomModelItem is a description of.
 */
Room::RoomBase*   Room::RoomModelItem::getRoom()    const
{
    return this->room;
}

/*!
 * Returns the plugins model of the room.
 */
ListModel*      Room::RoomModelItem::submodel() const
{
    return this->room->getRoomPluginsModel();
}

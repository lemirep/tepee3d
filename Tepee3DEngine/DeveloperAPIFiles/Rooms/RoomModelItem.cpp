#include "RoomModelItem.h"

/*!
 * \class Models::RoomModelItem
 * \code
 * #include <RoomModelItem.h>
 * \endcode
 * \brief The Models::RoomModelItem class represent a room item for the rooms model.
 * It contains a brief description of each room that can be seen in the room selector
 * menu.
 *
 *   Tepee3D
 *
 * \sa Room::RoomBase
 *
 * \inmodule Tepee3D
 */

/*!
 * Constructs a new Models::RoomModelItem instance given a \a room and an optionnal \a parent.
 */
Models::RoomModelItem::RoomModelItem(Room::RoomBase *room, QObject *parent) : SubListedListItem(parent)
{
    this->room = room;
}

/*!
 * Destroys a Models::RoomModelItem instance.
 */
Models::RoomModelItem::~RoomModelItem()
{
}

/*!
 * Returns the id of the RoomModelItem.
 */
int         Models::RoomModelItem::id() const
{
    return this->room->getRoomId();
}

/*!
 * Returns a QVariant containing the data for a given \a role identifier.
 */
QVariant    Models::RoomModelItem::data(int role) const
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
QHash<int, QByteArray>  Models::RoomModelItem::roleNames()  const
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
Room::RoomBase*   Models::RoomModelItem::getRoom()    const
{
    return this->room;
}

/*!
 * Returns the plugins model of the room.
 */
Models::ListModel*      Models::RoomModelItem::submodel() const
{
    return this->room->getRoomPluginsModel();
}

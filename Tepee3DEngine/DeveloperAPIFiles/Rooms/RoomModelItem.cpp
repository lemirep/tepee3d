/****************************************************************************
**
** Copyright (C) Paul Lemire, Tepee3DTeam and/or its subsidiary(-ies).
** Contact: paul.lemire@epitech.eu
** Contact: tepee3d_2014@labeip.epitech.eu
**
** This file is part of the Tepee3D project
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
****************************************************************************/

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
    if (this->room != NULL)
        delete this->room;
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
    case roomTextureFolder:
        return this->room->getRoomTextureFolderName();
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
    roles[roomQmlFile]  = "roomTextureFolder";

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

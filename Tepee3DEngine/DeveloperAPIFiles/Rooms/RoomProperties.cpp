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

#include "RoomProperties.h"

/*!
 * \class Room::RoomProperties
 * \code
 * #include <RoomProperties.h>
 * \endcode
 * \brief The Room::RoomProperties class contains all the attributes
 * that define a room.
 *
 *  \inmodule Tepee3D
 *
 * \sa Room::RoomBase
 */


/*!
 *  Constructs a new Room::RoomProperties instance with the optionnal \a parent argument.
 */

Room::RoomProperties::RoomProperties(QObject *parent) : QObject(parent)
{
    this->pluginsModel = new Models::ListModel(new Models::PluginModelItem(NULL, NULL));
}

/*!
 * Destroys a Room::RoomProperties instance.
 */
Room::RoomProperties::~RoomProperties()
{
    qDebug() << "Deleting RoomProperties";
    delete this->pluginsModel;
}

/*!
 * Returns the room's name.
 */
QString     Room::RoomProperties::getRoomName() const
{
    return this->roomName;
}

/*!
 * Returns a 3D vector containing the room's position.
 */
QVector3D   Room::RoomProperties::getPosition() const
{
    return this->position;
}

/*!
 * Returns a 3D vector containing the room's scale.
 */
QVector3D   Room::RoomProperties::getScale() const
{
    return this->scale;
}

/*!
 * Returns ListModel containing the room's plugins model.
 */
Models::ListModel*   Room::RoomProperties::getRoomPluginsModel() const
{
    return this->pluginsModel;
}

/*!
 * Sets the room's name to \a name.
 */
void        Room::RoomProperties::setRoomName(const QString &name)
{
    this->roomName = name;
}

/*!
 * Sets the room's position to \a position.
 */
void        Room::RoomProperties::setPosition(const QVector3D &position)
{
    this->position = position;
}

/*!
 * Sets the room's scale to \a scale.
 */
void        Room::RoomProperties::setScale(const QVector3D &scale)
{
    this->scale = scale;
}

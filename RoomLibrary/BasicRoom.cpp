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

#include "BasicRoom.h"
//DEBUG
#include <QDebug>

/*!
 * \class BasicRoom
 * \code
 * #include <BasicRoom.h>
 * \endcode
 * \brief The BasicRoom::BasicRoom class is simplest implementation of the RoomBase
 *
 * The BasicRoom class represents a squared room. It is compiled in a shared library
 * and then dynamically loaded in the Tepee3DEngine at runtime.
 *
 * \sa Room::RoomBase
 *
 *  \inmodule Tepee3D
 */

/*!
 * Constructs a new BasicRoom. This method being private cannot be called
 * directly.
 * \sa createNewInstance()
 */
BasicRoom::BasicRoom() : RoomBase()
{
}

/*!
 * Destroys a BasicRoom instance.
 */
BasicRoom::~BasicRoom()
{
}

/*!
 * Returns a new BasicRoom instance properly initialised.
 */
Room::RoomBase*  BasicRoom::createNewInstance()
{
    BasicRoom* room = new BasicRoom();
    room->setRoomQmlFile(BASICROOM_QML_FILE);
    return room;
}

/*!
 * Returns the current instance as a QObject for signals manipulations.
 */
QObject*    BasicRoom::getObject()
{
    return this;
}

/*!
 * Triggered when the room becomes the current room to update the plugins it contains
 */
void    BasicRoom::updateRoom()
{
    foreach (Models::ListItem* pluginItem, this->getRoomPluginsModel()->toList())
    {
        Plugins::PluginBase *plugin = NULL;
        if ((plugin = reinterpret_cast<Models::PluginModelItem *>(pluginItem)->getPlugin()) != NULL &&
                plugin->needsUpdating())
            plugin->updatePlugin();
    }
}

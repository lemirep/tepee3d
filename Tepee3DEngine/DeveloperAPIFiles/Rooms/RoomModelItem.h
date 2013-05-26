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

#ifndef ROOMMODELITEM_H
#define ROOMMODELITEM_H

#include "SubListedListItem.h"
#include "RoomBase.h"

namespace   Models
{

class RoomModelItem : public Models::SubListedListItem
{
    Q_OBJECT
public:

    enum    RoomModelItemRoles
    {
        roomId  =   Qt::UserRole + 1,
        roomPosition,
        roomScale,
        roomName,
        roomQmlFile
    };



    explicit RoomModelItem(Room::RoomBase *room, QObject *parent = 0);
    ~RoomModelItem();

    int                     id()                const;
    QVariant                data(int role)      const;
    QHash<int, QByteArray>  roleNames()         const;

    Room::RoomBase*         getRoom()           const;
    Models::ListModel*      submodel()          const;

private:
    Room::RoomBase               *room;

};

}
#endif // ROOMMODELITEM_H

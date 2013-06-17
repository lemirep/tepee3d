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

#ifndef ROOMBASE_H
#define ROOMBASE_H

#include <QObject>
#include <QVector3D>
#include <QQuickItem>
#include <QJsonArray>
#include <qmath.h>
#include "PluginBase.h"
#include "RoomInterface.h"
#include "RoomProperties.h"
#include "ListModel.h"
#include "PluginModelItem.h"

namespace Room
{

class RoomBase : public QObject, public Room::RoomInterface
{
    Q_OBJECT
    Q_INTERFACES(Room::RoomInterface)

protected:
    static int                      nextId;
    int                             roomId;

    QString                         roomQmlFile;
    Room::RoomProperties            *roomProperties;

public:
    RoomBase();
    virtual ~RoomBase();

    int                                     getRoomId()        const;
    RoomBase*                               getRoomBase();

    void                                    setRoomQmlFile(const QString &file);
    void                                    addWidgetToRoom(Plugins::PluginBase *widget);
    void                                    removeWidgetFromRoom(Models::PluginModelItem *pluginItem);
    void                                    placeWidgetsInSpace();

    void                                    enterRoom();
    void                                    leaveRoom();

    Models::ListModel*                      getRoomPluginsModel() const;
    Plugins::PluginBase*                    getPluginFromRoom(int pluginId) const;
    Room::RoomProperties*                   getRoomProperties() const;

    virtual bool                            operator >(RoomBase *room) const;
    virtual bool                            operator <(RoomBase *room) const;
    virtual bool                            collides(RoomBase *room) const;
    virtual double                          getRoomVolume()    const;

    virtual QString                         getRoomName()      const;
    virtual QString                         getRoomQmlFile()   const;

    virtual QVector3D                       getPosition()      const;
    virtual QVector3D                       getScale()         const;
    virtual QVector3D                       getMinBoundingPoint()   const;
    virtual QVector3D                       getMaxBoundingPoint()   const;

    virtual void                            setScale(const QVector3D& scale);
    virtual void                            setRoomName(const QString& name);
    virtual void                            setPosition(const QVector3D& position);

    virtual RoomBase*                       createNewInstance() = 0;
    virtual QObject*                        getObject()         = 0;

    virtual QJsonDocument                   toJsonRepresentation();


signals :

    void                                    roomEntered();
    void                                    roomLeft();

public slots :
    virtual void                            updateRoom();
    virtual void                            focusStateChangeRequest(Plugins::PluginEnums::PluginState, QObject*);

};

}

#endif // ROOMBASE_H

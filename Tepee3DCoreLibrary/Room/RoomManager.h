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

#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include <QCoreApplication>
#include <QTimer>
#include <PluginManager.h>
#include <QVector3D>
#include <qmath.h>
#include "RoomLoader.h"
#include "SubListedListModel.h"
#include "RoomModelItem.h"
#include "DatabaseServiceUserInterface.h"
#include "PlatformFactory.h"

#define ROOM_UPDATE_TIME 500

class RoomLoader;

namespace   Room
{
class RoomManager : public QObject, public View::QmlContentExposerInterface
{
    Q_OBJECT
    Q_INTERFACES(View::QmlContentExposerInterface)

public:
    ~RoomManager();
    static RoomManager*             getInstance(QObject *parent = NULL);
    static Room::RoomBase*       getNewRoomInstance();

    void                                          restoreRooms();

    Models::ListModel*                 getRoomModel() const;
    static void                                addRoomToModel(Room::RoomBase *room);

    Plugins::PluginBase*              getPluginFromRoom(int roomId, int pluginId) const;

    void                                         setCurrentRoom(RoomBase *room);
    RoomBase*                            getCurrentRoom()    const;

    // QmlContentExposer
    void                                         exposeContentToQml(QQmlContext *context);

    // METHODS THAT CAN BE CALLED FROM QML
    Q_INVOKABLE    void     setCurrentRoom(int roomModelId);
    Q_INVOKABLE    void     addNewPluginToCurrentRoom(int pluginModelId);
    Q_INVOKABLE    void     removePluginFromCurrentRoom(int pluginModelId);
    Q_INVOKABLE    void     addNewRoom(QString roomName = "RoomTest-");
    Q_INVOKABLE    void     deleteRoom(int roomModelId);
    Q_INVOKABLE    void     editRoom(int roomModelId, QString roomName, QVector3D roomPosition, QVector3D roomScale);
    Q_INVOKABLE    void     askFocusStateForPlugin(int pluginId, int focusState);
    Q_INVOKABLE    void     unsetFocusPluginsFromRoom();

private:
    RoomManager(QObject *parent = 0);

    static RoomManager                 *instance;
    static int                                       roomInstances;

    RoomBase                                 *roomPrototype; // ROOM BASE FROM LIBRARY -> ALL CREATED ROOM WILL BE OF THIS TYPE
    RoomBase                                 *currentRoom;   // ROOM IN WHICH WE CURRENTLY ARE
    QTimer                                       *roomUpdateTimer; // TIMER THAT WILL UPDATE ALL OF THE ROOM'S WIDGETS
    Models::SubListedListModel      *roomModel;

    void                    loadRoomLibrary();
    void                    placeNewRoomInSpace();

signals:
    void                    executeSQLQuery(const QString &query, QObject *sender, int id);
};

}

#endif // ROOMMANAGER_H

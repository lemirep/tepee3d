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

#ifndef ROOMLOADER_H
#define ROOMLOADER_H

#include <QHash>
#include <RoomBase.h>
#include <RoomManager.h>
#include <QTextStream>
#include <DatabaseServiceUserInterface.h>


#define FILEHEADER  "__ROOMFILE__"
#define ROOMFILEDIR "./RoomFile/"

#define SEARCH_FOR_ROOM 1
#define GENERIC_RESULT 2
#define RESTORE_ROOMS 3
#define RESTORE_PLUGINS_TO_ROOM 4
#define RESTORE_SKYBOX 5
#define DB_NAME "Tepee3D.sql"

 namespace Room
 {
    class RoomManager;

    class RoomLoader : public QObject, public Services::DatabaseServiceUserInterface
    {
        Q_OBJECT
        Q_INTERFACES(Services::DatabaseServiceUserInterface)

    private:
        RoomLoader(QObject *parent = 0);


        static      RoomLoader*     instance;

        void                        updateExistingRoom(RoomBase *room);
        void                        insertNewRoom(RoomBase *room);
        void                        insertOrReplacePluginsForRoom(RoomBase *room);
        void                        deleteRoom(RoomBase *room);
        void                        saveRoom(RoomBase *room);
        void                        restoreRooms();
        void                        restoreSkyboxPath();
        void                        saveSkyboxPath(const QString &skyboxPath);

        void                        searchForRoomEditUpdateCallback(QList<QSqlRecord> result, QPointer<QObject> data);
        void                        restoreRoomsCallback(QList<QSqlRecord> result, QPointer<QObject> data);
        void                        genericResultCallback(QList<QSqlRecord> result, QPointer<QObject> data);
        void                        restoreWidgetsForRoomCallback(QList<QSqlRecord> result, QPointer<QObject> data);
        void                        restoreSkyboxPathCallBack(QList<QSqlRecord> result,QPointer<QObject> data);

        QHash<int, void (RoomLoader::*)(QList<QSqlRecord> result, QPointer<QObject> data)>   pFunc;

    public :
        static RoomLoader*          getInstance(QObject *parent = 0);
        ~RoomLoader();

         static void                saveRoomToDatabase(Room::RoomBase *room);
         static void                deleteRoomFromDatabase(Room::RoomBase *room);
         static void                restoreRoomsFromDatabase();
         static void                addNewPluginToDatabase(Plugins::PluginBase *plugin);
         static void                restoreSkyboxPathFromDatabase();
         static void                updateSkyboxPathToDatabase(const QString &skyboxPath);

         void                       receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, QPointer<QObject> data);

    signals :
         void                       executeSQLQuery(const QString &query, QObject *sender, int id, const QString &dbName, QPointer<QObject> data = QPointer<QObject>());
    };
 }

#endif // ROOMLOADER_H

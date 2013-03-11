#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include <QTimer>
#include <PluginManager.h>
#include <QVector3D>
#include <qmath.h>
#include "SubListedListModel.h"
#include "RoomModelItem.h"
#include "DatabaseServiceUserInterface.h"


// CREATES ROOM MODEL, RESTORE AND SAVE ROOMS AND EXPOSE THEM TO QML

#define ROOM_UPDATE_TIME 500
#define ROOM_LIBRARY_DIRECTORY "libraries/room_library"


// WHEN CHANGING ROOM IN QML : -> STOP ALL ANIMATION OF CURRENT ROOM'S WIDGETS AND LIVE WIDGET VIEW IF IN IT
//                             -> HIDE ALL ROOM WIDGET
//                             -> SWITCH TO SELECTED ROOM
//                             -> IF THE ROOM'S WIDGETS WERE NOT LOADED BEFORE LOAD THEM AND INITIALIZE THEM
//                             -> SHOW ALL ROOM WIDGET
//                             -> UPDATA ALL OF THE ROOM'S WIDGET

namespace   Room
{
class RoomManager : public QObject, public View::QmlContentExposerInterface, public Services::DatabaseServiceUserInterface
{
    Q_OBJECT
public:
    ~RoomManager();
    static RoomManager*     getInstance(QObject *parent = NULL);
    static Room::RoomBase*   getNewRoomInstance();

    Models::ListModel*      getRoomModel() const;
    void                    addRoomToModel(Room::RoomBase *room);

    Plugins::PluginBase*    getPluginFromRoom(int roomId, int pluginId) const;

    void                    setCurrentRoom(RoomBase *room);
    RoomBase*               getCurrentRoom()    const;

    // QmlContentExposer
    void                    exposeContentToQml(QQmlContext *context);
    // DatabaseUser
    void                    receiveResultFromSQLQuery(QList<QSqlRecord> result, int id);

    // METHODS THAT CAN BE CALLED FROM QML
    Q_INVOKABLE    void     setCurrentRoom(int roomModelId);
    Q_INVOKABLE    void     addNewPluginToCurrentRoom(int pluginModelId);
    Q_INVOKABLE    void     removePluginFromCurrentRoom(int pluginModelId);
    Q_INVOKABLE    void     addNewRoom(QString roomName = "RoomTest-");
    Q_INVOKABLE    void     deleteRoom(int roomModelId);
    Q_INVOKABLE    void     editRoom(int roomModelId, QString roomName, QVector3D roomPosition, QVector3D roomScale);
    Q_INVOKABLE    void     unsetFocusPluginsFromRoom();

private:
    RoomManager(QObject *parent = 0);

    static RoomManager      *instance;
    static int              roomInstances;
    static QString          selectRoomsQuery;
    static QString          insertRoomQuery;
    static QString          updateRoomQuery;
    static QString          deleteRoomQuery;

    RoomBase                *roomPrototype; // ROOM BASE FROM LIBRARY -> ALL CREATED ROOM WILL BE OF THIS TYPE
    RoomBase                *currentRoom;   // ROOM IN WHICH WE CURRENTLY ARE
    QTimer                  *roomUpdateTimer; // TIMER THAT WILL UPDATE ALL OF THE ROOM'S WIDGETS
    Models::SubListedListModel      *roomModel;

    void                    loadRoomLibrary();
    void                    placeNewRoomInSpace();

signals:
    void                    executeSQLQuery(const QString &query, QObject *sender, int id);
};

}

#endif // ROOMMANAGER_H

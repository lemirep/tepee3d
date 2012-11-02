#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include <QTimer>
#include <PluginManager.h>
#include "QmlContentExposerInterface.h"
#include "ListModel.h"
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
class RoomManager : public QObject, public QmlContentExposerInterface, public DatabaseServiceUserInterface
{
    Q_OBJECT
public:
    RoomManager(QObject *parent = 0);
    ~RoomManager();

    ListModel*      getRoomModel() const;
    bool            addRoomToModel();

    RoomBase*       getCurrentRoom()    const;
    void            setCurrentRoom(RoomBase *room);
    // QmlContentExposer
    void            exposeContentToQml(QQmlContext *context);
    // DatabaseUser
    void            receiveResultFromSQLQuery(const QList<QSqlRecord> &result);


    // METHODS THAT CAN BE CALLED FROM QML
    Q_INVOKABLE    void     setCurrentRoom(int roomModelId);
    Q_INVOKABLE    void     addNewRoom();
    Q_INVOKABLE    void     addNewPluginToCurrentRoom(int pluginModelId);

private:
    ListModel       *roomModel;
    ListModel       *currentRoomPluginsModel;
    RoomBase        *roomPrototype; // ROOM BASE FROM LIBRARY -> ALL CREATED ROOM WILL BE OF THIS TYPE
    RoomBase        *currentRoom;   // ROOM IN WHICH WE CURRENTLY ARE
    QTimer          *roomUpdateTimer; // TIMER THAT WILL UPDATE ALL OF THE ROOM'S WIDGETS

    void            loadRoomLibrary();

signals:
    void    executeSQLQuery(const QString &query, QObject *sender);
    void    connectObjectToServices(QObject *serviceUser);
    void    disconnectObjectFromServices(QObject *serviceUser);
};

}

#endif // ROOMMANAGER_H

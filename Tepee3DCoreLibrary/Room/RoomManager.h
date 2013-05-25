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

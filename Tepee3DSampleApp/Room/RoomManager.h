#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include <QTimer>
#include <PluginLoader.h>
#include "QmlContentExposerInterface.h"
#include "ListModel.h"
#include "RoomModelItem.h"
#include "DatabaseServiceUserInterface.h"

// CREATES ROOM MODEL, RESTORE AND SAVE ROOMS AND EXPOSE THEM TO QML

#define ROOM_UPDATE_TIME 500
#define ROOM_LIBRARY_DIRECTORY "libraries/room_library"

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
Q_INVOKABLE    void     setCurrentRoom(int roomId);



private:
    ListModel       *roomModel;
    RoomBase        *roomPrototype;
    RoomBase        *currentRoom;
    QTimer          *roomUpdateTimer;

    void            loadRoomLibrary();

signals:
    void executeSQLQuery(const QString &query, QObject *sender);
};

}

#endif // ROOMMANAGER_H

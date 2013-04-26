#ifndef BASICROOM_H
#define BASICROOM_H

#include <QQmlEngine>
#include <QVector3D>
#include <PluginModelItem.h>
#include "RoomBase.h"

#define BASICROOM_QML_FILE "Room.qml"

class BasicRoom : public Room::RoomBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.tepee3d.Room.BasicRoom")

private:

public:
    BasicRoom();
    ~BasicRoom();

    QObject*                        getObject();
    Room::RoomBase*                 createNewInstance();

public slots:
    void                            updateRoom();

};

#endif // BASICROOM_H

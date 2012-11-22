#ifndef BASICROOM_H
#define BASICROOM_H

#include <QQmlEngine>
#include <Qt/qvector3d.h>
#include <iostream>
#include "RoomBase.h"

#define BASICROOM_QML_FILE "Room.qml"

class BasicRoom : public Room::RoomBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.tepee3d.Room.basicroom")

private:

public:
    BasicRoom();
    ~BasicRoom();


    QObject*                        getObject();
    QQuickItem*                     getRoomQmlObject()  const;
    Room::RoomBase*                 createNewInstance();

public slots:
    void                            updateRoom();

private:



};

#endif // BASICROOM_H

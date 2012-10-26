#ifndef BASICROOM_H
#define BASICROOM_H

#include <Qt/qqmlengine.h>
#include <Qt/qvector3d.h>
#include <iostream>
#include "RoomBase.h"


class BasicRoom : public Room::RoomBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.tepee3d.Room.basicroom")

private:

    QQuickItem*                 roomQmlItem;
    QQuickItem*                 parentQmlItem;
    QQmlEngine*                 engine;

    QString                     roomName;
    QString                     qmlFile;
    QList<Plugins::PluginBase*>          widgets;

    QVector3D                   position;
    QVector3D                   scale;
    QVector3D                   roomCenter;

    void                        updateRoomCenter();

    static  int                 nextId;

public:
//    explicit BasicRoom(QQuickItem* parentQmlObject = 0, QQmlEngine* engine = 0, QString roomName = "", QVector3D position = QVector3D(), QVector3D scale = QVector3D());
    BasicRoom();
    ~BasicRoom();

    QString                     getRoomQml()        const;
    QString                     getRoomName()       const;

    QVector3D                   getPosition()       const;
    QVector3D                   getScale()          const;
    QVector3D                   getRoomCenter()     const;

    QObject*                    getObject();
    QQuickItem*                 getRoomQmlObject()  const;
    QList<Plugins::PluginBase*>          getWidgetsList()    const;

    void                        setScale(QVector3D scale);
    void                        setRoomName(QString name);
    void                        setPosition(QVector3D position);
    void                        addWidgetToRoom(Plugins::PluginBase *);

    Room::RoomBase*             createNewInstance();

public slots:
    void                        updateRoom();

private:



};

#endif // BASICROOM_H

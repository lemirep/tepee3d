#ifndef ROOMBASE_H
#define ROOMBASE_H

#include <QObject>
#include <QVector3D>
#include <QQuickItem>
#include "PluginBase.h"
#include "RoomInterface.h"
#include "ListModel.h"
#include "PluginModelItem.h"

namespace Room
{

class RoomBase : public QObject, Room::RoomInterface
{
    Q_OBJECT
    Q_INTERFACES(Room::RoomInterface)

protected:
    static int                      nextId;

    int                             roomId;
    QString                         roomName;
    QString                         roomQmlFile;
    QVector3D                       position;
    QVector3D                       scale;
    QVector3D                       roomCenter;

    QList<Plugins::PluginBase*>     widgets;

public:
    RoomBase();


    int                                     getRoomId()        const;
    RoomBase*                               getRoomBase();

    virtual QString                         getRoomName()      const;
    virtual QString                         getRoomQmlFile()   const;

    virtual QVector3D                       getPosition()      const;
    virtual QVector3D                       getScale()         const;
    virtual QVector3D                       getRoomCenter()    const;

    virtual void                            setScale(const QVector3D& scale);
    virtual void                            setRoomName(const QString& name);
    virtual void                            setPosition(const QVector3D& position);
    virtual void                            setRoomQmlFile(const QString &file);
    virtual void                            addWidgetToRoom(Plugins::PluginBase *widget);
    virtual QList<Plugins::PluginBase *>    getWidgetsList()   const;

    virtual RoomBase*               createNewInstance()      = 0;
    virtual QObject*                getObject()              = 0;
    virtual QQuickItem*             getRoomQmlObject() const = 0;

signals :


public slots :
    virtual void                    updateRoom();


};

}

#endif // ROOMBASE_H

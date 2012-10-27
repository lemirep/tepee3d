#ifndef ROOMBASE_H
#define ROOMBASE_H

#include <QObject>
#include <QVector3D>
#include "PluginBase.h"
#include "RoomInterface.h"

namespace Room
{

class RoomBase : public QObject, Room::RoomInterface
{
    Q_OBJECT
    Q_INTERFACES(Room::RoomInterface)

protected:
    static int                      id;
    int                             roomId;

public:
    RoomBase();

    RoomBase*                       getRoomBase();

    int                             getRoomId()        const;

    virtual RoomBase*               createNewInstance()      = 0;
    virtual QString                 getRoomName()      const = 0;
    virtual QString                 getRoomQml()       const = 0;

    virtual QVector3D               getPosition()      const = 0;
    virtual QVector3D               getScale()         const = 0;
    virtual QVector3D               getRoomCenter()    const = 0;

    virtual QObject*                getObject()              = 0;
    virtual QQuickItem*             getRoomQmlObject() const = 0;

    virtual QList<Plugins::PluginBase *>     getWidgetsList()   const = 0;

    virtual void                    setScale(const QVector3D& scale)         = 0;
    virtual void                    setRoomName(const QString& name)         = 0;
    virtual void                    setPosition(const QVector3D& position)   = 0;
    virtual void                    addWidgetToRoom(Plugins::PluginBase *) = 0;

signals :


public slots :
    virtual void                    updateRoom();


};

}

#endif // ROOMBASE_H

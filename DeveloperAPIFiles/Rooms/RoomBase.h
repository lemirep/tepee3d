#ifndef ROOMBASE_H
#define ROOMBASE_H

#include <QObject>
#include <QVector3D>
#include <QQuickItem>
#include "PluginBase.h"
#include "RoomInterface.h"
#include "RoomProperties.h"
#include "ListModel.h"
#include "PluginModelItem.h"

namespace Room
{

class RoomBase : public QQuickItem, Room::RoomInterface
{
    Q_OBJECT
    Q_INTERFACES(Room::RoomInterface)
    Q_PROPERTY (QString roomName READ getRoomName WRITE setRoomName)
    Q_PROPERTY (int     roomId   READ getRoomId)
//    Q_PROPERTY (ListModel* roomPluginsModel READ getRoomPluginsModel)

protected:
    static int                      nextId;
    int                             roomId;

    QString                         roomQmlFile;
    Room::RoomProperties            *roomProperties;

public:
    RoomBase();


    int                                     getRoomId()        const;
    RoomBase*                               getRoomBase();

    virtual bool                            operator >(RoomBase *room) const;
    virtual bool                            operator <(RoomBase *room) const;
    virtual double                          getRoomVolume()    const;

    virtual QString                         getRoomName()      const;
    virtual QString                         getRoomQmlFile()   const;

    virtual QVector3D                       getPosition()      const;
    virtual QVector3D                       getScale()         const;

    virtual void                            setScale(const QVector3D& scale);
    virtual void                            setRoomName(const QString& name);
    virtual void                            setPosition(const QVector3D& position);

    virtual void                            setRoomQmlFile(const QString &file);
    virtual void                            addWidgetToRoom(Plugins::PluginBase *widget);

//    virtual QList<Plugins::PluginBase *>    getWidgetsList()   const;

    virtual ListModel*                      getRoomPluginsModel() const;

    virtual Room::RoomProperties*            getRoomProperties() const;



    virtual RoomBase*               createNewInstance() = 0;
    virtual QObject*                getObject()         = 0;

signals :


public slots :
    virtual void                    updateRoom();


};

}

#endif // ROOMBASE_H

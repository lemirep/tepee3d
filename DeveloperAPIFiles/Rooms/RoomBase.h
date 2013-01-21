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

protected:
    static int                      nextId;
    int                             roomId;

    QString                         roomQmlFile;
    Room::RoomProperties            *roomProperties;

public:
    RoomBase();
    ~RoomBase();

    int                                     getRoomId()        const;
    RoomBase*                               getRoomBase();

    void                                    setRoomQmlFile(const QString &file);
    void                                    addWidgetToRoom(Plugins::PluginBase *widget);
    void                                    removeWidgetFromRoom(Plugins::PluginBase *widget);

    void                                    enterRoom();
    void                                    leaveRoom();

    ListModel*                              getRoomPluginsModel() const;
    Plugins::PluginBase*                    getPluginFromRoom(int pluginId) const;
    Room::RoomProperties*                   getRoomProperties() const;

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

    virtual RoomBase*                       createNewInstance() = 0;
    virtual QObject*                        getObject()         = 0;


signals :

    void                                    roomEntered();
    void                                    roomLeft();

public slots :
    virtual void                            updateRoom();
    virtual void                            focusStateChangeRequest(Plugins::PluginEnums::PluginState, QObject*);

};

}

#endif // ROOMBASE_H

#ifndef ROOMMODELITEM_H
#define ROOMMODELITEM_H

#include "SubListedListItem.h"
#include "RoomBase.h"

namespace   Room
{

class RoomModelItem : public Models::SubListedListItem
{
    Q_OBJECT
public:

    enum    RoomModelItemRoles
    {
        roomId  =   Qt::UserRole + 1,
        roomPosition,
        roomScale,
        roomName,
        roomQmlFile
    };



    explicit RoomModelItem(Room::RoomBase *room, QObject *parent = 0);
    ~RoomModelItem();

    int                     id()                const;
    QVariant                data(int role)      const;
    QHash<int, QByteArray>  roleNames()         const;

    Room::RoomBase*         getRoom()           const;
    Models::ListModel*      submodel()          const;

private:
    Room::RoomBase               *room;

};

}
#endif // ROOMMODELITEM_H

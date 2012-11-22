#ifndef ROOMMODELITEM_H
#define ROOMMODELITEM_H

#include "ListItem.h"
#include "RoomBase.h"

namespace   Room
{

class RoomModelItem : public ListItem
{
    Q_OBJECT
public:

    enum    RoomModelItemRoles
    {
        roomId  =   Qt::UserRole + 1,
        roomPosition,
        roomScale,
        roomName,
        roomCenter,
        roomQmlFile
    };



    explicit RoomModelItem(Room::RoomBase *room, QObject *parent = 0);
    ~RoomModelItem();

    int                     id()                const;
    QVariant                data(int role)      const;
    QHash<int, QByteArray>  roleNames()         const;

    Room::RoomBase               *getRoom()  const;
    void                         triggerItemUpdate();

private:
    Room::RoomBase               *room;

};

}
#endif // ROOMMODELITEM_H

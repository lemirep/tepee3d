#ifndef ROOMINTERFACE_H
#define ROOMINTERFACE_H

namespace  Room
{

class RoomBase;

class RoomInterface
{
public :
    virtual RoomBase*   getRoomBase() = 0;
};

}
// REGISTER INTERFACE TO QT
Q_DECLARE_INTERFACE(Room::RoomInterface, "com.tepee3d.Room.RoomInterface/1.0")

#endif // ROOMINTERFACE_H

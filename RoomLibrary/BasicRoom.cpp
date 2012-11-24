#include "BasicRoom.h"
//DEBUG
#include <QDebug>


BasicRoom::BasicRoom() : RoomBase()
{

}

BasicRoom::~BasicRoom()
{
}

Room::RoomBase*  BasicRoom::createNewInstance()
{
    BasicRoom* room = new BasicRoom();
    room->setRoomQmlFile(BASICROOM_QML_FILE);
    return room;
}

QObject*    BasicRoom::getObject()
{
    return this;
}

void    BasicRoom::updateRoom()
{
   // qDebug() << "Updating " << this->getRoomName();
    foreach (Plugins::PluginBase* plugin, this->widgets)
    {
      //  qDebug() << "Updating " << plugin->getPluginName();
    }
}

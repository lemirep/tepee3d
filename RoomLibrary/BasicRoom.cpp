#include "BasicRoom.h"
//DEBUG
#include <QDebug>


BasicRoom::BasicRoom() : RoomBase()
{
    // REGISTER TYPE TO QML ENGINE SO ELEMENT CAN BE USED
//    qmlRegisterType<BasicRoom>("Room", 1, 0, "RoomProperties");
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
//    foreach (Plugins::PluginBase* plugin, this->getWidgetsList())
//    {
      //  qDebug() << "Updating " << plugin->getPluginName();
//    }
}

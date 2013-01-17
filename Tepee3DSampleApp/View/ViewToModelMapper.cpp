#include "ViewToModelMapper.h"

View::ViewToModelMapper::ViewToModelMapper(QObject *parent): QObject(parent)
{
}

Plugins::PluginBase*    View::ViewToModelMapper::getPluginFromRoom(int roomId, int pluginId)
{
    return Room::RoomManager::getInstance()->getPluginFromRoom(roomId, pluginId);
}

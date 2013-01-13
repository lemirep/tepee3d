#include "RoomProperties.h"

Room::RoomProperties::RoomProperties(QObject *parent) : QObject(parent)
{
    this->pluginsModel = new ListModel(new Plugins::PluginModelItem(NULL, NULL));
}

Room::RoomProperties::~RoomProperties()
{
}

QString     Room::RoomProperties::getRoomName() const
{
    return this->roomName;
}

QVector3D   Room::RoomProperties::getPosition() const
{
    return this->position;
}

QVector3D   Room::RoomProperties::getScale() const
{
    return this->scale;
}

ListModel*   Room::RoomProperties::getRoomPluginsModel() const
{
    return this->pluginsModel;
}

void        Room::RoomProperties::setRoomName(const QString &name)
{
    this->roomName = name;
}

void        Room::RoomProperties::setPosition(const QVector3D &position)
{
    this->position = position;
}

void        Room::RoomProperties::setScale(const QVector3D &scale)
{
    this->scale = scale;
}

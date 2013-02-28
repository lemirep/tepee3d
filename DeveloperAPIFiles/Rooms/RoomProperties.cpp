#include "RoomProperties.h"

/*!
 * \class Room::RoomProperties
 *
 * \brief The Room::RoomProperties class contains all the attributes
 * that define a room.
 *
 * \sa Room::RoomBase
 */


Room::RoomProperties::RoomProperties(QObject *parent) : QObject(parent)
{
    this->pluginsModel = new ListModel(new Plugins::PluginModelItem(NULL, NULL));
}

Room::RoomProperties::~RoomProperties()
{
}

/*!
 * Returns the room´s name.
 */
QString     Room::RoomProperties::getRoomName() const
{
    return this->roomName;
}

/*!
 * Returns a 3D vector containing the room´s position.
 */
QVector3D   Room::RoomProperties::getPosition() const
{
    return this->position;
}

/*!
 * Returns a 3D vector containing the room´s scale.
 */
QVector3D   Room::RoomProperties::getScale() const
{
    return this->scale;
}

/*!
 * Returns ListModel containing the room´s plugins model.
 */
ListModel*   Room::RoomProperties::getRoomPluginsModel() const
{
    return this->pluginsModel;
}

/*!
 * Sets the room´s name to name.
 */
void        Room::RoomProperties::setRoomName(const QString &name)
{
    this->roomName = name;
}

/*!
 * Sets the room´s position to position.
 */
void        Room::RoomProperties::setPosition(const QVector3D &position)
{
    this->position = position;
}

/*!
 * Sets the room´s scale to scale.
 */
void        Room::RoomProperties::setScale(const QVector3D &scale)
{
    this->scale = scale;
}

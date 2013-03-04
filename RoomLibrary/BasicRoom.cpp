#include "BasicRoom.h"
//DEBUG
#include <QDebug>

/*!
 * \class BasicRoom
 * \code
 * #include <BasicRoom.h>
 * \endcode
 * \brief The BasicRoom::BasicRoom class is simplest implementation of the RoomBase
 *
 * The BasicRoom class represents a squared room. It is compiled in a shared library
 * and then dynamically loaded in the Tepee3DEngine at runtime.
 *
 * \sa Room::RoomBase
 */

/*!
 * Constructs a new BasicRoom. This method being private cannot be called
 * directly.
 * \sa Room::RoomBase* BasicRoom::createNewInstance()
 */
BasicRoom::BasicRoom() : RoomBase()
{
    // REGISTER TYPE TO QML ENGINE SO ELEMENT CAN BE USED
//    qmlRegisterType<BasicRoom>("Room", 1, 0, "RoomProperties");
}

/*!
 * Destroys a BasicRoom instance.
 */
BasicRoom::~BasicRoom()
{
}

/*!
 * Returns a new BasicRoom instance properly initialised.
 */
Room::RoomBase*  BasicRoom::createNewInstance()
{
    BasicRoom* room = new BasicRoom();
    room->setRoomQmlFile(BASICROOM_QML_FILE);
    return room;
}

/*!
 * Returns the current instance as a QObject for signals manipulations.
 */
QObject*    BasicRoom::getObject()
{
    return this;
}

/*!
 * Triggered when the room becomes the current room to update the plugins it contains
 */
void    BasicRoom::updateRoom()
{
   // qDebug() << "Updating " << this->getRoomName();
//    foreach (Plugins::PluginBase* plugin, this->getWidgetsList())
//    {
      //  qDebug() << "Updating " << plugin->getPluginName();
//    }
}

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
 *
 *  \inmodule Tepee3D
 */

/*!
 * Constructs a new BasicRoom. This method being private cannot be called
 * directly.
 * \sa createNewInstance()
 */
BasicRoom::BasicRoom() : RoomBase()
{
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
    foreach (Models::ListItem* pluginItem, this->getRoomPluginsModel()->toList())
    {
        Plugins::PluginBase *plugin = NULL;
        if ((plugin = reinterpret_cast<Models::PluginModelItem *>(pluginItem)->getPlugin()) != NULL &&
                plugin->needsUpdating())
            plugin->updatePlugin();
    }
}

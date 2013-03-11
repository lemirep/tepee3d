#include "ViewToModelMapper.h"

/*!
 * \class View::ViewToModelMapp
 *
 * \code
 * #include <ViewToModelMapper.h>
 * \endcode
 *
 * \brief The View::ViewToModelMapper is used internally to perform linking between
 * custom C++ QML components and other C++ modules. For pure QML component Q_INVOKABLE methods
 * fit better.
 *
 * \inmodule Tepee3D
 *
 */

/*!
 * Constructs a new View::ViewToModelMapper instance with the optionnal \a parent.
 */

View::ViewToModelMapper::ViewToModelMapper(QObject *parent): QObject(parent)
{
}

/*!
 * Returns a plugin given its \a roomId and its \a pluginId.
 */

Plugins::PluginBase*    View::ViewToModelMapper::getPluginFromRoom(int roomId, int pluginId)
{
    return Room::RoomManager::getInstance()->getPluginFromRoom(roomId, pluginId);
}

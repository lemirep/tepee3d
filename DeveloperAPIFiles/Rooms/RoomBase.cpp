#include "RoomBase.h"
// DEBUG
#include <QDebug>

/*!
 * \class Room::RoomBase
 *
 * \brief The Room::RoomBase class is the base class a Tepee3D room has to
 * inherit from. It provided the application informations about the room
 * such as its position, its volume and its scale as well as the various
 * methods needed to interact with the widgets in the room.
 *
 * \sa Room::RoomProperties
 */


int Room::RoomBase::nextId = 0;

Room::RoomBase::RoomBase() : QQuickItem()
{
    this->roomId = Room::RoomBase::nextId++;
    this->roomProperties = new Room::RoomProperties(this);
}

Room::RoomBase::~RoomBase()
{
}

/*!
 * Returns the room´s id.
 */
int         Room::RoomBase::getRoomId() const
{
    return this->roomId;
}

/*!
 * Returns the room instance.
 */
Room::RoomBase*   Room::RoomBase::getRoomBase()
{
    return this;
}

/*!
 * Returns the room´s volume.
 */
double            Room::RoomBase::getRoomVolume() const
{
    QVector3D scale = this->getScale();

    return scale.x() * scale.y() * scale.z();
}

/*!
 * Returns true if the current room´s volume is inferior to room´s volume.
 */
bool            Room::RoomBase::operator <(RoomBase *room) const
{
    return this->getRoomVolume() < room->getRoomVolume();
}

/*!
 * Returns true if the current room´s volume is superior to room´s volume.
 */
bool            Room::RoomBase::operator >(RoomBase *room) const
{
    return this->getRoomVolume() > room->getRoomVolume();
}

/*!
 * Returns true if the current room collides with room.
 */
bool            Room::RoomBase::collides(RoomBase *room) const
{
    QVector3D   minRoomA = this->getMinBoundingPoint();
    QVector3D   maxRoomA = this->getMaxBoundingPoint();
    QVector3D   minRoomB = room->getMinBoundingPoint();
    QVector3D   maxRoomB = room->getMaxBoundingPoint();

    if (minRoomA.x() < maxRoomB.x() && maxRoomA.x() > minRoomB.x()
            && minRoomA.y() < maxRoomB.y() && maxRoomA.y() > minRoomB.y()
            && minRoomA.z() < maxRoomB.z() && maxRoomA.z() > minRoomB.z())
        return true;
    return false;
}

/*!
 * Returns the room´s name.
 */
QString     Room::RoomBase::getRoomName() const
{
    return this->roomProperties->getRoomName();
}

/*!
 * Returns the room´s QML file which is its representation in the 3D world.
 */
QString     Room::RoomBase::getRoomQmlFile() const
{
    return this->roomQmlFile;
}

/*!
 * Returns a 3D vector containing the room´s position.
 */
QVector3D   Room::RoomBase::getPosition() const
{
    return this->roomProperties->getPosition();
}

/*!
 * Returns a 3D vector containing the room´s scale.
 */
QVector3D   Room::RoomBase::getScale() const
{
    return this->roomProperties->getScale();
}

/*!
 * Returns a 3D vector containing the room´s minimum bounding points.
 */
QVector3D   Room::RoomBase::getMinBoundingPoint() const
{
    // POSITION IS THE CENTER OF THE ROOM
    QVector3D pos = this->roomProperties->getPosition();
    QVector3D scale = this->roomProperties->getScale();
    return QVector3D(pos.x() - (scale.x() / 2),
                     pos.y() - (scale.y() / 2),
                     pos.z() - (scale.z() / 2));
}

/*!
 * Returns a 3D vector containing the room´s maximum bounding points.
 */
QVector3D   Room::RoomBase::getMaxBoundingPoint() const
{
    // POSITION IS THE CENTER OF THE ROOM
    QVector3D pos = this->roomProperties->getPosition();
    QVector3D scale = this->roomProperties->getScale();
    return QVector3D(pos.x() + (scale.x() / 2),
                     pos.y() + (scale.y() / 2),
                     pos.z() + (scale.z() / 2));
}

/*!
 * Returns the model containing plugins of the current room.
 */
ListModel*  Room::RoomBase::getRoomPluginsModel()   const
{
    return this->roomProperties->getRoomPluginsModel();
}

/*!
 * Sets scale as the room´s scale.
 */
void        Room::RoomBase::setScale(const QVector3D &scale)
{
    this->roomProperties->setScale(scale);
}

/*!
 * Sets name as the room´s name.
 */
void        Room::RoomBase::setRoomName(const QString &name)
{
    this->roomProperties->setRoomName(name);
}

/*!
 * Sets position as the room´s position.
 */
void        Room::RoomBase::setPosition(const QVector3D &position)
{
    this->roomProperties->setPosition(position);
}

/*!
 * Sets file as the room´s qml representation file.
 */
void        Room::RoomBase::setRoomQmlFile(const QString &file)
{
    this->roomQmlFile = file;
}

/*!
 * Adds a new plugin to the room. Signals connections for the plugins are handled there as well.
 */
void        Room::RoomBase::addWidgetToRoom(Plugins::PluginBase *widget)
{
    QObject::connect(this, SIGNAL(roomEntered()), widget, SIGNAL(roomEntered()));
    QObject::connect(this, SIGNAL(roomLeft()), widget, SIGNAL(roomLeft()));
    QObject::connect(widget, SIGNAL(askForFocusState(Plugins::PluginEnums::PluginState,QObject*)),
                     this, SLOT(focusStateChangeRequest(Plugins::PluginEnums::PluginState, QObject*)));
    this->roomProperties->getRoomPluginsModel()->appendRow(new Plugins::PluginModelItem(widget));
}

/*!
 * Removes the plugin widget from the current room, disconnecting signals as well.
 */
void        Room::RoomBase::removeWidgetFromRoom(Plugins::PluginBase *widget)
{
    QObject::disconnect(this, SIGNAL(roomEntered()), widget, SIGNAL(roomEntered()));
    QObject::disconnect(this, SIGNAL(roomLeft()), widget, SIGNAL(roomLeft()));
    QObject::disconnect(widget, SIGNAL(askForFocusState(Plugins::PluginEnums::PluginState,QObject*)),
                        this, SLOT(focusStateChangeRequest(Plugins::PluginEnums::PluginState, QObject*)));
}

/*!
 * Triggered every second by a timer, the room can update its plugins there. It is triggered only
 * if the room is the currently selected room in the visual interface.
 */
void        Room::RoomBase::updateRoom()
{
    // FOR LOGICAL UPDATE ONLY HAPPENS EVERY HALF SECONDS
    // IF YOU NEED TO UPDATE THE VIEW, USE A TIMER IN YOUR PLUGIN WITH A 50MS DURATION
    qDebug() << "Room is updated -> but you should should have implemented this method in the room subclass";
}

/*!
 * Returns the properties of the room.
 */
Room::RoomProperties*    Room::RoomBase::getRoomProperties() const
{
    return this->roomProperties;
}

/*!
 * Returns the plugin identified by pluginId if it is in the current room.
 * Otherwise, a NULL pointer is returned.
 */

Plugins::PluginBase*    Room::RoomBase::getPluginFromRoom(int pluginId) const
{
    Plugins::PluginModelItem* pluginItem = NULL;

    if ((pluginItem = (Plugins::PluginModelItem *)this->roomProperties->getRoomPluginsModel()->find(pluginId)) != NULL)
        return pluginItem->getPlugin();
    return NULL;
}

/*!
 * Slot triggered when the room become the currently selected room in the interface.
 */
void        Room::RoomBase::enterRoom()
{
    emit (roomEntered());
}

/*!
 * Slot triggered when the room which was the currently selected room is unselected.
 */
void        Room::RoomBase::leaveRoom()
{
    emit (roomLeft());
}

/*!
 * Handles plugin´s focusState change requests, if no action is againt the request, the focusState is granted to the
 * plugin. Otherwise the focusState of the plugin is not changed.
 */

void        Room::RoomBase::focusStateChangeRequest(Plugins::PluginEnums::PluginState requestedState, QObject* sender)
{
    Plugins::PluginBase*   plugin = NULL;
    Plugins::PluginBase*   requester = (Plugins::PluginBase*)sender;
    bool                   requestAccepted = true;

    // IF THERE IS ANOTHER ITEM IN SELECTED -> ACCEPT AND SET OTHER ITEM TO IDLE
    // IF THERE IS ANOTHER ITEM IN FOCUS -> REFUSE AND DO NOT MODIFY ANY WIDGET
    foreach (ListItem* pluginItem, this->roomProperties->getRoomPluginsModel()->toList())
    {
        plugin = ((Plugins::PluginModelItem*)(pluginItem))->getPlugin();
        if (plugin != requester && plugin->getFocusState() != Plugins::PluginEnums::pluginIdleState)
        {
            if (plugin->getFocusState() == Plugins::PluginEnums::pluginFocusedState)
                plugin->setFocusState(Plugins::PluginEnums::pluginIdleState);
            else if (plugin->getFocusState() == Plugins::PluginEnums::pluginSelectedState)
                requestAccepted = false;
            break;
        }
    }
    if (requestAccepted)
        requester->setFocusState(requestedState);
}

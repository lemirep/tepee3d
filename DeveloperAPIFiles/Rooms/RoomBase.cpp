#include "RoomBase.h"
// DEBUG
#include <QDebug>

/*!
 * \class Room::RoomBase
 *
 * \brief The Room::RoomBase class is the base class a Tepee3D has to
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

int         Room::RoomBase::getRoomId() const
{
    return this->roomId;
}

Room::RoomBase*   Room::RoomBase::getRoomBase()
{
    return this;
}

double            Room::RoomBase::getRoomVolume() const
{
    QVector3D scale = this->getScale();

    return scale.x() * scale.y() * scale.z();
}

bool            Room::RoomBase::operator <(RoomBase *room) const
{
    return this->getRoomVolume() < room->getRoomVolume();
}

bool            Room::RoomBase::operator >(RoomBase *room) const
{
    return this->getRoomVolume() > room->getRoomVolume();
}

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

QString     Room::RoomBase::getRoomName() const
{
    return this->roomProperties->getRoomName();
}

QString     Room::RoomBase::getRoomQmlFile() const
{
    return this->roomQmlFile;
}

QVector3D   Room::RoomBase::getPosition() const
{
    return this->roomProperties->getPosition();
}

QVector3D   Room::RoomBase::getScale() const
{
    return this->roomProperties->getScale();
}

QVector3D   Room::RoomBase::getMinBoundingPoint() const
{
    // POSITION IS THE CENTER OF THE ROOM
    QVector3D pos = this->roomProperties->getPosition();
    QVector3D scale = this->roomProperties->getScale();
    return QVector3D(pos.x() - (scale.x() / 2),
                     pos.y() - (scale.y() / 2),
                     pos.z() - (scale.z() / 2));
}

QVector3D   Room::RoomBase::getMaxBoundingPoint() const
{
    // POSITION IS THE CENTER OF THE ROOM
    QVector3D pos = this->roomProperties->getPosition();
    QVector3D scale = this->roomProperties->getScale();
    return QVector3D(pos.x() + (scale.x() / 2),
                     pos.y() + (scale.y() / 2),
                     pos.z() + (scale.z() / 2));
}

ListModel*  Room::RoomBase::getRoomPluginsModel()   const
{
    return this->roomProperties->getRoomPluginsModel();
}

void        Room::RoomBase::setScale(const QVector3D &scale)
{
    this->roomProperties->setScale(scale);
}

void        Room::RoomBase::setRoomName(const QString &name)
{
    this->roomProperties->setRoomName(name);
}

void        Room::RoomBase::setPosition(const QVector3D &position)
{
    this->roomProperties->setPosition(position);
}

void        Room::RoomBase::setRoomQmlFile(const QString &file)
{
    this->roomQmlFile = file;
}

void        Room::RoomBase::addWidgetToRoom(Plugins::PluginBase *widget)
{
    QObject::connect(this, SIGNAL(roomEntered()), widget, SIGNAL(roomEntered()));
    QObject::connect(this, SIGNAL(roomLeft()), widget, SIGNAL(roomLeft()));
    QObject::connect(widget, SIGNAL(askForFocusState(Plugins::PluginEnums::PluginState,QObject*)),
                     this, SLOT(focusStateChangeRequest(Plugins::PluginEnums::PluginState, QObject*)));
    this->roomProperties->getRoomPluginsModel()->appendRow(new Plugins::PluginModelItem(widget));
}

void        Room::RoomBase::removeWidgetFromRoom(Plugins::PluginBase *widget)
{
    QObject::disconnect(this, SIGNAL(roomEntered()), widget, SIGNAL(roomEntered()));
    QObject::disconnect(this, SIGNAL(roomLeft()), widget, SIGNAL(roomLeft()));
    QObject::disconnect(widget, SIGNAL(askForFocusState(Plugins::PluginEnums::PluginState,QObject*)),
                        this, SLOT(focusStateChangeRequest(Plugins::PluginEnums::PluginState, QObject*)));
}

void        Room::RoomBase::updateRoom()
{
    // FOR LOGICAL UPDATE ONLY HAPPENS EVERY HALF SECONDS
    // IF YOU NEED TO UPDATE THE VIEW, USE A TIMER IN YOUR PLUGIN WITH A 50MS DURATION
    qDebug() << "Room is updated -> but you should should have implemented this method in the room subclass";
}

Room::RoomProperties*    Room::RoomBase::getRoomProperties() const
{
    return this->roomProperties;
}

Plugins::PluginBase*    Room::RoomBase::getPluginFromRoom(int pluginId) const
{
    Plugins::PluginModelItem* pluginItem = NULL;

    if ((pluginItem = (Plugins::PluginModelItem *)this->roomProperties->getRoomPluginsModel()->find(pluginId)) != NULL)
        return pluginItem->getPlugin();
    return NULL;
}

void        Room::RoomBase::enterRoom()
{
    emit (roomEntered());
}

void        Room::RoomBase::leaveRoom()
{
    emit (roomLeft());
}

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

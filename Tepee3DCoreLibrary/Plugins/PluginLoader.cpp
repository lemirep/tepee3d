/****************************************************************************
**
** Copyright (C) Paul Lemire, Tepee3DTeam and/or its subsidiary(-ies).
** Contact: paul.lemire@epitech.eu
** Contact: tepee3d_2014@labeip.epitech.eu
**
** This file is part of the Tepee3D project
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
****************************************************************************/

#include "PluginLoader.h"
// DEBUG
#include <QDebug>

/*!
 * \class Plugins::PluginLoader
 * \brief The Plugins::PluginLoader class is an utility static class
 * aimed at easing the process of loading plugin libraries. It loads all
 * the local plugin libraries in a list. That list can later be used to
 * instantiate new plugin instances.
 *
 * \since 1.0
 *
 * \inmodule Tepee3D
 */


/*!
 * This methods loads all the local libraries found in the Tepee3D plugin forlder.
 * Each library is checked to see whether it is a valid plugin or not, if it´s the
 * case an instance of the given plugin is saved in a list.
 */

Plugins::PluginLoader*   Plugins::PluginLoader::instance = NULL;
QList<Plugins::PluginBase *> Plugins::PluginLoader::widgetPlugins = QList<Plugins::PluginBase *>();

Plugins::PluginLoader::PluginLoader(QObject *parent) : QObject(parent)
{
}

Plugins::PluginLoader::~PluginLoader()
{
}


Plugins::PluginLoader*   Plugins::PluginLoader::getInstance(QObject *parent)
{
    if (Plugins::PluginLoader::instance == NULL)
        Plugins::PluginLoader::instance = new Plugins::PluginLoader(parent);
    return Plugins::PluginLoader::instance;
}

void Plugins::PluginLoader::addPluginToRoom(Plugins::PluginBase *plugin, Room::RoomBase *room)
{
    if (room != NULL && plugin != NULL)
    {
        qDebug() << "Adding new plugin to Room";
        Plugins::PluginManager::initRoomPlugin(plugin);
        room->addWidgetToRoom(plugin);
    }
}

void    Plugins::PluginLoader::loadWidgetPlugins()
{
    QDir    pluginsDir = PlatformFactory::getPlatformInitializer()->getWidgetSharedLibrariesDirectory();
    // LOOP THROUGH EACH FILE OF THE PLUGIN DIR AND LOAD THE PLUGINS
    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        qDebug() << "NEW PLUGIN FOUND " << fileName << " ABSOLUTE PATH " << pluginsDir.absoluteFilePath(fileName);
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        Plugins::PluginInterface *plugin = qobject_cast<PluginInterface *>(pluginLoader.instance());
        if (plugin)
        {
            qDebug() << "WIDGET PLUGIN LOADED";
            widgetPlugins.append(plugin->getPluginBase());
        }
        else
        {
            qDebug() << "FAILED TO LOAD " << fileName;
            qDebug() << pluginLoader.errorString();
            pluginLoader.unload();
        }
    }
}

/*!
 * Returns a QList containing PluginBases plugins that could be loaded locally.
 */
QList<Plugins::PluginBase*>  Plugins::PluginLoader::getWidgetPlugins()
{
    return widgetPlugins;
}

QString     Plugins::PluginLoader::loadAllPluginForRoom(Room::RoomBase *room)
{
    return QString("SELECT idWidget, posX, posY, posZ FROM widgetImpl "
                   "WHERE idRoom = (SELECT idRoom FROM room WHERE name = '%1');")
            .arg(room->getRoomName());
}

QString     Plugins::PluginLoader::addOrReplacePluginImpl(Plugins::PluginBase *plugin, Room::RoomBase *room)
{
    return QString("INSERT OR REPLACE INTO widgetImpl (idRoom, idWidget, posX, posY, posZ) VALUES"
                   " ((SELECT idRoom FROM room WHERE name = '%1'), %2, %3, %4, %5);")
            .arg(room->getRoomName(),
                 QString::number(plugin->getPluginId()),
                 QString::number(plugin->getPluginPosition().x()),
                 QString::number(plugin->getPluginPosition().y()),
                 QString::number(plugin->getPluginPosition().z()));
}

QString Plugins::PluginLoader::removeAllPluginsFromRoom(Room::RoomBase *room)
{
    return QString("DELETE FROM widgetImpl WHERE idRoom = (SELECT idRoom FROM room WHERE name = '%1');")
            .arg(room->getRoomName());
}

bool Plugins::PluginLoader::installPluginOnPlatform()
{
}


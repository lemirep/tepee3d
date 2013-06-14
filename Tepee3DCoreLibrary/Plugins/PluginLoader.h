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

#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QList>
#include <QCoreApplication>
#include <QPluginLoader>
#include <QQmlExtensionPlugin>
#include <QDir>
#include <DatabaseServiceUserInterface.h>
#include "PluginInterface.h"
#include "PluginBase.h"
#include <PluginManager.h>
#include <RoomBase.h>
#include <PlatformFactory.h>

#define PLUGIN_LOADED 1
#define DB_NAME "Tepee3D.sql"

namespace Plugins
{

class PluginLoader :  public QObject
{
    Q_OBJECT

private :
    PluginLoader(QObject *parent = 0); // PRIVATE SO THAT IT CANNOT  BE CALLED
    static QList<PluginBase *>      widgetPlugins; //LIST CONTAINING ALL THE PLUGINS
    static      PluginLoader*       instance;
public :
    ~PluginLoader();
    static void                     loadWidgetPlugins(); //TRIES TO LOAD EVERY PLUGIN IN DIR AND RETURN FALSE IF ERROR OCCURS
    static QList<PluginBase *>      getWidgetPlugins(); // RETURN LIST CONTAINING ALL THE LOADED PLUGINS
    static PluginLoader*            getInstance(QObject *parent = 0);
    static void                     addPluginToRoom(Plugins::PluginBase *plugin, Room::RoomBase *room);
    static QString                  loadAllPluginForRoom(Room::RoomBase *room);
    static QString                  addOrReplacePluginImpl(Plugins::PluginBase *plugin, Room::RoomBase *room);
    static QString                  removeAllPluginsFromRoom(Room::RoomBase *room);
    static bool                     installPluginOnPlatform();
signals :

};

}
#endif // PLUGINLOADER_H

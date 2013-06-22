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

#include "PluginModelItem.h"
// DEBUG
#include <QDebug>

/*!
 * \class Models::PluginModelItem
 * \code
 * #include <PluginModelItem.h>
 * \endcode
 *
 * \brief Models::PluginModelItem
 *
 * \inmodule Tepee3D
 */

/*!
 * Constructs a new Models::PluginModelItem instance given a \a plugin and an optionnal \a parent.
 */

Models::PluginModelItem::PluginModelItem(Plugins::PluginBase* plugin, QObject *parent) : ListItem(parent)
{
    this->plugin = plugin;
}

/*!
 * Destroys a Models::PluginModelItem instance
 */
Models::PluginModelItem::~PluginModelItem()
{
    // ENSURE THAT THE PLUGIN ABOUT TO BE DELETED IS A PLUGIN CREATED FROM AN INSTANCE OF
    // A PLUGIN FROM THE PLUGIN LOADER LIST AND NOT A PLUGIN LOADER PLUGIN ITSELF
    qDebug() << "DELETING PLUGIN MODEL ITEM";
    if (this->plugin != NULL)
        delete this->plugin;
}

/*!
 * Returns the id of the PluginModelItem.
 */
int     Models::PluginModelItem::id()  const
{
    return this->plugin->getPluginId();
}

/*!
 * Returns the role values of a given \a role of the PluginModelItem.
 */
QVariant    Models::PluginModelItem::data(int role)    const
{
    switch (role)
    {
    case pluginId :
        return this->id();
    case pluginName :
        return this->plugin->getPluginName();
    case pluginRoomQmlFile :
        return this->plugin->getRoomPluginQmlFile();
    case pluginMenuQmlFile :
        return this->plugin->getMenuPluginQmlFile();
    case pluginPosition :
        return this->plugin->getPluginPosition();
    default :
        return QVariant();
    }
}

/*!
 * Returns a hash containing the roles of the PluginModelItem.
 */
QHash<int, QByteArray> Models::PluginModelItem::roleNames()   const
{
    QHash<int, QByteArray>  roles;

    roles[pluginId]   = "pluginId";
    roles[pluginName] = "pluginName";
    roles[pluginRoomQmlFile] = "pluginRoomQmlFile";
    roles[pluginMenuQmlFile] = "pluginMenuQmlFile";
    roles[pluginPosition] = "pluginPosition";

    return roles;
}

/*!
 * Returns the instance of the plugin the PluginModelItem is a description of.
 */

Plugins::PluginBase*    Models::PluginModelItem::getPlugin()   const
{
    return this->plugin;
}

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

#ifndef PLUGINQMLPLUGINPROPERTIES_H
#define PLUGINQMLPLUGINPROPERTIES_H

#include <QObject>
#include <QQuickItem>
#include <QDebug>
#include "ViewToModelMapper.h"
#include "PluginBase.h"
#include "PluginEnums.h"

// CUSTOM C++ QML OBJECT USED TO MAP A QML PLUGIN TO A PLUGINBASE MODEL

namespace Plugins
{
// USED TO FIND PLUGIN BASE FROM QML
class PluginQmlPluginProperties : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int pluginId READ getPluginId WRITE setPluginId NOTIFY pluginIdChanged)
    Q_PROPERTY(int pluginRoomId READ getPluginRoomId WRITE setPluginRoomId NOTIFY pluginRoomIdChanged)
    Q_PROPERTY(Plugins::PluginEnums::PluginState focusState READ getFocusState NOTIFY focusStateChanged)
    Q_ENUMS(Plugins::PluginEnums::PluginState)

public:
    explicit PluginQmlPluginProperties();
    ~PluginQmlPluginProperties();

    Q_INVOKABLE void            askForFocusState(int);

    int                         getPluginId()   const;
    void                        setPluginId(int id);

    int                         getPluginRoomId()   const;
    void                        setPluginRoomId(int id);

    PluginEnums::PluginState    getFocusState() const;

private:
    int                 pluginId;
    int                 pluginRoomId;
    PluginBase          *plugin;

    void                        findPluginForRoomAndPluginId();

signals:
    void                        pluginIdChanged();
    void                        focusStateChanged(QVariant newFocusStateValue, QVariant previousFocusState);
    void                        pluginRoomIdChanged();
    void                        roomEntered();
    void                        roomLeft();
};
}
#endif // PLUGINQMLPLUGINPROPERTIES_H

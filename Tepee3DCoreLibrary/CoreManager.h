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

#ifndef QMLVIEWMANAGER_H
#define QMLVIEWMANAGER_H

#include <QCoreApplication>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QQmlContext>
#include "QmlViewProperties.h"
#include "QmlContentExposerInterface.h"
#include "PluginManager.h"
#include "RoomManager.h"
#include "ServicesManager.h"
#include "QmlAsTexture.h"
#include "PlatformFactory.h"
#include <CoreLibraryInterface.h>

#define CORE_VERSION "0.1"

class CoreManager : public QObject, public CoreLibraryInterface
{
    Q_OBJECT
    Q_INTERFACES(CoreLibraryInterface)
    Q_PLUGIN_METADATA(IID "com.tepee3d.Core")

private:
    View::QmlViewProperties         *viewProperties;   // QML VIEW PROPERTIES
    Room::RoomManager               *roomManager;      // ROOM MANAGER
    Services::ServicesManager       *servicesManager;  // SERVICESMANAGER
    Plugins::PluginManager          *pluginsManager;   // PLUGIN MANAGER

public:
    explicit CoreManager();
    ~CoreManager();

    void                            initCoreEngine();
    QString                         getCoreVersion();
    QObject*                        getObject();

public slots:
    bool                            initView();
    void                            cleanBeforeClosing();

signals:
    void                            quit();

};
#endif // QMLVIEWMANAGER_H

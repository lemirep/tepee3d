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

#ifndef GENERICPLATFORMINITIALIZER_H
#define GENERICPLATFORMINITIALIZER_H

#include "IPlatformInitializer.h"
#include <QCoreApplication>

#define GENERIC_DATA_DIR ""
#define GENERIC_SHARED_LIBRARIES_DIR "libraries"
#define GENERIC_THIRDPARTY_LIBRARIES_DIR "libraries/3rd_party"
#define GENERIC_WIDGET_LIBRARIES_DIR "libraries/widget_libraries"
#define GENERIC_ROOM_LIBRARY_DIR "libraries/room_library"
#define GENERIC_SERVICES_LIBRARIES_DIR "libraries/services_lib"
#define GENERIC_WIDGET_RESOURCE_DIR "plugins_qml"
#define GENERIC_DATABASE_DIRECTORY "databases"

class GenericPlatformInitializer : public IPlatformInitializer
{
public:
    GenericPlatformInitializer();
    bool        initPlatform();
    QDir        getDataDirectory() const;
    QDir        getWidgetSharedLibrariesDirectory() const;
    QDir        getWidgetsResourceDirectory() const;
    QDir        getThirdPartiesLibrariesDirectory() const;
    QDir        getServicesSharedLibrariesDirectory() const;
    QDir        getRoomSharedLibraryDirectory() const;
    QDir        getSharedLibraryDirectory() const;
    QDir        getDatabaseDirectory() const;
    QString     getPlatformName() const;
};

#endif // GENERICPLATFORMINITIALIZER_H

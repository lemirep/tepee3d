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

#ifndef IPLATFORMINITIALIZER_H
#define IPLATFORMINITIALIZER_H

#include <QString>
#include <QDir>

#define QNX_PLATFORM "qnx"
#define IOS_PLATFORM "ios"
#define MAC_PLATFORM "mac"
#define LINUX_32_PLATFORM "linux_32"
#define LINUX_64_PLATFORM "linux_64"
#define UNIX_32_PLATFORM "unix_32"
#define UNIX_64_PLATFORM "unix_64"
#define WINDOWS_32_PLATFORM "windows_32"
#define WINDOWS_64_PLATFORM "windows_64"
#define ANDROID_PLATFORM "android"


class IPlatformInitializer
{
public :
    virtual bool            initPlatform() = 0;
    virtual QDir           getDataDirectory() const = 0;
    virtual QDir           getWidgetSharedLibrariesDirectory() const = 0;
    virtual QDir           getServicesSharedLibrariesDirectory() const = 0;
    virtual QDir           getRoomSharedLibraryDirectory() const = 0;
    virtual QString      getPlatformName() const = 0;
};

#endif // IPLATFORMINITIALIZER_H

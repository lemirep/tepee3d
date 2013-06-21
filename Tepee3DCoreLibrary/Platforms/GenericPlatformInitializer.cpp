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

#include "GenericPlatformInitializer.h"

GenericPlatformInitializer::GenericPlatformInitializer() : IPlatformInitializer()
{
}

bool GenericPlatformInitializer::initPlatform()
{
    return true;
}

QDir GenericPlatformInitializer::getDataDirectory() const
{
    QDir    dir = QCoreApplication::applicationDirPath();

#if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug" || dir.dirName().toLower() == "release")
       dir.cdUp();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS")
    {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
#ifdef COVERAGE_AND_UNITTESTS
    dir.cdUp();
    dir.cd("Tepee3DEngine");
#endif
    return dir;
}

QDir GenericPlatformInitializer::getServicesSharedLibrariesDirectory() const
{
    QDir    dir = QCoreApplication::applicationDirPath();

#if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug" || dir.dirName().toLower() == "release")
       dir.cdUp();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS")
    {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
#ifdef COVERAGE_AND_UNITTESTS
    dir.cdUp();
    dir.cd("Tepee3DEngine");
#endif
    dir.cd(GENERIC_SERVICES_LIBRARIES_DIR);
    return dir;
}

QDir GenericPlatformInitializer::getRoomSharedLibraryDirectory() const
{
    QDir    dir = QCoreApplication::applicationDirPath();

#if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug" || dir.dirName().toLower() == "release")
       dir.cdUp();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS")
    {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
#ifdef COVERAGE_AND_UNITTESTS
    dir.cdUp();
    dir.cd("Tepee3DEngine");
#endif
    dir.cd(GENERIC_ROOM_LIBRARY_DIR);
    return dir;
}

QDir GenericPlatformInitializer::getSharedLibraryDirectory() const
{
    QDir dir = QCoreApplication::applicationDirPath();
#ifdef COVERAGE_AND_UNITTESTS
    dir.cdUp();
    dir.cd("Tepee3DEngine");
#endif
    dir.cd(GENERIC_SHARED_LIBRARIES_DIR);
    return dir;
}

QDir GenericPlatformInitializer::getWidgetSharedLibrariesDirectory() const
{
    QDir    dir = QCoreApplication::applicationDirPath();

#if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug" || dir.dirName().toLower() == "release")
       dir.cdUp();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS")
    {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
#ifdef COVERAGE_AND_UNITTESTS
    dir.cdUp();
    dir.cd("Tepee3DEngine");
#endif
    dir.cd(GENERIC_WIDGET_LIBRARIES_DIR);
    return dir;
}

QString GenericPlatformInitializer::getPlatformName() const
{
#if defined Q_OS_QNX
    return QNX_PLATFORM;
#elif defined Q_OS_MACX
    return MAC_PLATFORM;
#elif defined Q_OS_IOS
    return IOS_PLATFORM;
#elif defined Q_OS_LINUX
    #if defined Q_PROCESSOR_X86_64
        return LINUX_64_PLATFORM;
    #else
        return LINUX_32_PLATFORM;
    #endif
#elif defined Q_OS_UNIX
    #if define Q_PROCESSOR_X86_64
        return UNIX_64_PLATFORM;
    #else
        return UNIX_32_PLATFORM;
    #endif
#elif defined Q_OS_WIN32
    return WINDOWS_32_PLATFORM;
#elif defined Q_OS_WIN64
    return WINDOWS_64_PLATFORM;
#endif
}

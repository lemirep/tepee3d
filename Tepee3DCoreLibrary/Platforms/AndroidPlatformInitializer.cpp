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

#include "AndroidPlatformInitializer.h"
#include <QDebug>

AndroidPlatformInitializer::AndroidPlatformInitializer() : IPlatformInitializer()
{
}

bool AndroidPlatformInitializer::initPlatform()
{
    // Copy files from assets to data dir

    if (QFile("assets:/qml/main.qml").exists())
    {
        qDebug() << "Copying Files Android";

        QList<QString> pathsList;

        pathsList.prepend("qml/Resources/Textures/skybox");
        pathsList.prepend("qml/Resources/Pictures");
        pathsList.prepend("qml/Resources/Textures");
        pathsList.prepend("qml/Resources/Models");
        pathsList.prepend("qml/Resources");
        pathsList.prepend("qml/Rooms");
        pathsList.prepend("qml/Menus");
        pathsList.prepend("qml/Notifications");
        pathsList.prepend("qml/Plugins");
        pathsList.prepend("qml/content");
        pathsList.prepend("qml/js");
        pathsList.prepend("qml");

        pathsList.prepend("databases");

        pathsList.prepend("DeveloperAPIFiles/qml/UIComponents");
        pathsList.prepend("DeveloperAPIFiles/qml/Resources/Pictures");
        pathsList.prepend("DeveloperAPIFiles/qml/Resources");
        pathsList.prepend("DeveloperAPIFiles/qml");
        pathsList.prepend("DeveloperAPIFiles/js");
        pathsList.prepend("DeveloperAPIFiles");

        pathsList.prepend("plugins_qml/SeriesPlugin");
        pathsList.prepend("plugins_qml/WatchPlugin");
        pathsList.prepend("plugins_qml/TestPlugin");
        pathsList.prepend("plugins_qml/XBMCPlugin");
        pathsList.prepend("plugins_qml/HarlemShake");
        pathsList.prepend("plugins_qml");

        foreach (QString dirEntry, pathsList)
        {
            bool exists = QDir(dirEntry).exists();
            if (!exists)
            {
                qDebug() << "Dir doesn't exist, creating it " << dirEntry;
                exists = getDataDirectory().mkdir(dirEntry);
                if (exists)
                {
                    QDir tmpDir(dirEntry);
                    foreach (QString entry, QDir("assets:/" + dirEntry).entryList(QDir::Files))
                    {
                        if (!QFile::copy("assets:/" + dirEntry + "/" + entry, tmpDir.absolutePath() + "/" + entry))
                            qDebug() << "Copy Failed for Entry " << dirEntry << " -- >" << entry << " to " << tmpDir.absolutePath() + "/" + entry;
                        // Give Write access to databases
                        if (dirEntry == "databases")
                            QFile::setPermissions(tmpDir.absolutePath() + "/" + entry, QFile::ReadOwner|QFile::WriteOwner);
                    }
                }
            }
        }
    }

    QDir tmpServicesLibDir = AndroidPlatformInitializer::getServicesSharedLibrariesDirectory();
    qDebug() << "Service DIr Lib " << tmpServicesLibDir.absolutePath();
    bool exists = false;
    if (!(exists = tmpServicesLibDir.exists()))
    {
        exists = AndroidPlatformInitializer::getDataDirectory().mkdir(ANDROID_SERVICES_DIR);
        if (exists)
        {
            qDebug() << "Service Lib Dir Created";
            QList<QString> serviceLibs;
            serviceLibs.prepend("libManageDatabaseServiceLibrary.so");
            serviceLibs.prepend("libWebServiceManagerLibrary.so");
            serviceLibs.prepend("libFileDownloaderLibrary.so");
            foreach (QString serviceLib, serviceLibs)
            {
                this->copyLibToDir(this->getSharedLibraryDirectory().absolutePath() + "/" + serviceLib,
                                   tmpServicesLibDir.absolutePath() + "/" + serviceLib);
            }
        }
    }

    // ROOM LIBRARY
    QDir tmpRoomLibDir = AndroidPlatformInitializer::getRoomSharedLibraryDirectory();
    qDebug() << "RoomDIr Lib " << tmpRoomLibDir.absolutePath();
    if (!(exists = tmpRoomLibDir.exists()))
    {
        exists = AndroidPlatformInitializer::getDataDirectory().mkdir(ANDROID_ROOM_DIR);
        if (exists)
        {
            QString libName = "libRoomLibrary.so";
            this->copyLibToDir(this->getSharedLibraryDirectory().absolutePath() + "/" + libName,
                               tmpRoomLibDir.absolutePath() + "/" + libName);
        }
    }

    // WIDGET LIBRARY

    QDir tmpWidgetLibDir = AndroidPlatformInitializer::getWidgetSharedLibrariesDirectory();
    qDebug() << "Widget DIr Lib " << tmpWidgetLibDir.absolutePath();
    if (!(exists = tmpWidgetLibDir.exists()))
    {
        exists = AndroidPlatformInitializer::getDataDirectory().mkdir(ANDROID_WIDGETS_DIR);
        if (exists)
            foreach (QString widgetLib, this->getSharedLibraryDirectory().entryList())
            {
                if (widgetLib.compare("libCoreLibrary.so") != 0 &&
                        widgetLib.compare("libRoomLibrary.so") != 0 &&
                        widgetLib.compare("libManageDatabaseServiceLibrary.so") != 0 &&
                        widgetLib.compare("libWebServiceManagerLibrary.so") != 0 &&
                        widgetLib.compare("libFileDownloaderLibrary.so") != 0 &&
                        widgetLib.compare("gdbserver") != 0 &&
                        widgetLib.compare("libgnustl_shared.so") != 0 &&
                        !widgetLib.startsWith("libQt5") &&
                        !widgetLib.startsWith("lib--Managed_by_Qt_Creator"))
                    this->copyLibToDir(this->getSharedLibraryDirectory().absolutePath() + "/" + widgetLib,
                                       this->getWidgetSharedLibrariesDirectory().absolutePath() + "/" + widgetLib);
            }
    }
    qDebug() << "Copying Files Done";
    return true;
}

QDir AndroidPlatformInitializer::getWidgetSharedLibrariesDirectory() const
{
    return QDir(QString(ANDROID_DATA_DIR) + "/" + QString(ANDROID_WIDGETS_DIR));
}

QDir AndroidPlatformInitializer::getServicesSharedLibrariesDirectory() const
{
    return QDir(QString(ANDROID_DATA_DIR) + "/" + QString(ANDROID_SERVICES_DIR));
}

QDir AndroidPlatformInitializer::getRoomSharedLibraryDirectory() const
{
    return QDir(QString(ANDROID_DATA_DIR) + "/" + QString(ANDROID_ROOM_DIR));
}

QDir AndroidPlatformInitializer::getSharedLibraryDirectory() const
{
    return QDir(ANDROID_LIB_DIR);
}

QDir AndroidPlatformInitializer::getDataDirectory() const
{
    return QDir(ANDROID_DATA_DIR);
}

QString AndroidPlatformInitializer::getPlatformName() const
{
    return ANDROID_PLATFORM;
}

bool AndroidPlatformInitializer::copyLibToDir(QString src, QString dst)
{
    if (QFile::exists(src))
        if (QFile::copy(src, dst))
            return QFile::remove(src);
    return false;
}

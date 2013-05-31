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
            }
            if (exists)
            {
                QDir tmpDir(dirEntry);
                foreach (QString entry, QDir("assets:/" + dirEntry).entryList(QDir::Files))
                {
                    qDebug() << "Entry " << dirEntry << " -- >" << entry << " to " << tmpDir.absolutePath() + "/" + entry;
                    if (!QFile::copy("assets:/" + dirEntry + "/" + entry, tmpDir.absolutePath() + "/" + entry))
                        qDebug() << "Copy Failed";
                }
            }
        }
    }

    QDir tmpServicesLibDir = AndroidPlatformInitializer::getServicesSharedLibrariesDirectory();
    if (!tmpServicesLibDir.exists())
        AndroidPlatformInitializer::getSharedLibraryDirectory().mkdir("services_lib");
    qDebug() << "Copying Files Done";
    return true;
}

QDir AndroidPlatformInitializer::getWidgetSharedLibrariesDirectory() const
{
//    return QDir(ANDROID_LIB_DIR + "/widget_libraries");
    return QDir(ANDROID_LIB_DIR);
}

QDir AndroidPlatformInitializer::getServicesSharedLibrariesDirectory() const
{
//    return QDir(ANDROID_LIB_DIR + "/services_lib");
    return QDir(ANDROID_LIB_DIR);
}

QDir AndroidPlatformInitializer::getRoomSharedLibraryDirectory() const
{
    return QDir(ANDROID_LIB_DIR);
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

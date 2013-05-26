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
        QDir assetDirectory("assets:/databases/");
        //QDir assetDirectory2("assets:/plugins_qml/");
        //QDir assetDirectory3("assets:/DeveloperAPIFiles/");

        // qml
        foreach (QString entry, assetDirectory.entryList(QDir::Files))
        {
            qDebug() << "Copying " << AndroidPlatformInitializer::getDataDirectory().absolutePath() + "/databases/"  + entry;
            QFile(entry).copy(AndroidPlatformInitializer::getDataDirectory().absolutePath() + "/databases/"  + entry);
        }
//        // plugins_qml
//        foreach (QString entry, assetDirectory2.entryList())
//        {
//            qDebug() << "entry 2" << entry;
//        }
//        // databases
//        foreach (QString entry, assetDirectory3.entryList())
//        {
//            qDebug() << "entry 3" << entry;
//        }
    }
    qDebug() << "Copying Files Done";
    return true;
}

QDir AndroidPlatformInitializer::getWidgetSharedLibrariesDirectory() const
{
    return QDir(ANDROID_LIB_DIR);
}

QDir AndroidPlatformInitializer::getServicesSharedLibrariesDirectory() const
{
    return QDir(ANDROID_LIB_DIR);
}

QDir AndroidPlatformInitializer::getRoomSharedLibraryDirectory() const
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

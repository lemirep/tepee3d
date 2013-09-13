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

#include <QGuiApplication>
#include <QPluginLoader>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QUrl>
#include <QScopedPointer>
#include <CoreLibraryInterface.h>

#define CORE_LIBRARY_DIRECTORY "libraries/core"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> app(new QGuiApplication(argc, argv));
    CoreLibraryInterface* coreEngine = NULL;
    QDir libDir;
    QPluginLoader loader;

#ifndef Q_OS_ANDROID
    libDir = QCoreApplication::applicationDirPath();
    libDir.cd(CORE_LIBRARY_DIRECTORY);
    qDebug() << libDir.absolutePath();
    qDebug() << libDir.absoluteFilePath(libDir.entryList(QDir::Files).first());
    loader.setFileName(libDir.absoluteFilePath(libDir.entryList(QDir::Files).first()));
#endif

#ifdef Q_OS_ANDROID
    libDir = QDir("/data/data/org.qtproject.example.Tepee3D/lib");
    qDebug() << libDir.absolutePath();
    qDebug() << libDir.absoluteFilePath("libCoreLibrary.so");
    loader.setFileName(libDir.absoluteFilePath("libCoreLibrary.so"));
#endif

    qDebug() << "Trying to load Core Library";

    if ((coreEngine = qobject_cast<CoreLibraryInterface *>(loader.instance())) != NULL)
    {
        qDebug() << "Core Library Loaded";
        coreEngine->initCoreEngine();
        QObject::connect(coreEngine->getObject(), SIGNAL(quit()), app.data(), SLOT(quit()));
    }
    else
    {
        qDebug() << "Couldnt load core library";
        qDebug() << loader.errorString();
    }
    return app->exec();
}

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

#ifndef ANDROIDPLATFORMINITIALIZER_H
#define ANDROIDPLATFORMINITIALIZER_H

#include "IPlatformInitializer.h"

#define ANDROID_LIB_DIR "/data/data/org.qtproject.example.Tepee3D/lib"
#define ANDROID_DATA_DIR "./"


class AndroidPlatformInitializer : public IPlatformInitializer
{
public:
    AndroidPlatformInitializer();
    bool initPlatform();
    virtual QDir           getDataDirectory() const;
    virtual QDir           getWidgetSharedLibrariesDirectory() const;
    virtual QDir           getServicesSharedLibrariesDirectory() const;
    virtual QDir           getRoomSharedLibraryDirectory() const;
    virtual QString      getPlatformName() const;
};

#endif // ANDROIDPLATFORMINITIALIZER_H

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

#ifndef LEAPMOTIONMANAGERLIBRARY_H
#define LEAPMOTIONMANAGERLIBRARY_H

#include <QObject>
#include "ServiceInterface.h"
#include "LeapMotionController.h"
//#include "LeapGestureArea.h"
#include "LeapMotionServiceUserInterface.h"
//#include "QmlContentExposerInterface.h"

#define LEAP_MOTION_LIBRARY_VERSION "0.0.1"
#define LEAP_MOTION_SERVICE_ID 5

class LeapMotionManagerLibrary : public QObject,
                                 public Services::ServiceInterface
//                                 public View::QmlContentExposerInterface
{
    Q_OBJECT
    Q_INTERFACES(Services::ServiceInterface)
//    Q_INTERFACES(View::QmlContentExposerInterface)
    Q_PLUGIN_METADATA(IID "com.tepee3d.Services.leapmotioncontrollerservice")
public:
    LeapMotionManagerLibrary();
    ~LeapMotionManagerLibrary();

private:

    LeapMotionController *leapMotionController;

public:
    // ServiceInterface interface
    void initLibraryConnection(QObject *parent);
    bool connectServiceToUser(QObject *user);
    bool disconnectServiceFromUser(QObject *user);
    int getServiceId() const;
    QString getServiceVersion() const;
    QObject *getLibraryQObject();
    // QmlContentExposerInterface interface
//    void exposeContentToQml(QQmlContext *context);

signals:
    void    initialized();

};

#endif // LEAPMOTIONMANAGERLIBRARY_H

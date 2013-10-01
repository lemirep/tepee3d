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

#include "LeapMotionManagerLibrary.h"
#include <QDebug>

LeapMotionManagerLibrary::LeapMotionManagerLibrary() : QObject()
{
    this->leapMotionController = NULL;
    // SHOULD BE CALLED TO REGISTER LEAP MOTION AS TOUCH DEVICE BUT INCLUDE NOT RESOLVED
    //    QWindowSystemInterface::registerTouchDevice(LeapMotionTouchDevice::getInstance());
}

LeapMotionManagerLibrary::~LeapMotionManagerLibrary()
{
    if (this->leapMotionController != NULL)
        this->leapMotionController = NULL;
}

void LeapMotionManagerLibrary::initLibraryConnection(QObject *parent)
{
    QObject::connect(this, SIGNAL(initialized()), parent, SLOT(libraryInitialized()));
    this->leapMotionController = LeapMotionController::getInstance();
    emit (initialized());
}

bool LeapMotionManagerLibrary::connectServiceToUser(QObject *user)
{
    bool connected = false;
    if(qobject_cast<Services::LeapMotionServiceInputUserInterface *>(user) != NULL)
    {
        QObject::connect(user, SIGNAL(registerToLeapMotionInputs(QObject*)),
                         this->leapMotionController, SLOT(registerTargetListenerToLeapMotionInputs(QObject*)));
        QObject::connect(user, SIGNAL(unregisterFromLeapMotionInputs(QObject*)),
                         this->leapMotionController, SLOT(unregisterTargetListenerFromLeapMotionInputs(QObject*)));
        connected = true;
    }
    if(qobject_cast<Services::LeapMotionServiceGestureUserInterface *>(user) != NULL)
    {
        QObject::connect(user, SIGNAL(registerToLeapMotionGestures(QObject*)),
                         this->leapMotionController, SLOT(registerTargetListenerToLeapMotionGestures(QObject*)));
        QObject::connect(user, SIGNAL(unregisterFromLeapMotionGestures(QObject*)),
                         this->leapMotionController, SLOT(unregisterTargetListenerFromLeapMotionGestures(QObject*)));
        connected = true;
    }
    if (!connected)
        qDebug() << "Object doesn't implement LeapMotionServiceUserInterface";
    return connected;
}

bool LeapMotionManagerLibrary::disconnectServiceFromUser(QObject *user)
{
    bool connected = false;
    if(qobject_cast<Services::LeapMotionServiceInputUserInterface *>(user) != NULL)
    {
        QObject::disconnect(user, SIGNAL(registerToLeapMotionInputs(QObject*)),
                         this->leapMotionController, SLOT(registerTargetListenerToLeapMotionInputs(QObject*)));
        QObject::disconnect(user, SIGNAL(unregisterFromLeapMotionInputs(QObject*)),
                         this->leapMotionController, SLOT(unregisterTargetListenerFromLeapMotionInputs(QObject*)));
        connected = true;
    }
    if(qobject_cast<Services::LeapMotionServiceGestureUserInterface *>(user) != NULL)
    {
        QObject::disconnect(user, SIGNAL(registerToLeapMotionGestures(QObject*)),
                         this->leapMotionController, SLOT(registerTargetListenerToLeapMotionGestures(QObject*)));
        QObject::connect(user, SIGNAL(unregisterFromLeapMotionGestures(QObject*)),
                         this->leapMotionController, SLOT(unregisterTargetListenerFromLeapMotionGestures(QObject*)));
        connected = true;
    }
    if (!connected)
        qDebug() << "Object doesn't implement LeapMotionServiceUserInterface";
    return connected;
}

int LeapMotionManagerLibrary::getServiceId() const
{
    return LEAP_MOTION_SERVICE_ID;
}

QString LeapMotionManagerLibrary::getServiceVersion() const
{
    return QString(LEAP_MOTION_LIBRARY_VERSION);
}

QObject *LeapMotionManagerLibrary::getLibraryQObject()
{
    return this;
}

//void LeapMotionManagerLibrary::exposeContentToQml(QQmlContext *context)
//{
//    qmlRegisterType<LeapGestureArea>("LeapGestureArea", 1, 0, "LeapGestureArea");
//}

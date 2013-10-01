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

#include "LeapGestureArea.h"

Tepee3DQmlExtensions::LeapGestureArea::LeapGestureArea(QQuickItem *parent) : QQuickItem(parent)
{
    // REGISTER THE OBJECT TO TEPEE3D SERVICES
    View::ViewToModelMapper::connectQQuickItemToServices(this);
}

Tepee3DQmlExtensions::LeapGestureArea::~LeapGestureArea()
{
    // DISCONNECT THE OBJECT LEAP MOTION GESTURES SERVICE
    emit unregisterFromLeapMotionGestures(this);
    View::ViewToModelMapper::disconnectQQuickItemFromServices(this);
}

void  Tepee3DQmlExtensions::LeapGestureArea::touchEvent(QTouchEvent *event)
{
    qDebug() << "Receiving Touch Events";
}

void Tepee3DQmlExtensions::LeapGestureArea::componentComplete()
{
    // CONNECT THE OBJECT AS A LISTENER TO LEAP MOTION GESTURES
    emit registerToLeapMotionGestures(this);
}

QSGNode * Tepee3DQmlExtensions::LeapGestureArea::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data)
{
    Q_UNUSED(data);
    qDebug() << "Update Paint Node";
    QSGSimpleRectNode *rectangle = static_cast<QSGSimpleRectNode *>(oldNode);
    if (!rectangle)
        rectangle = new QSGSimpleRectNode();
    rectangle->setRect(QRectF(0, 0, width(), height()));
    rectangle->setColor(QColor(255, 0, 0, 50));
    this->update();
    return rectangle;
}

void  Tepee3DQmlExtensions::LeapGestureArea::onCircleGestureCallBack(const QVector3D &circleCenter,
                                                                     const QVector3D &circleNormal,
                                                                     const float circleRadius,
                                                                     const float circleTurns,
                                                                     const Services::LeapMotionServiceGestureUserInterface::GestureState circleGestureState)
{
    //    qDebug() << "LeapGextureArea Circle " << circleCenter;

    if (this->contains(QPointF(circleCenter.x(), circleCenter.y())))
        emit circleGesture();
}

void  Tepee3DQmlExtensions::LeapGestureArea::onScreenTapGestureCallBack(const QVector3D &screenTapDirection,
                                                                        const QVector3D &screenTapPosition,
                                                                        const Services::LeapMotionServiceGestureUserInterface::GestureState screenTapGestureState)
{
    if (this->contains(QPointF(screenTapPosition.x(), screenTapPosition.y())))
    {
        emit screenTapGesture();
    }
}

void  Tepee3DQmlExtensions::LeapGestureArea::onKeyTapGestureCallBack(const QVector3D &keyTapDirection,
                                                                     const QVector3D &keyTapPosition,
                                                                     const Services::LeapMotionServiceGestureUserInterface::GestureState keyTapGestureState)
{
    if (this->contains(QPointF(keyTapPosition.x(), keyTapPosition.y())))
        emit keyTapGesture();
}

void  Tepee3DQmlExtensions::LeapGestureArea::onSwipeGestureCallBack(const QVector3D &swipeDirection,
                                                                    const QVector3D &swipePosition,
                                                                    const QVector3D &swipeStartPosition,
                                                                    const float swipeSpeed,
                                                                    const Services::LeapMotionServiceGestureUserInterface::GestureState swipeGestureState)
{
    if (this->contains(QPointF(swipeStartPosition.x(), swipeStartPosition.y()))
            && this->contains(QPointF(swipePosition.x(), swipePosition.y())))
    {
        emit swipeGesture();
    }
}

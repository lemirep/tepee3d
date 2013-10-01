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

#ifndef LEAPGESTUREAREA_H
#define LEAPGESTUREAREA_H

#include <QQuickItem>
#include <QSGSimpleRectNode>
#include <ViewToModelMapper.h>
#include "LeapMotionServiceUserInterface.h"

namespace Tepee3DQmlExtensions
{
class LeapGestureArea : public QQuickItem, public Services::LeapMotionServiceGestureUserInterface
{
    Q_OBJECT
    Q_INTERFACES(Services::LeapMotionServiceGestureUserInterface)
//     QQmlParserStatus interface
public:
    LeapGestureArea(QQuickItem *parent = 0);
    ~LeapGestureArea();

protected :
    void    touchEvent(QTouchEvent *event);
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data);
    // QQmlParserStatus interface
    void componentComplete();

    // LeapMotionServiceGestureUserInterface interface
public:
    void onCircleGestureCallBack(const QVector3D &cicrcleCenter,
                                 const QVector3D &circleNormal,
                                 const float circleRadius,
                                 const float circleTurns,
                                 const GestureState circleGestureState);
    void onScreenTapGestureCallBack(const QVector3D &screenTapDirection,
                                    const QVector3D &screenTapPosition,
                                    const GestureState screenTapGestureState);
    void onKeyTapGestureCallBack(const QVector3D &keyTapDirection,
                                 const QVector3D &keyTapPosition,
                                 const GestureState keyTapGestureState);
    void onSwipeGestureCallBack(const QVector3D &swipeDirection,
                                const QVector3D &swipePosition,
                                const QVector3D &swipeStartPosition,
                                const float swipeSpeed,
                                const GestureState swipeGestureState);

signals:
    void registerToLeapMotionGestures(QObject *listener);
    void unregisterFromLeapMotionGestures(QObject *listener);
    void circleGesture();
    void swipeGesture();
    void keyTapGesture();
    void screenTapGesture();


};
}

#endif // LEAPGESTUREAREA_H

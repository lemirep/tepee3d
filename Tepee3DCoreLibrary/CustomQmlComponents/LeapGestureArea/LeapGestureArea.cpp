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
    //    emit unregisterFromLeapMotionGestures(this);
    //    View::ViewToModelMapper::disconnectQQuickItemFromServices(this);
}

void Tepee3DQmlExtensions::LeapGestureArea::componentComplete()
{
    QQuickItem::componentComplete();
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

void  Tepee3DQmlExtensions::LeapGestureArea::onCircleGestureCallBack(int gestureId,
                                                                     const QVector3D circleCenter,
                                                                     const QVector3D circleNormal,
                                                                     const float circleRadius,
                                                                     const float circleTurns,
                                                                     const bool clockwise,
                                                                     const Services::LeapMotionServiceGestureUserInterface::GestureState circleGestureState)
{
    //    qDebug() << "LeapGextureArea Circle " << circleCenter;
    if (!isEnabled())
        return ;
    if (this->contains(QPointF(circleCenter.x(), circleCenter.y())))
    {
        Tepee3DQmlExtensions::LeapCircleGesture *gesture = NULL;
        if (this->savedGestures.contains(gestureId))
        {
            gesture = static_cast<Tepee3DQmlExtensions::LeapCircleGesture *>(this->savedGestures.take(gestureId));
            if (circleGestureState == Services::LeapMotionServiceGestureUserInterface::DoneState)
            {
                gesture->setState(Tepee3DQmlExtensions::LeapCircleGesture::CircleGestureDone);
                this->savedGestures.remove(gestureId);
            }
            else
                gesture->setState(Tepee3DQmlExtensions::LeapCircleGesture::CircleGestureUpdated);
        }
        else
        {
            gesture = new Tepee3DQmlExtensions::LeapCircleGesture();
            gesture->setId(gestureId);
        }
        gesture->setCenter(circleCenter);
        gesture->setNormal(circleNormal);
        gesture->setRadius(circleRadius);
        gesture->setTurns(circleTurns);
        gesture->setClockwise(clockwise);
        if (circleGestureState != Services::LeapMotionServiceGestureUserInterface::DoneState)
            this->savedGestures[gestureId] = gesture;
        emit circleGesture(gesture);
    }
}

void  Tepee3DQmlExtensions::LeapGestureArea::onScreenTapGestureCallBack(int gestureId,
                                                                        const QVector3D screenTapDirection,
                                                                        const QVector3D screenTapPosition,
                                                                        const Services::LeapMotionServiceGestureUserInterface::GestureState screenTapGestureState)
{
    Q_UNUSED(screenTapGestureState)
    if (!isEnabled())
        return ;
    if (this->contains(QPointF(screenTapPosition.x(), screenTapPosition.y())))
    {
        Tepee3DQmlExtensions::LeapTapGesture *gesture = new Tepee3DQmlExtensions::LeapTapGesture();
        gesture->setId(gestureId);
        gesture->setDirection(screenTapDirection);
        gesture->setPosition(screenTapPosition);
        emit screenTapGesture(gesture);
    }
}

void  Tepee3DQmlExtensions::LeapGestureArea::onKeyTapGestureCallBack(int gestureId,
                                                                     const QVector3D keyTapDirection,
                                                                     const QVector3D keyTapPosition,
                                                                     const Services::LeapMotionServiceGestureUserInterface::GestureState keyTapGestureState)
{
    Q_UNUSED(keyTapGestureState)
    if (!isEnabled())
        return ;
    if (this->contains(QPointF(keyTapPosition.x(), keyTapPosition.y())))
    {
        Tepee3DQmlExtensions::LeapTapGesture *gesture = new Tepee3DQmlExtensions::LeapTapGesture();
        gesture->setId(gestureId);
        gesture->setDirection(keyTapDirection);
        gesture->setPosition(keyTapPosition);
        emit keyTapGesture(gesture);
    }
}

void  Tepee3DQmlExtensions::LeapGestureArea::onSwipeGestureCallBack(int gestureId,
                                                                    const QVector3D swipeDirection,
                                                                    const QVector3D swipePosition,
                                                                    const QVector3D swipeStartPosition,
                                                                    const float swipeSpeed,
                                                                    const Services::LeapMotionServiceGestureUserInterface::GestureState swipeGestureState)
{
    if (!isEnabled())
        return ;
    if (this->contains(QPointF(swipeStartPosition.x(), swipeStartPosition.y()))
            || this->contains(QPointF(swipePosition.x(), swipePosition.y())))
    {
        Tepee3DQmlExtensions::LeapSwipeGesture *gesture = NULL;
        if (this->savedGestures.contains(gestureId))
        {
            gesture = static_cast<Tepee3DQmlExtensions::LeapSwipeGesture *>(this->savedGestures.take(gestureId));
            if (swipeGestureState == Services::LeapMotionServiceGestureUserInterface::DoneState)
            {
                gesture->setState(Tepee3DQmlExtensions::LeapSwipeGesture::SwipeGestureDone);
                this->savedGestures.remove(gestureId);
            }
            else
                gesture->setState(Tepee3DQmlExtensions::LeapSwipeGesture::SwipeGestureUpdated);
        }
        else
        {
            gesture = new Tepee3DQmlExtensions::LeapSwipeGesture();
            gesture->setId(gestureId);
        }
        gesture->setDirection(swipeDirection);
        gesture->setPosition(swipePosition);
        gesture->setStartPosition(swipeStartPosition);
        gesture->setSpeed(swipeSpeed);
        if (swipeGestureState != Services::LeapMotionServiceGestureUserInterface::DoneState)
            this->savedGestures[gestureId] = gesture;
        emit swipeGesture(gesture);
    }
}

void Tepee3DQmlExtensions::LeapGestureArea::onHandCallBack(const QList<Services::LeapMotionServiceGestureUserInterface::HandObject> &hands)
{
    if (!isEnabled())
        return ;
    QList<int> savedHandIDs = this->m_hands.keys();

    foreach (const Services::LeapMotionServiceGestureUserInterface::HandObject &hand, hands)
    {
        LeapHand *handObj;
        if (this->m_hands.contains(hand.id))
            handObj = reinterpret_cast<LeapHand *>(this->m_hands[hand.id]);
        else
        {
            handObj = new LeapHand(hand.id);
            this->m_hands[hand.id] = handObj;
        }
        savedHandIDs.removeAll(hand.id);
        handObj->setDirection(hand.direction);
        handObj->setPitch(hand.pitch);
        handObj->setRoll(hand.roll);
        handObj->setYaw(hand.yaw);
    }
    // REMOVE HANDS THAT HAVE NOT BEEN UPDATED OR ADDED
    foreach (int leftHandId, savedHandIDs)
        this->m_hands.remove(leftHandId);
    emit handsUpdated(this->m_hands.values());
}

QQmlListProperty<Tepee3DQmlExtensions::LeapHand> Tepee3DQmlExtensions::LeapGestureArea::getHands()
{
    return QQmlListProperty<LeapHand>(this, NULL, &Tepee3DQmlExtensions::LeapGestureArea::appendHand,
                                      &Tepee3DQmlExtensions::LeapGestureArea::handCount,
                                      &Tepee3DQmlExtensions::LeapGestureArea::handAt,
                                      NULL);
}

void Tepee3DQmlExtensions::LeapGestureArea::appendHand(QQmlListProperty<Tepee3DQmlExtensions::LeapHand> *list, Tepee3DQmlExtensions::LeapHand *hand)
{
    LeapGestureArea *area = static_cast<LeapGestureArea *>(list->object);
    area->m_hands[hand->getHandID()] = hand;
}

int Tepee3DQmlExtensions::LeapGestureArea::handCount(QQmlListProperty<Tepee3DQmlExtensions::LeapHand> *list)
{
    LeapGestureArea *area = static_cast<LeapGestureArea *>(list->object);
    return area->m_hands.count();
}

Tepee3DQmlExtensions::LeapHand *Tepee3DQmlExtensions::LeapGestureArea::handAt(QQmlListProperty<Tepee3DQmlExtensions::LeapHand> *list, int index)
{
    LeapGestureArea *area = static_cast<LeapGestureArea *>(list->object);
    return reinterpret_cast<LeapHand *>(area->m_hands[index]);
}


Tepee3DQmlExtensions::LeapCircleGesture::LeapCircleGesture() :
    QObject(),
    m_id(0),
    m_center(0,0,0),
    m_normal(0,0,0),
    m_radius(0),
    m_turns(0),
    m_state(Tepee3DQmlExtensions::LeapCircleGesture::CircleGestureStart),
    m_clockwise(true)
{
}

Tepee3DQmlExtensions::LeapCircleGesture::CircleGestureState Tepee3DQmlExtensions::LeapCircleGesture::getState() const
{
    return this->m_state;
}

QVector3D Tepee3DQmlExtensions::LeapCircleGesture::getCenter() const
{
    return this->m_center;
}

QVector3D Tepee3DQmlExtensions::LeapCircleGesture::getNormal() const
{
    return this->m_normal;
}

qreal Tepee3DQmlExtensions::LeapCircleGesture::getRadius() const
{
    return this->m_radius;
}

qreal Tepee3DQmlExtensions::LeapCircleGesture::getTurns() const
{
    return this->m_turns;
}

bool Tepee3DQmlExtensions::LeapCircleGesture::getClockwise() const
{
    return this->m_clockwise;
}

int Tepee3DQmlExtensions::LeapCircleGesture::getId() const
{
    return this->m_id;
}

void Tepee3DQmlExtensions::LeapCircleGesture::setId(int id)
{
    this->m_id = id;
}

void Tepee3DQmlExtensions::LeapCircleGesture::setClockwise(bool clockwise)
{
    if (clockwise != this->m_clockwise)
    {
        this->m_clockwise = clockwise;
        emit clockwiseChanged();
    }
}

void Tepee3DQmlExtensions::LeapCircleGesture::setState(Tepee3DQmlExtensions::LeapCircleGesture::CircleGestureState state)
{
    if (state != this->m_state)
    {
        this->m_state = state;
        emit stateChanged();
    }
}

void Tepee3DQmlExtensions::LeapCircleGesture::setCenter(const QVector3D &center)
{
    if (center != this->m_center)
    {
        this->m_center = center;
        emit centerChanged();
    }
}

void Tepee3DQmlExtensions::LeapCircleGesture::setNormal(const QVector3D &normal)
{
    if (normal != this->m_normal)
    {
        this->m_normal = normal;
        emit normalChanged();
    }
}

void Tepee3DQmlExtensions::LeapCircleGesture::setRadius(qreal radius)
{
    if (radius != this->m_radius)
    {
        this->m_radius = radius;
        emit radiusChanged();
    }
}

void Tepee3DQmlExtensions::LeapCircleGesture::setTurns(qreal turns)
{
    if (turns != this->m_turns)
    {
        this->m_turns = turns;
        emit turnsChanged();
    }
}




Tepee3DQmlExtensions::LeapSwipeGesture::LeapSwipeGesture() :
    QObject(),
    m_state(Tepee3DQmlExtensions::LeapSwipeGesture::SwipeGestureStart),
    m_direction(0,0,0),
    m_position(0,0,0),
    m_startPosition(0,0,0),
    m_speed(0),
    m_id(0)

{
}

Tepee3DQmlExtensions::LeapSwipeGesture::SwipeGestureState Tepee3DQmlExtensions::LeapSwipeGesture::getState() const
{
    return this->m_state;
}

QVector3D Tepee3DQmlExtensions::LeapSwipeGesture::getDirection() const
{
    return this->m_direction;
}

QVector3D Tepee3DQmlExtensions::LeapSwipeGesture::getPosition() const
{
    return this->m_position;
}

QVector3D Tepee3DQmlExtensions::LeapSwipeGesture::getStartPosition() const
{
    return this->m_startPosition;
}

qreal Tepee3DQmlExtensions::LeapSwipeGesture::getSpeed() const
{
    return this->m_speed;
}

int Tepee3DQmlExtensions::LeapSwipeGesture::getId() const
{
    return this->m_id;
}

void Tepee3DQmlExtensions::LeapSwipeGesture::setId(int id)
{
    this->m_id = id;
}

void Tepee3DQmlExtensions::LeapSwipeGesture::setState(Tepee3DQmlExtensions::LeapSwipeGesture::SwipeGestureState state)
{
    if (state != this->m_state)
    {
        this->m_state = state;
        emit stateChanged();
    }
}

void Tepee3DQmlExtensions::LeapSwipeGesture::setDirection(const QVector3D &direction)
{
    if (direction != this->m_direction)
    {
        this->m_direction = direction;
        emit directionChanged();
    }
}

void Tepee3DQmlExtensions::LeapSwipeGesture::setPosition(const QVector3D &position)
{
    if (position != this->m_position)
    {
        this->m_position = position;
        emit positionChanged();
    }
}

void Tepee3DQmlExtensions::LeapSwipeGesture::setStartPosition(const QVector3D &startPosition)
{
    if (startPosition != this->m_startPosition)
    {
        this->m_startPosition = startPosition;
        emit startPositionChanged();
    }
}

void Tepee3DQmlExtensions::LeapSwipeGesture::setSpeed(qreal speed)
{
    if (speed != this->m_speed)
    {
        this->m_speed = speed;
        emit speedChanged();
    }
}


Tepee3DQmlExtensions::LeapTapGesture::LeapTapGesture() :
    QObject(),
    m_id(0),
    m_direction(0,0,0),
    m_position(0,0,0)
{
}

int Tepee3DQmlExtensions::LeapTapGesture::getId() const
{
    return this->m_id;
}

QVector3D Tepee3DQmlExtensions::LeapTapGesture::getDirection() const
{
    return this->m_direction;
}

QVector3D Tepee3DQmlExtensions::LeapTapGesture::getPosition() const
{
    return this->m_position;
}

void Tepee3DQmlExtensions::LeapTapGesture::setId(int id)
{
    this->m_id = id;
}

void Tepee3DQmlExtensions::LeapTapGesture::setPosition(const QVector3D position)
{
    if (position != this->m_position)
    {
        this->m_position = position;
        emit positionChanged();
    }
}

void Tepee3DQmlExtensions::LeapTapGesture::setDirection(const QVector3D direction)
{
    if (direction != this->m_direction)
    {
        this->m_direction = direction;
        emit directionChanged();
    }
}


Tepee3DQmlExtensions::LeapHand::LeapHand(int handID) : QObject(), m_handID(handID)
{
}

Tepee3DQmlExtensions::LeapHand::~LeapHand()
{
}

QVector3D Tepee3DQmlExtensions::LeapHand::getDirection() const
{
    return this->m_direction;
}

qreal Tepee3DQmlExtensions::LeapHand::getPitch() const
{
    return this->m_pitch;
}

qreal Tepee3DQmlExtensions::LeapHand::getRoll() const
{
    return this->m_roll;
}

qreal Tepee3DQmlExtensions::LeapHand::getYaw() const
{
    return this->m_yaw;
}

int Tepee3DQmlExtensions::LeapHand::getHandID() const
{
    return this->m_handID;
}

void Tepee3DQmlExtensions::LeapHand::setDirection(const QVector3D &direction)
{
    if (this->m_direction != direction)
    {
        this->m_direction = direction;
        emit directionChanged();
    }
}

void Tepee3DQmlExtensions::LeapHand::setPitch(qreal pitch)
{
    if (this->m_pitch != pitch)
    {
        this->m_pitch = pitch;
        emit pitchChanged();
    }
}

void Tepee3DQmlExtensions::LeapHand::setRoll(qreal roll)
{
    if (this->m_roll != roll)
    {
        this->m_roll = roll;
        emit rollChanged();
    }
}

void Tepee3DQmlExtensions::LeapHand::setYaw(qreal yaw)
{
    if (this->m_yaw != yaw)
    {
        this->m_yaw = yaw;
        emit yawChanged();
    }
}

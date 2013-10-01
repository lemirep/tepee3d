/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtQml module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
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
** $QT_END_LICENSE$
**
****************************************************************************/


#include <QQuickWindow>
#include <QSGSimpleRectNode>
#include "Tepee3DTouchArea.h"
#include <QEvent>
#include <math.h>
#include <QDebug>

void Tepee3DQmlExtensions::QQuickTouchPoint::setPointId(int id)
{
    if (_id == id)
        return;
    _id = id;
    emit pointIdChanged();
}

void Tepee3DQmlExtensions::QQuickTouchPoint::setX(qreal x)
{
    if (_x == x)
        return;
    _x = x;
    emit xChanged();
}

void Tepee3DQmlExtensions::QQuickTouchPoint::setY(qreal y)
{
    if (_y == y)
        return;
    _y = y;
    emit yChanged();
}

void Tepee3DQmlExtensions::QQuickTouchPoint::setPressure(qreal pressure)
{
    if (_pressure == pressure)
        return;
    _pressure = pressure;
    emit pressureChanged();
}

void Tepee3DQmlExtensions::QQuickTouchPoint::setVelocity(const QVector2D &velocity)
{
    if (_velocity == velocity)
        return;
    _velocity = velocity;
    emit velocityChanged();
}

void Tepee3DQmlExtensions::QQuickTouchPoint::setArea(const QRectF &area)
{
    if (_area == area)
        return;
    _area = area;
    emit areaChanged();
}

void Tepee3DQmlExtensions::QQuickTouchPoint::setPressed(bool pressed)
{
    if (_pressed == pressed)
        return;
    _pressed = pressed;
    emit pressedChanged();
}

void Tepee3DQmlExtensions::QQuickTouchPoint::setStartX(qreal startX)
{
    if (_startX == startX)
        return;
    _startX = startX;
    emit startXChanged();
}

void Tepee3DQmlExtensions::QQuickTouchPoint::setStartY(qreal startY)
{
    if (_startY == startY)
        return;
    _startY = startY;
    emit startYChanged();
}

void Tepee3DQmlExtensions::QQuickTouchPoint::setPreviousX(qreal previousX)
{
    if (_previousX == previousX)
        return;
    _previousX = previousX;
    emit previousXChanged();
}

void Tepee3DQmlExtensions:: QQuickTouchPoint::setPreviousY(qreal previousY)
{
    if (_previousY == previousY)
        return;
    _previousY = previousY;
    emit previousYChanged();
}

void Tepee3DQmlExtensions::QQuickTouchPoint::setSceneX(qreal sceneX)
{
    if (_sceneX == sceneX)
        return;
    _sceneX = sceneX;
    emit sceneXChanged();
}

void Tepee3DQmlExtensions::QQuickTouchPoint::setSceneY(qreal sceneY)
{
    if (_sceneY == sceneY)
        return;
    _sceneY = sceneY;
    emit sceneYChanged();
}

Tepee3DQmlExtensions::QQuickMultiPointTouchArea::QQuickMultiPointTouchArea(QQuickItem *parent)
    : QQuickItem(parent),
      _currentWindow(0),
      _minimumTouchPoints(0),
      _maximumTouchPoints(INT_MAX),
      _stealTouch(false)
{
    setFiltersChildMouseEvents(true);
#ifdef Q_OS_MAC
    connect(this, &QQuickItem::windowChanged, this, &QQuickMultiPointTouchArea::setTouchEventsEnabledForWindow);
#endif
}

Tepee3DQmlExtensions::QQuickMultiPointTouchArea::~QQuickMultiPointTouchArea()
{
    clearTouchLists();
    foreach (QObject *obj, _touchPoints) {
        QQuickTouchPoint *dtp = static_cast<QQuickTouchPoint*>(obj);
        if (!dtp->isQmlDefined())
            delete dtp;
    }
}

int Tepee3DQmlExtensions::QQuickMultiPointTouchArea::minimumTouchPoints() const
{
    return _minimumTouchPoints;
}

void Tepee3DQmlExtensions::QQuickMultiPointTouchArea::setMinimumTouchPoints(int num)
{
    if (_minimumTouchPoints == num)
        return;
    _minimumTouchPoints = num;
    emit minimumTouchPointsChanged();
}

int Tepee3DQmlExtensions::QQuickMultiPointTouchArea::maximumTouchPoints() const
{
    return _maximumTouchPoints;
}

void Tepee3DQmlExtensions::QQuickMultiPointTouchArea::setMaximumTouchPoints(int num)
{
    if (_maximumTouchPoints == num)
        return;
    _maximumTouchPoints = num;
    emit maximumTouchPointsChanged();
}

void Tepee3DQmlExtensions::QQuickMultiPointTouchArea::touchEvent(QTouchEvent *event)
{
    switch (event->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd: {
        //if e.g. a parent Flickable has the mouse grab, don't process the touch events
        QQuickWindow *c = window();
        QQuickItem *grabber = c ? c->mouseGrabberItem() : 0;
        if (grabber && grabber != this && grabber->keepMouseGrab() && grabber->isEnabled()) {
            QQuickItem *item = this;
            while ((item = item->parentItem())) {
                if (item == grabber)
                    return;
            }
        }
        updateTouchData(event);
        if (event->type() == QEvent::TouchEnd) {
            //TODO: move to window
            _stealTouch = false;
            setKeepTouchGrab(false);
            ungrabTouchPoints();
        }
        break;
    }
    default:
        QQuickItem::touchEvent(event);
        break;
    }
}

void Tepee3DQmlExtensions::QQuickMultiPointTouchArea::grabGesture()
{
    _stealTouch = true;

    grabTouchPoints(_touchPoints.keys().toVector());
    setKeepTouchGrab(true);
}

void Tepee3DQmlExtensions::QQuickMultiPointTouchArea::updateTouchData(QEvent *event)
{
    bool ended = false;
    bool moved = false;
    bool started = false;

    clearTouchLists();
    QTouchEvent *e = static_cast<QTouchEvent*>(event);
    QList<QTouchEvent::TouchPoint> touchPoints = e->touchPoints();
    int numTouchPoints = touchPoints.count();
    //always remove released touches, and make sure we handle all releases before adds.
    foreach (const QTouchEvent::TouchPoint &p, touchPoints) {
        Qt::TouchPointState touchPointState = p.state();
        int id = p.id();
        if (touchPointState & Qt::TouchPointReleased) {
            QQuickTouchPoint* dtp = static_cast<QQuickTouchPoint*>(_touchPoints.value(id));
            if (!dtp)
                continue;
            updateTouchPoint(dtp, &p);
            dtp->setPressed(false);
            _releasedTouchPoints.append(dtp);
            _touchPoints.remove(id);
            ended = true;
        }
    }
    if (numTouchPoints >= _minimumTouchPoints && numTouchPoints <= _maximumTouchPoints) {
        foreach (const QTouchEvent::TouchPoint &p, touchPoints) {
            Qt::TouchPointState touchPointState = p.state();
            int id = p.id();
            if (touchPointState & Qt::TouchPointReleased) {
                //handled above
            } else if (!_touchPoints.contains(id)) { //could be pressed, moved, or stationary
                // (we may have just obtained enough points to start tracking them -- in that case moved or stationary count as newly pressed)
                addTouchPoint(&p);
                started = true;
            } else if (touchPointState & Qt::TouchPointMoved) {
                QQuickTouchPoint* dtp = static_cast<QQuickTouchPoint*>(_touchPoints[id]);
                Q_ASSERT(dtp);
                _movedTouchPoints.append(dtp);
                updateTouchPoint(dtp,&p);
                moved = true;
            } else {
                QQuickTouchPoint* dtp = static_cast<QQuickTouchPoint*>(_touchPoints[id]);
                Q_ASSERT(dtp);
                updateTouchPoint(dtp,&p);
            }
        }

        //see if we should be grabbing the gesture
        if (!_stealTouch /* !ignoring gesture*/) {
            bool offerGrab = false;
            const int dragThreshold = qApp->styleHints()->startDragDistance();
            foreach (const QTouchEvent::TouchPoint &p, touchPoints) {
                if (p.state() == Qt::TouchPointReleased)
                    continue;
                const QPointF &currentPos = p.scenePos();
                const QPointF &startPos = p.startScenePos();
                if (qAbs(currentPos.x() - startPos.x()) > dragThreshold)
                    offerGrab = true;
                else if (qAbs(currentPos.y() - startPos.y()) > dragThreshold)
                    offerGrab = true;
                if (offerGrab)
                    break;
            }

            if (offerGrab) {
                QQuickGrabGestureEvent event;
                event._touchPoints = _touchPoints.values();
                emit gestureStarted(&event);
                if (event.wantsGrab())
                    grabGesture();
            }
        }

        if (ended)
            emit released(_releasedTouchPoints);
        if (moved)
            emit updated(_movedTouchPoints);
        if (started)
            emit pressed(_pressedTouchPoints);
        if (ended || moved || started) emit touchUpdated(_touchPoints.values());
    }
}

void Tepee3DQmlExtensions::QQuickMultiPointTouchArea::clearTouchLists()
{
    foreach (QObject *obj, _releasedTouchPoints) {
        QQuickTouchPoint *dtp = static_cast<QQuickTouchPoint*>(obj);
        if (!dtp->isQmlDefined())
            delete dtp;
        else
            dtp->setInUse(false);
    }
    _releasedTouchPoints.clear();
    _pressedTouchPoints.clear();
    _movedTouchPoints.clear();
}

void Tepee3DQmlExtensions::QQuickMultiPointTouchArea::addTouchPoint(const QTouchEvent::TouchPoint *p)
{
    Tepee3DQmlExtensions::QQuickTouchPoint *dtp = 0;
    foreach (QQuickTouchPoint* tp, _touchPrototypes) {
        if (!tp->inUse()) {
            tp->setInUse(true);
            dtp = tp;
            break;
        }
    }

    if (dtp == 0)
        dtp = new QQuickTouchPoint(false);
    dtp->setPointId(p->id());
    updateTouchPoint(dtp,p);
    dtp->setPressed(true);
    _touchPoints.insert(p->id(),dtp);
    _pressedTouchPoints.append(dtp);
}

void Tepee3DQmlExtensions::QQuickMultiPointTouchArea::setTouchEventsEnabledForWindow(QWindow *window)
{
#ifdef Q_OS_MAC
    // Resolve function for enabling touch events from the (cocoa) platform plugin.
    typedef void (*RegisterTouchWindowFunction)(QWindow *, bool);
    RegisterTouchWindowFunction registerTouchWindow = reinterpret_cast<RegisterTouchWindowFunction>(
        QGuiApplication::platformNativeInterface()->nativeResourceFunctionForIntegration("registertouchwindow"));
    if (!registerTouchWindow)
        return; // Not necessarily an error, Qt migh be using a different platform plugin.

    // Disable touch on the old window, enable on the new window.
    if (_currentWindow)
        registerTouchWindow(_currentWindow, false);
    if (window)
        registerTouchWindow(window, true);
    // Save the current window, setTouchEventsEnabledForWindow will be called
    // with a null window on disable.
    _currentWindow = window;
#endif
}

void Tepee3DQmlExtensions::QQuickMultiPointTouchArea::addTouchPrototype(QQuickTouchPoint *prototype)
{
    int id = _touchPrototypes.count();
    prototype->setPointId(id);
    _touchPrototypes.insert(id, prototype);
}

void Tepee3DQmlExtensions::QQuickMultiPointTouchArea::updateTouchPoint(QQuickTouchPoint *dtp, const QTouchEvent::TouchPoint *p)
{
    //TODO: if !qmlDefined, could bypass setters.
    //      also, should only emit signals after all values have been set
    dtp->setX(p->pos().x());
    dtp->setY(p->pos().y());
    dtp->setPressure(p->pressure());
    dtp->setVelocity(p->velocity());
    dtp->setArea(p->rect());
    dtp->setStartX(p->startPos().x());
    dtp->setStartY(p->startPos().y());
    dtp->setPreviousX(p->lastPos().x());
    dtp->setPreviousY(p->lastPos().y());
    dtp->setSceneX(p->scenePos().x());
    dtp->setSceneY(p->scenePos().y());
}

void Tepee3DQmlExtensions::QQuickMultiPointTouchArea::ungrab()
{
    if (_touchPoints.count()) {
        _stealTouch = false;
        setKeepTouchGrab(false);
        foreach (QObject *obj, _touchPoints)
            static_cast<QQuickTouchPoint*>(obj)->setPressed(false);
        emit canceled(_touchPoints.values());
        clearTouchLists();
        foreach (QObject *obj, _touchPoints) {
            QQuickTouchPoint *dtp = static_cast<QQuickTouchPoint*>(obj);
            if (!dtp->isQmlDefined())
                delete dtp;
            else
                dtp->setInUse(false);
        }
        _touchPoints.clear();
        emit touchUpdated(QList<QObject*>());
    }
}

void Tepee3DQmlExtensions::QQuickMultiPointTouchArea::touchUngrabEvent()
{
    ungrab();
}

bool Tepee3DQmlExtensions::QQuickMultiPointTouchArea::childMouseEventFilter(QQuickItem *i, QEvent *event)
{
    if (!isEnabled() || !isVisible())
        return QQuickItem::childMouseEventFilter(i, event);
    switch (event->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
        if (!shouldFilter(event))
            return false;
        updateTouchData(event);
        return _stealTouch;
    case QEvent::TouchEnd: {
            if (!shouldFilter(event))
                return false;
            updateTouchData(event);
            //TODO: verify this behavior
            _stealTouch = false;
            setKeepTouchGrab(false);
            ungrabTouchPoints();
        }
        break;
    default:
        break;
    }
    return QQuickItem::childMouseEventFilter(i, event);
}

bool Tepee3DQmlExtensions::QQuickMultiPointTouchArea::shouldFilter(QEvent *event)
{
    QQuickWindow *c = window();
    QQuickItem *grabber = c ? c->mouseGrabberItem() : 0;
    bool disabledItem = grabber && !grabber->isEnabled();
    bool stealThisEvent = _stealTouch;
    bool containsPoint = false;
    if (!stealThisEvent) {
        switch (event->type()) {
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd: {
                QTouchEvent *te = static_cast<QTouchEvent*>(event);
                foreach (const QTouchEvent::TouchPoint &point, te->touchPoints()) {
                    if (contains(mapFromScene(point.scenePos()))) {
                        containsPoint = true;
                        break;
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    if ((stealThisEvent || containsPoint) && (!grabber || !grabber->keepTouchGrab() || disabledItem)) {
        return true;
    }
    ungrab();
    return false;
}

QSGNode *Tepee3DQmlExtensions::QQuickMultiPointTouchArea::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data)
{
    Q_UNUSED(data);

    QSGSimpleRectNode *rectangle = static_cast<QSGSimpleRectNode *>(oldNode);
    if (!rectangle)
        rectangle = new QSGSimpleRectNode();
    rectangle->setRect(QRectF(0, 0, width(), height()));
    rectangle->setColor(QColor(255, 0, 0, 50));
    this->update();
    return rectangle;
}



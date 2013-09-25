#include "LeapMotionListener.h"
#include <QDebug>

LeapMotionListener::LeapMotionListener() : QObject(), Leap::Listener()
{
    this->touchPoints = QList<QTouchEvent::TouchPoint>();
    this->mousePressed = false;
    this->primaryScreen = QGuiApplication::primaryScreen();
}

LeapMotionListener::~LeapMotionListener()
{
}

void LeapMotionListener::swipeGestureHandler(const Leap::Gesture &gesture, const Leap::Frame &frame)
{
    Leap::SwipeGesture swipe = gesture;
    qDebug() << "Swipe Gesture >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
}

void LeapMotionListener::circleGestureHandler(const Leap::Gesture &gesture, const Leap::Frame &frame)
{
    Leap::CircleGesture circle = gesture;
    qDebug() << "Circle Gesture >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
}

void LeapMotionListener::keyTapGestureHandler(const Leap::Gesture &gesture, const Leap::Frame &frame)
{
    Leap::KeyTapGesture keyTap = gesture;
    qDebug() << "KeyTap Gesture >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
}

void LeapMotionListener::screenTapGestureHandler(const Leap::Gesture &gesture, const Leap::Frame &frame)
{
    qDebug() << "ScreenTap Gesture >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
    Leap::ScreenTapGesture screenTap = gesture;
    QPointF globalPointerPos = this->convertPointablePosToScreenPos(frame.interactionBox(), screenTap.pointable());
    QPointF localPointerPos = this->convertGlobalPosToLocalPos(globalPointerPos);

    QCursor ::setPos(globalPointerPos.toPoint());
    //    QCoreApplication::postEvent(this->targetListener, new QMouseEvent(QMouseEvent::MouseButtonPress,
    //                                                                      localPointerPos,
    //                                                                      globalPointerPos,
    //                                                                      Qt::LeftButton,
    //                                                                      Qt::LeftButton,
    //                                                                      Qt::NoModifier));
    //    QCoreApplication::postEvent(this->targetListener, new QMouseEvent(QMouseEvent::MouseButtonRelease,
    //                                                                      localPointerPos,
    //                                                                      globalPointerPos,
    //                                                                      Qt::LeftButton,
    //                                                                      Qt::LeftButton,
    //                                                                      Qt::NoModifier));
}

void LeapMotionListener::handleMouseEvents(const Leap::Frame &frame)
{
    // FRONT MOST FINGER / POINTABLE WILL ACT AS THE MOUSE
    // IF FRONT MOST FINDER IS IN HOVERING ZONE -> HOVER : MOUSE MOVE OR BUTTON RELEASE IF ONE WAS PRESSED
    // IF FRONT MOST FINGER IS IN THE TOUCH ZONE -> MOUSE BUTTON PRESS

    /////// MOUSE EVENTS /////////
    // MOUSE BUTTON PRESSED
    // MOUSE BUTTON RELEASED
    // MOUSE MOVE

    if (this->inputListeners.empty())
        return ;


    Leap::Pointable pointer = frame.fingers().frontmost();

    if (!pointer.isValid())
        return ;

    QMouseEvent::Type frameMouseEvent = QMouseEvent::None;
    QPointF globalPointerPos = this->convertPointablePosToScreenPos(frame.interactionBox(), pointer);
    QPointF localPointerPos = this->convertGlobalPosToLocalPos(globalPointerPos);
    Qt::MouseButton button = Qt::NoButton;

    // FINGER TOUCHING AND NO PREVIOUS PRESS -> SETTING BUTTON PRESS
    if (pointer.touchDistance() <= 0 &&
            pointer.touchZone() == Leap::Pointable::ZONE_TOUCHING &&
            !this->mousePressed)
    {
        qDebug() << "Press";
        this->mousePressed = true;
        frameMouseEvent = QMouseEvent::MouseButtonPress;
        button = Qt::LeftButton;
    }

    // FINGER NOT TOUCHING AND PREVIOUS PRESS -> RELEASING BUTTON PRESS
    if (pointer.touchDistance() > 0 &&
            pointer.touchZone() == Leap::Pointable::ZONE_HOVERING &&
            this->mousePressed)
    {
        qDebug() << "Release";
        frameMouseEvent = QMouseEvent::MouseButtonRelease;
        this->mousePressed = false;
        button = Qt::LeftButton;
    }

    // FINGER IN TOUCHING OR HOVERING ZONE AND NO BUTTON PRESS / RELEASE CHANGE -> MouseMove
    if (pointer.touchZone() != Leap::Pointable::ZONE_NONE &&
            frameMouseEvent == QMouseEvent::None)
    {
        //        qDebug() << "Move";
        frameMouseEvent = QMouseEvent::MouseMove;
        QCursor ::setPos(globalPointerPos.toPoint());
    }

    if (frameMouseEvent != QMouseEvent::None)
    {
        foreach (QObject *listener, this->inputListeners)
            QCoreApplication::postEvent(listener, new QMouseEvent(frameMouseEvent,
                                                                  localPointerPos,
                                                                  globalPointerPos,
                                                                  button,
                                                                  button,
                                                                  Qt::NoModifier));
    }
}

void LeapMotionListener::handleTouchEvents(const Leap::Frame &frame)
{
    if (this->inputListeners.empty())
        return ;
    /////// TOUCH EVENTS /////////
    // TOUCHBEGIN
    // TOUCHUPDATE
    // TOUCHEND
    // TOUCHCANCEL

    QTouchEvent::Type frameTouchEvent = QTouchEvent::None;
    QList<Leap::Pointable> touchingPointables;

    // RETRIEVE ONLY VALID AND TOUCHING POINTS
    for (int i = 0; i < frame.pointables().count(); i++)
    {
        const Leap::Pointable pointer = frame.pointables()[i];
        if (pointer.touchDistance() <= 0.5 && // IF TOO SENSISBLE CHANGE 0 FOR A VALUE LIKE 0.5 OR 0.75
                pointer.touchZone() != Leap::Pointable::ZONE_NONE &&
                pointer.isValid())
            touchingPointables.append(pointer);
    }

    int pointCountDiff = touchingPointables.count() - this->touchPoints.size();

    //    qDebug() << "Points : " << touchingPointables.size();
    //    qDebug() << "Diff " << pointCountDiff;

    if (pointCountDiff == 0 && !this->touchPoints.empty()) // SAME AMOUT OF POINTS AS PREVIOUS FRAME AND MORE THAN 0 POINTS
    {
        qDebug() << "Touch Update";
        frameTouchEvent = QTouchEvent::TouchUpdate;
    }
    else if (pointCountDiff < 0) // LESS POINTS PRESSED THAN PREVIOUS FRAME
    {
        if (touchingPointables.count() == 0) // NO MORE TOUCHING POINTS
        {
            qDebug() << "Touch End";
            frameTouchEvent = QTouchEvent::TouchEnd;
        }
        else
        {
            qDebug() << "Touch Cancel";
            frameTouchEvent = QTouchEvent::TouchCancel;
        }
    }
    else if (pointCountDiff > 0 && this->touchPoints.empty()) // MORE POINTS IN CURRENT FRAME THAN PREVIOUS
    {
        qDebug() << "Touch Begin";
        frameTouchEvent = QTouchEvent::TouchBegin;
    }

    // SET TOUCH POINTS LIST IF TOUCHBEGIN OR TOUCHUPDATE
    if (frameTouchEvent != QTouchEvent::TouchCancel) // NO NEED TO TEST FOR TOUCHEND AS touchPointables == 0 IN THAT CASE
        for (int i = 0; i < touchingPointables.count(); i++)
        {
            Leap::Pointable pointer = touchingPointables[i];
            Leap::Vector normalizedPointerPos = frame.interactionBox().normalizePoint(pointer.stabilizedTipPosition());
            QPointF globalPointerPos = this->convertPointablePosToScreenPos(normalizedPointerPos);
            QPointF localPointerPos = this->convertGlobalPosToLocalPos(globalPointerPos);
            QTouchEvent::TouchPoint touchPoint(pointer.id());

            // RETRIEVE LAST TOUCH EVENT MATCHING POINTABLE ID IF IT EXISTS
            for (int j = 0; j < this->touchPoints.size(); j++)
            {
                if (this->touchPoints[j].id() == pointer.id())
                {
                    touchPoint = this->touchPoints.takeAt(j);
                    touchPoint.setLastPos(touchPoint.pos());
                    touchPoint.setLastScreenPos(touchPoint.screenPos());
                    //                    touchPoint.setLastNormalizedPos(touchPoint.normalizedPos());
                }
            }

            // IF START OF MOUVEMENT, SET STARTING POS OF TOUCH EVENT
            if (frameTouchEvent == QTouchEvent::TouchBegin)
            {
                touchPoint.setStartPos(localPointerPos);
                touchPoint.setStartScreenPos(globalPointerPos);
                //                touchPoint.setStartNormalizedPos(QPointF(normalizedPointerPos.x, normalizedPointerPos.y));
                //                if (frame.pointables().frontmost() == pointer)
                //                    touchPoint.setPrimary(true);
            }
            // SET ALL ATTRIBUTES THAT NEED TO BE SET OR UPDATED
            touchPoint.setPos(localPointerPos);
            touchPoint.setScreenPos(globalPointerPos);
            touchPoint.setPressure(pointer.touchDistance());
            this->touchPoints.prepend(touchPoint);
            //            touchPoint.setNormalizedPos(QPointF(normalizedPointerPos.x, normalizedPointerPos.y));
        }

    // CLEAR TOUCH POINTS ON TOUCHEND OR TOUCHCANCEL
    if (frameTouchEvent == QTouchEvent::TouchEnd || frameTouchEvent == QTouchEvent::TouchCancel)
        this->touchPoints.clear();

    // TRANSMIT EVENT TO TARGETLISTENER IF THE EVENT IS VALID
    if (frameTouchEvent != QTouchEvent::None)
        foreach (QObject *listener, this->inputListeners)
            QCoreApplication::postEvent(listener,
                                        new QTouchEvent(frameTouchEvent,
                                                        NULL,
                                                        //                                                        LeapMotionTouchDevice::getInstance(),
                                                        Qt::NoModifier,
                                                        0,
                                                        touchPoints));
}

QPointF LeapMotionListener::convertPointablePosToScreenPos(const Leap::InteractionBox &interactionBox,
                                                           const Leap::Pointable &pointable)
{
    Leap::Vector normalizedPos = interactionBox.normalizePoint(pointable.stabilizedTipPosition());
    return this->convertPointablePosToScreenPos(normalizedPos);
}

QPointF LeapMotionListener::convertPointablePosToScreenPos(const Leap::Vector &normalizedPos)
{
    return QPointF(normalizedPos.x * 1920,
                   (1 - normalizedPos.y) * 1080);
    //    return QPointF(normalizedPos.x * this->primaryScreen->geometry().x(),
    //                   (1 - normalizedPos.y) * this->primaryScreen->geometry().y());
}

QPointF LeapMotionListener::convertGlobalPosToLocalPos(const QPointF &globalPos)
{
    //    return QPointF(this->primaryScreen->m(globalPos.toPoint()));
    return globalPos;
}

void LeapMotionListener::onInit(const Leap::Controller &controller)
{
    qDebug() << "On Listener Init";
    // SET SUPPORTED GESTURES WE WANT TO HANDLE
    controller.enableGesture(Leap::Gesture::TYPE_CIRCLE, true);
    controller.enableGesture(Leap::Gesture::TYPE_SWIPE, true);
    controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP, true);
    controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP, true);

    this->gestureHandlers[Leap::Gesture::TYPE_SWIPE] = &LeapMotionListener::swipeGestureHandler;
    this->gestureHandlers[Leap::Gesture::TYPE_CIRCLE] = &LeapMotionListener::circleGestureHandler;
    this->gestureHandlers[Leap::Gesture::TYPE_KEY_TAP] = &LeapMotionListener::keyTapGestureHandler;
    this->gestureHandlers[Leap::Gesture::TYPE_SCREEN_TAP] = &LeapMotionListener::screenTapGestureHandler;
}

void LeapMotionListener::onConnect(const Leap::Controller &)
{
    qDebug() << "On Listener Connect";
}

void LeapMotionListener::onDisconnect(const Leap::Controller &)
{
    qDebug() << "On Listener Disonnect";
}

void LeapMotionListener::onExit(const Leap::Controller &)
{
    qDebug() << "On Listener Exit";
}

void LeapMotionListener::onFrame(const Leap::Controller &controller)
{
    Leap::Frame frame = controller.frame();

    //    QCoreApplication::postEvent(this->targetListener, new QMouseEvent(QMouseEvent::MouseButtonPress,
    //                                                                      QPointF(50, 400),
    //                                                                      Qt::LeftButton,
    //                                                                      Qt::LeftButton,
    //                                                                      Qt::NoModifier));
    //    QCoreApplication::postEvent(this->targetListener, new QMouseEvent(QMouseEvent::MouseButtonRelease,
    //                                                                      QPointF(50, 400),
    //                                                                      Qt::LeftButton,
    //                                                                      Qt::LeftButton,
    //                                                                      Qt::NoModifier));

    //    qDebug() << "On Listener Frame";
    if (frame.isValid())
    {
        // RETRIEVE FINGER INFORMATIONS AND CONVERT THEM TO MOUSE AND TOUCH EVENTS
        this->handleMouseEvents(frame);
        //        this->handleTouchEvents(frame);

        // ANALYSE FRAME GESTURES AND CALL TARGETS THAT ARE QTQUICK PLUGINS
        // CREATE FOR QTQUICK PLUGINS (ONE FOR EACH GESTURE)
        // IMPLEMENT ADD TARGET FOR THIS PLUGINS SO THAT THEY CAN REGISTER TO THIS SERVICE
        // FOR EACH GESTURE IN A FRAME, CHECK IF QTQUICK PLUGIN HAS IMPLEMENT GESTURE TYPE AND IF GESTURE OCCURED WITHIN THE QTQUICK PLUGIN AREA
        // IF SO TRIGGER CALLBACK IN QTQUICK PLUGIN
        /////// LEAP MOTION GESTURES ////////
        // SCREEN TAP
        // SWIPE
        // CIRCLE
        // KEY TAP
        // frame.gestures CONTAINS ALL GESTURES OF THE CURRENT FRAME
        for (int i = 0; i < frame.gestures().count(); i++)
        {
            Leap::Gesture gesture = frame.gestures()[i];
            if (gesture.isValid() && this->gestureHandlers.contains(gesture.type()))
                (this->*this->gestureHandlers[gesture.type()])(gesture, frame);
        }
    }
}

void LeapMotionListener::onFocusGained(const Leap::Controller &)
{
    qDebug() << "On Listener FocusGained";
}

void LeapMotionListener::onFocusLost(const Leap::Controller &)
{
    qDebug() << "On Listener FocusLost";
}

void LeapMotionListener::addInputListener(QObject *target)
{
    if ((qobject_cast<QQuickItem *>(target) != NULL ||
         qobject_cast<QWindow*>(target) != NULL) &&
            !this->inputListeners.contains(target))
        this->inputListeners.append(target);
}

void LeapMotionListener::removeInputListener(QObject *target)
{
    if (target != NULL && this->inputListeners.contains(target))
        this->inputListeners.removeAll(target);
}

void LeapMotionListener::addGestureListener(QObject *listener)
{
    if ((qobject_cast<QQuickItem *>(listener) != NULL ||
         qobject_cast<QWindow*>(listener) != NULL) &&
            !this->inputListeners.contains(listener))
        this->inputListeners.append(listener);
}

void LeapMotionListener::removeGestureListener(QObject *listener)
{
    if (listener != NULL && this->inputListeners.contains(listener))
        this->inputListeners.removeAll(listener);
}



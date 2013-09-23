#include "LeapMotionListener.h"
#include <QDebug>

LeapMotionListener::LeapMotionListener() : QObject(), Leap::Listener()
{
    this->targetListener = NULL;
    this->touchPoints = QList<QTouchEvent::TouchPoint>();
    this->mousePressed = false;
}

LeapMotionListener::~LeapMotionListener()
{
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

    if (this->targetListener == NULL)
        return ;

    Leap::Pointable pointer = frame.fingers().frontmost();

    if (!pointer.isValid())
        return ;

    QMouseEvent::Type frameMouseEvent = QMouseEvent::None;
    QPointF globalPointerPos = this->convertPointablePosToScreenPos(frame.interactionBox(), pointer);
    QPointF localPointerPos = this->convertGlobalPosToLocalPos(globalPointerPos);

    // FINGER TOUCHING AND NO PREVIOUS PRESS -> SETTING BUTTON PRESS
    if (pointer.touchDistance() <= 0 &&
            pointer.touchZone() == Leap::Pointable::ZONE_TOUCHING &&
            !mousePressed)
        frameMouseEvent = QMouseEvent::MouseButtonPress;

    // FINGER NOT TOUCHING AND PREVIOUS PRESS -> RELEASING BUTTON PRESS
    if (pointer.touchDistance() > 0 &&
            pointer.touchZone() == Leap::Pointable::ZONE_HOVERING &&
            mousePressed)
        frameMouseEvent = QMouseEvent::MouseButtonRelease;

    // FINGER IN TOUCHING OR HOVERING ZONE AND NO BUTTON PRESS / RELEASE CHANGE -> MouseMove
    if (pointer.touchZone() != Leap::Pointable::ZONE_NONE &&
            frameMouseEvent == QMouseEvent::None)
        frameMouseEvent = QMouseEvent::MouseMove;

    if (frameMouseEvent != QMouseEvent::None)
        QCoreApplication::postEvent(this->targetListener, new QMouseEvent(frameMouseEvent,
                                                                          localPointerPos,
                                                                          globalPointerPos,
                                                                          Qt::LeftButton,
                                                                          Qt::LeftButton,
                                                                          Qt::NoModifier));
}

void LeapMotionListener::handleTouchEvents(const Leap::Frame &frame)
{
    if (this->targetListener == NULL)
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
        if (pointer.touchDistance() <= 0 && // IF TOO SENSISBLE CHANGE 0 FOR A VALUE LIKE 0.5 OR 0.75
                pointer.touchZone() == Leap::Pointable::ZONE_TOUCHING &&
                pointer.isValid())
            touchingPointables.append(pointer);
    }

    int pointCountDiff = touchingPointables.count() - this->touchPoints.size();

    if (pointCountDiff == 0 && !this->touchPoints.empty()) // SAME AMOUT OF POINTS AS PREVIOUS FRAME AND MORE THAN 0 POINTS
        frameTouchEvent = QTouchEvent::TouchUpdate;
    else if (pointCountDiff < 0) // LESS POINTS PRESSED THAN PREVIOUS FRAME
        if (touchingPointables.count() == 0) // NO MORE TOUCHING POINTS
            frameTouchEvent = QTouchEvent::TouchEnd;
        else
            frameTouchEvent = QTouchEvent::TouchCancel;
    else if (this->touchPoints.empty()) // MORE POINTS IN CURRENT FRAME THAN PREVIOUS
        frameTouchEvent = QTouchEvent::TouchBegin;

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
                    touchPoint.setLastNormalizedPos(touchPoint.normalizedPos());
                }
            }

            // IF START OF MOUVEMENT, SET STARTING POS OF TOUCH EVENT
            if (frameTouchEvent == QTouchEvent::TouchBegin)
            {
                touchPoint.setStartPos(localPointerPos);
                touchPoint.setStartScreenPos(globalPointerPos);
                touchPoint.setStartNormalizedPos(QPointF(normalizedPointerPos.x, normalizedPointerPos.y));
                //                if (frame.pointables().frontmost() == pointer)
                //                    touchPoint.setPrimary(true);
            }
            // SET ALL ATTRIBUTES THAT NEED TO BE SET OR UPDATED
            touchPoint.setPos(localPointerPos);
            touchPoint.setScreenPos(globalPointerPos);
            touchPoint.setPressure(pointer.touchDistance());
            touchPoint.setNormalizedPos(QPointF(normalizedPointerPos.x, normalizedPointerPos.y));
        }

    // CLEAR TOUCH POINTS ON TOUCHEND OR TOUCHCANCEL
    if (frameTouchEvent == QTouchEvent::TouchEnd || frameTouchEvent == QTouchEvent::TouchCancel)
        this->touchPoints.clear();

    // TRANSMIT EVENT TO TARGETLISTENER IF THE EVENT IS VALID
    if (frameTouchEvent != QTouchEvent::None)
        QCoreApplication::postEvent(this->targetListener,
                                    new QTouchEvent(frameTouchEvent,
                                                    LeapMotionTouchDevice::getInstance(),
                                                    Qt::NoModifier,
                                                    0,
                                                    touchPoints));
}

QPointF LeapMotionListener::convertPointablePosToScreenPos(const Leap::InteractionBox &interactionBox,
                                                           const Leap::Pointable &pointable)
{
    Leap::Vector normalizedPos = interactionBox.normalizePoint(pointable.stabilizedTipPosition());
    return QPointF(normalizedPos.x * this->targetListener->width(),
                   this->targetListener->height() - normalizedPos.y * this->targetListener->height());
}

QPointF LeapMotionListener::convertPointablePosToScreenPos(const Leap::Vector &normalizedPos)
{
    return QPointF(normalizedPos.x * this->targetListener->width(),
                   this->targetListener->height() - normalizedPos.y * this->targetListener->height());
}

QPointF LeapMotionListener::convertGlobalPosToLocalPos(const QPointF &globalPos)
{
    return QPointF(this->targetListener->mapFromGlobal(globalPos.toPoint()));
}

void LeapMotionListener::onInit(const Leap::Controller &)
{
    qDebug() << "On Listener Init";
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

    qDebug() << "On Listener Frame";
    if (frame.isValid())
    {
        // RETRIEVE FINGER INFORMATIONS AND CONVERT THEM TO MOUSE AND TOUCH EVENTS
        this->handleMouseEvents(frame);
        this->handleTouchEvents(frame);

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

void LeapMotionListener::setTargetListener(QObject *target)
{
    this->targetListener = qobject_cast<QWindow*>(target);
}



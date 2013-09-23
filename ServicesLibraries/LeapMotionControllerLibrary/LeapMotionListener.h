#ifndef LEAPMOTIONLISTENER_H
#define LEAPMOTIONLISTENER_H

#include <QObject>
#include <QList>
#include <QCoreApplication>
#include <QWindow>
#include <QTouchEvent>
#include <QMouseEvent>
#include "LeapMotionTouchDevice.h"
#include "Leap.h"

class LeapMotionListener : public QObject, public Leap::Listener
{
    Q_OBJECT

public :
    LeapMotionListener();
    ~LeapMotionListener();

private :
    QWindow* targetListener;
    QList<QTouchEvent::TouchPoint> touchPoints;
    bool                           mousePressed;

    void handleMouseEvents(const Leap::Frame &frame);
    void handleTouchEvents(const Leap::Frame &frame);
    QPointF convertPointablePosToScreenPos(const Leap::InteractionBox &interactionBox,
                                        const Leap::Pointable &pointable);
    QPointF convertPointablePosToScreenPos(const Leap::Vector &normalizedPos);
    QPointF convertGlobalPosToLocalPos(const QPointF &globalPos);
    // Listener interface
public:
    void onInit(const Leap::Controller &);
    void onConnect(const Leap::Controller &);
    void onDisconnect(const Leap::Controller &);
    void onExit(const Leap::Controller &);
    void onFrame(const Leap::Controller &);
    void onFocusGained(const Leap::Controller &);
    void onFocusLost(const Leap::Controller &);

public:
    void    setTargetListener(QObject *target);
};

#endif // LEAPMOTIONLISTENER_H

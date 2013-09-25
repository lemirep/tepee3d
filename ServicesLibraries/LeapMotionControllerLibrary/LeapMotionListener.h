#ifndef LEAPMOTIONLISTENER_H
#define LEAPMOTIONLISTENER_H

#include <QObject>
#include <QList>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QWindow>
#include <QTouchEvent>
#include <QMouseEvent>
#include <QHash>
#include <QQuickItem>
#include "LeapMotionTouchDevice.h"
#include "Leap.h"

class LeapMotionListener : public QObject, public Leap::Listener
{
    Q_OBJECT

public :
    LeapMotionListener();
    ~LeapMotionListener();

private :
    QList<QObject*> inputListeners;
    QList<QObject*> gesturesListeners;
    QScreen         *primaryScreen;

    QList<QTouchEvent::TouchPoint> touchPoints;
    bool                           mousePressed;
    QHash<Leap::Gesture::Type, void (LeapMotionListener::*)(const Leap::Gesture &gesture, const Leap::Frame &frame)> gestureHandlers;

    void swipeGestureHandler(const Leap::Gesture &gesture, const Leap::Frame & frame);
    void circleGestureHandler(const Leap::Gesture &gesture, const Leap::Frame & frame);
    void keyTapGestureHandler(const Leap::Gesture &gesture, const Leap::Frame & frame);
    void screenTapGestureHandler(const Leap::Gesture &gesture, const Leap::Frame & frame);

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
    void    addInputListener(QObject *target);
    void    removeInputListener(QObject *target);
    void    addGestureListener(QObject *listener);
    void    removeGestureListener(QObject *listener);
};

#endif // LEAPMOTIONLISTENER_H

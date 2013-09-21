#ifndef LEAPMOTIONLISTENER_H
#define LEAPMOTIONLISTENER_H

#include <QObject>
#include <QList>
#include <QWidget>
#include <QWindow>
#include "Leap.h"

class LeapMotionListener : public QObject, public Leap::Listener
{
    Q_OBJECT

public :
    LeapMotionListener();
    ~LeapMotionListener();

private :
    QList<QObject*> targetListeners;

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
    void    addTargetListener(QObject *target);
    void    removeTargetListener(QObject *target);
};

#endif // LEAPMOTIONLISTENER_H

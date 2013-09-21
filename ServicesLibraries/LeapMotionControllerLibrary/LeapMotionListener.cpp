#include "LeapMotionListener.h"
#include <QDebug>

LeapMotionListener::LeapMotionListener() : QObject(), Leap::Listener()
{
}

LeapMotionListener::~LeapMotionListener()
{
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

void LeapMotionListener::onFrame(const Leap::Controller &)
{
    qDebug() << "On Listener Frame";
}

void LeapMotionListener::onFocusGained(const Leap::Controller &)
{
    qDebug() << "On Listener FocusGained";
}

void LeapMotionListener::onFocusLost(const Leap::Controller &)
{
    qDebug() << "On Listener FocusLost";
}

void LeapMotionListener::addTargetListener(QObject *target)
{
    if (qobject_cast<QWidget*>(target) != NULL ||
            qobject_cast<QWindow*>(target) != NULL)
        this->targetListeners.append(target);
}

void LeapMotionListener::removeTargetListener(QObject *target)
{
    if (target == NULL)
        return ;
    int index = this->targetListeners.indexOf(target);
    if (index != -1)
        this->targetListeners.removeAt(index);
}

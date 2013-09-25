#ifndef LEAPGESTUREAREA_H
#define LEAPGESTUREAREA_H

#include <QQuickItem>
#include <QQmlContext>
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
    // QQmlParserStatus interface
    void componentComplete();

    // LeapMotionServiceUserInterface interface
signals:
    void registerToLeapMotionGestures(QObject *listener);
    void unregisterFromLeapMotionGestures(QObject *listener);
};
}

#endif // LEAPGESTUREAREA_H

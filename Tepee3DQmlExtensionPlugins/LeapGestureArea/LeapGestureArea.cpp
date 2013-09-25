#include "LeapGestureArea.h"

Tepee3DQmlExtensions::LeapGestureArea::LeapGestureArea(QQuickItem *parent) : QQuickItem(parent)
{
//    Services::ServiceManager::getInstance()->connectObjectToServices(this);
}

Tepee3DQmlExtensions::LeapGestureArea::~LeapGestureArea()
{
    emit unregisterFromLeapMotionGestures(this);
}

void Tepee3DQmlExtensions::LeapGestureArea::componentComplete()
{
    qDebug() << "Connection Item to Leap Motion";
    emit registerToLeapMotionGestures(this);
}

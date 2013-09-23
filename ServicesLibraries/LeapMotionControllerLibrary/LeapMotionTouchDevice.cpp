#include "LeapMotionTouchDevice.h"

LeapMotionTouchDevice * LeapMotionTouchDevice::instance = NULL;

LeapMotionTouchDevice *LeapMotionTouchDevice::getInstance()
{
    if (LeapMotionTouchDevice::instance == NULL)
        LeapMotionTouchDevice::instance = new LeapMotionTouchDevice();
    return LeapMotionTouchDevice::instance;
}

LeapMotionTouchDevice::~LeapMotionTouchDevice()
{
    LeapMotionTouchDevice::instance = NULL;
}

QTouchDevice::Capabilities LeapMotionTouchDevice::capabilities() const
{
    return QTouchDevice::Position|QTouchDevice::Pressure|QTouchDevice::NormalizedPosition;
}

QTouchDevice::DeviceType LeapMotionTouchDevice::type() const
{
    return QTouchDevice::TouchScreen;
}

QString LeapMotionTouchDevice::name() const
{
    return QString("Leap Motion");
}

LeapMotionTouchDevice::LeapMotionTouchDevice() : QTouchDevice()
{
}


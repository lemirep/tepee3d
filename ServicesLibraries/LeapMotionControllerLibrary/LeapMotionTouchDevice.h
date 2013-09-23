#ifndef LEAPMOTIONTOUCHDEVICE_H
#define LEAPMOTIONTOUCHDEVICE_H

#include <QTouchDevice>

class LeapMotionTouchDevice : public QTouchDevice
{
public:
    static LeapMotionTouchDevice *getInstance();
    ~LeapMotionTouchDevice();

    QTouchDevice::Capabilities capabilities() const;
    QTouchDevice::DeviceType type() const;
    QString name() const;

private:
    static LeapMotionTouchDevice *instance;
    LeapMotionTouchDevice();

};

#endif // LEAPMOTIONTOUCHDEVICE_H

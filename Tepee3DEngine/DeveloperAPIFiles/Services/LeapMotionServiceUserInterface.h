#ifndef LEAPMOTIONSERVICEUSERINTERFACE_H
#define LEAPMOTIONSERVICEUSERINTERFACE_H

namespace Services
{

class LeapMotionServiceInputUserInterface
{
public :
    // REGISTER SIGNAL
    virtual void    registerToLeapMotionInputs(QObject *listener) = 0;
    virtual void    unregisterFromLeapMotionInputs(QObject *listener) = 0;
};

class LeapMotionServiceGestureUserInterface
{
public :
    // REGISTER SIGNAL
    virtual void    registerToLeapMotionGestures(QObject *listener) = 0;
    virtual void    unregisterFromLeapMotionGestures(QObject *listener) = 0;
};

}
Q_DECLARE_INTERFACE(Services::LeapMotionServiceInputUserInterface, "com.tepee3d.Services.LeapMotionServiceInputUserInterface/1.0")
Q_DECLARE_INTERFACE(Services::LeapMotionServiceGestureUserInterface, "com.tepee3d.Services.LeapMotionServiceGestureUserInterface/1.0")

#endif // LEAPMOTIONSERVICEUSERINTERFACE_H

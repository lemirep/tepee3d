#ifndef LEAPMOTIONSERVICEUSERINTERFACE_H
#define LEAPMOTIONSERVICEUSERINTERFACE_H

namespace Services
{
class LeapMotionServiceUserInterface
{
public :
    // REGISTER SIGNAL
    void    registerToLeapMotionInputs(QObject *targetListener);
    // UNREGISTER SIGNAL
    void    unregisterFromLeapMotionInputs(QObject *targetListener);
};
}
Q_DECLARE_INTERFACE(Services::LeapMotionServiceUserInterface, "com.tepee3d.Services.LeapMotionServiceUserInterface/1.0")

#endif // LEAPMOTIONSERVICEUSERINTERFACE_H

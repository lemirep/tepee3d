#ifndef LEAPMOTIONSERVICEUSERINTERFACE_H
#define LEAPMOTIONSERVICEUSERINTERFACE_H

namespace Services
{
class LeapMotionServiceUserInterface
{
public :
    // REGISTER SIGNAL
    virtual void    registerToLeapMotionInputs(QObject *targetListener) = 0;
};
}
Q_DECLARE_INTERFACE(Services::LeapMotionServiceUserInterface, "com.tepee3d.Services.LeapMotionServiceUserInterface/1.0")

#endif // LEAPMOTIONSERVICEUSERINTERFACE_H

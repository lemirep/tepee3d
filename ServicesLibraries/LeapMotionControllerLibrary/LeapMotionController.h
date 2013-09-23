#ifndef LEAPMOTIONCONTROLLER_H
#define LEAPMOTIONCONTROLLER_H


#include <QObject>
#include "Leap.h"
#include "LeapMotionListener.h"

class LeapMotionController : public QObject
{
    Q_OBJECT

private :
    LeapMotionController(QObject *parent = 0);

    static LeapMotionController *instance;
    LeapMotionListener *leapListener;
    Leap::Controller   *leapController;

public:
    ~LeapMotionController();

    static LeapMotionController *getInstance();

public slots:
    void    registerTargetListenerToLeapMotionInputs(QObject *targetListener);
};

#endif // LEAPMOTIONCONTROLLER_H

#include "LeapMotionController.h"

LeapMotionController * LeapMotionController::instance = NULL;

LeapMotionController::LeapMotionController(QObject *parent) : QObject(parent)
{
    this->leapController = new Leap::Controller();
    this->leapListener = new LeapMotionListener();
    // SET SUPPORTED GESTURES WE WANT TO HANDLE
    this->leapController->enableGesture(Leap::Gesture::TYPE_CIRCLE, true);
    this->leapController->enableGesture(Leap::Gesture::TYPE_SWIPE, true);
    this->leapController->enableGesture(Leap::Gesture::TYPE_SCREEN_TAP, true);
    this->leapController->enableGesture(Leap::Gesture::TYPE_KEY_TAP, true);
    // ADD LISTENER TO LEAP CONTROLLER
    this->leapController->addListener(*this->leapListener);
}

LeapMotionController::~LeapMotionController()
{
    this->leapController->removeListener(*this->leapListener);
    delete this->leapListener;
    delete this->leapController;
}


LeapMotionController *LeapMotionController::getInstance()
{
    if (LeapMotionController::instance == NULL)
        LeapMotionController::instance = new LeapMotionController();
    return LeapMotionController::instance;
}

void LeapMotionController::registerTargetListenerToLeapMotionInputs(QObject *targetListener)
{
    this->leapListener->addTargetListener(targetListener);
}

void LeapMotionController::unregisterTargetListenerFromLeapMotionInputs(QObject *targetListener)
{
    this->leapListener->removeTargetListener(targetListener);
}

#include "LeapMotionController.h"

LeapMotionController * LeapMotionController::instance = NULL;

LeapMotionController::LeapMotionController(QObject *parent) : QObject(parent)
{
    this->leapController = new Leap::Controller();
    this->leapListener = new LeapMotionListener();
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

void LeapMotionController::registerTargetListenerToLeapMotionInputs(QObject *listener)
{
    this->leapListener->addInputListener(listener);
}

void LeapMotionController::registerTargetListenerToLeapMotionGestures(QObject *listener)
{
    this->leapListener->addGestureListener(listener);
}

void LeapMotionController::unregisterTargetListenerFromLeapMotionInputs(QObject *listener)
{
    this->leapListener->removeInputListener(listener);
}

void LeapMotionController::unregisterTargetListenerFromLeapMotionGestures(QObject *listener)
{
    this->leapListener->removeGestureListener(listener);
}

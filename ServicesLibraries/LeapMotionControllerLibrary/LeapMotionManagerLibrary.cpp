#include "LeapMotionManagerLibrary.h"
#include <QDebug>

LeapMotionManagerLibrary::LeapMotionManagerLibrary() : QObject()
{
    this->leapMotionController = NULL;
    // SHOULD BE CALLED TO REGISTER LEAP MOTION AS TOUCH DEVICE BUT INCLUDE NOT RESOLVED
    //    QWindowSystemInterface::registerTouchDevice(LeapMotionTouchDevice::getInstance());
}

LeapMotionManagerLibrary::~LeapMotionManagerLibrary()
{
    if (this->leapMotionController != NULL)
        delete  this->leapMotionController;
}

void LeapMotionManagerLibrary::initLibraryConnection(QObject *parent)
{
    QObject::connect(this, SIGNAL(initialized()), parent, SLOT(libraryInitialized()));
    this->leapMotionController = LeapMotionController::getInstance();
    emit (initialized());
}

bool LeapMotionManagerLibrary::connectServiceToUser(QObject *user)
{
    bool connected = false;
    if(qobject_cast<Services::LeapMotionServiceInputUserInterface *>(user) != NULL)
    {
        QObject::connect(user, SIGNAL(registerToLeapMotionInputs(QObject*)),
                         this->leapMotionController, SLOT(registerTargetListenerToLeapMotionInputs(QObject*)));
        QObject::connect(user, SIGNAL(unregisterFromLeapMotionInputs(QObject*)),
                         this->leapMotionController, SLOT(unregisterTargetListenerFromLeapMotionInputs(QObject*)));
        connected = true;
    }
    if(qobject_cast<Services::LeapMotionServiceGestureUserInterface *>(user) != NULL)
    {
        QObject::connect(user, SIGNAL(registerToLeapMotionGestures(QObject*)),
                         this->leapMotionController, SLOT(registerTargetListenerToLeapMotionGestures(QObject*)));
        QObject::connect(user, SIGNAL(unregisterFromLeapMotionGestures(QObject*)),
                         this->leapMotionController, SLOT(unregisterTargetListenerFromLeapMotionGestures(QObject*)));
        connected = true;
    }
    if (!connected)
        qDebug() << "Object doesn't implement LeapMotionServiceUserInterface";
    return connected;
}

bool LeapMotionManagerLibrary::disconnectServiceFromUser(QObject *user)
{
    bool connected = false;
    if(qobject_cast<Services::LeapMotionServiceInputUserInterface *>(user) != NULL)
    {
        QObject::disconnect(user, SIGNAL(registerToLeapMotionInputs(QObject*)),
                         this->leapMotionController, SLOT(registerTargetListenerToLeapMotionInputs(QObject*)));
        QObject::disconnect(user, SIGNAL(unregisterFromLeapMotionInputs(QObject*)),
                         this->leapMotionController, SLOT(unregisterTargetListenerFromLeapMotionInputs(QObject*)));
        connected = true;
    }
    if(qobject_cast<Services::LeapMotionServiceGestureUserInterface *>(user) != NULL)
    {
        QObject::disconnect(user, SIGNAL(registerToLeapMotionGestures(QObject*)),
                         this->leapMotionController, SLOT(registerTargetListenerToLeapMotionGestures(QObject*)));
        QObject::connect(user, SIGNAL(unregisterFromLeapMotionGestures(QObject*)),
                         this->leapMotionController, SLOT(unregisterTargetListenerFromLeapMotionGestures(QObject*)));
        connected = true;
    }
    if (!connected)
        qDebug() << "Object doesn't implement LeapMotionServiceUserInterface";
    return connected;
}

int LeapMotionManagerLibrary::getServiceId() const
{
    return LEAP_MOTION_SERVICE_ID;
}

QString LeapMotionManagerLibrary::getServiceVersion() const
{
    return QString(LEAP_MOTION_LIBRARY_VERSION);
}

QObject *LeapMotionManagerLibrary::getLibraryQObject()
{
    return this;
}

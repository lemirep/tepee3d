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
    if(qobject_cast<Services::LeapMotionServiceUserInterface *>(user) != NULL)
    {
        QObject::connect(user, SIGNAL(registerToLeapMotionInputs(QObject*)),
                         this->leapMotionController, SLOT(registerTargetListenerToLeapMotionInputs(QObject*)));
        return true;
    }
    else
        qDebug() << "Object doesn't implement LeapMotionServiceUserInterface";
    return false;
}

bool LeapMotionManagerLibrary::disconnectServiceFromUser(QObject *user)
{
    if(qobject_cast<Services::LeapMotionServiceUserInterface *>(user) != NULL)
    {
        QObject::disconnect(user, SIGNAL(registerToLeapMotionInputs(QObject*)),
                         this->leapMotionController, SLOT(registerTargetListenerToLeapMotionInputs(QObject*)));
        return true;
    }
    else
        qDebug() << "Object doesn't implement LeapMotionServiceUserInterface";
    return false;
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

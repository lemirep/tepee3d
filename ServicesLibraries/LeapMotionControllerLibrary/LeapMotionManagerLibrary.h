#ifndef LEAPMOTIONMANAGERLIBRARY_H
#define LEAPMOTIONMANAGERLIBRARY_H

#include <QObject>
#include "ServiceInterface.h"
#include "LeapMotionController.h"
#include "LeapMotionServiceUserInterface.h"

#define LEAP_MOTION_LIBRARY_VERSION "0.0.1"
#define LEAP_MOTION_SERVICE_ID 5

class LeapMotionManagerLibrary : public QObject, public Services::ServiceInterface
{
    Q_OBJECT
    Q_INTERFACES(Services::ServiceInterface)
    Q_PLUGIN_METADATA(IID "com.tepee3d.Services.leapmotioncontrollerservice")
public:
    LeapMotionManagerLibrary();
    ~LeapMotionManagerLibrary();

private:

    LeapMotionController *leapMotionController;

    // ServiceInterface interface
public:
    void initLibraryConnection(QObject *parent);
    bool connectServiceToUser(QObject *user);
    bool disconnectServiceFromUser(QObject *user);
    int getServiceId() const;
    QString getServiceVersion() const;
    QObject *getLibraryQObject();

signals:
    void    initialized();
};

#endif // LEAPMOTIONMANAGERLIBRARY_H

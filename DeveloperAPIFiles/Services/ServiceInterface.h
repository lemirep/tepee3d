#ifndef SERVICEINTERFACE_H
#define SERVICEINTERFACE_H

#include <QObject>
#include <QtPlugin>

namespace Services
{

class ServiceInterface
{

public :
    virtual void        initLibraryConnection(QObject *parent) = 0;
    virtual bool        connectServiceToUser(QObject *user) = 0;
    virtual bool        disconnectServiceFromUser(QObject *user) = 0;
    virtual QObject*    getLibraryQObject() = 0;
};

}
Q_DECLARE_INTERFACE(Services::ServiceInterface, "com.tepee3d.Services.ServiceInterface/1.0")


#endif // SERVICEINTERFACE_H

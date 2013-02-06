#include "ServicesManager.h"

// FOR DEBUG
#include <QDebug>

/*!
 * \namespace Services
 * \brief The Services namespace contains all classes that either manage or
 * provide a service that modules of the application can register to.
 */

/*!
 * \class Services::ServicesManager
 *
 * \brief The Services::ServicesManager class manages all the services
 * libraries.
 *
 * The Services::ServicesManager class is a singleton class. It loads the services libraries
 * and allow classes implementing the services interfaces to register for a given
 * service.
 */

Services::ServicesManager* Services::ServicesManager::instance = NULL;

Services::ServicesManager::ServicesManager(QObject *parent) : QObject(parent)
{
    this->services = QList<ServiceInterface*>();
    this->loadServicesLibraries();
}

Services::ServicesManager*   Services::ServicesManager::getInstance(QObject *parent)
{
    if (ServicesManager::instance == NULL)
        ServicesManager::instance = new Services::ServicesManager(parent);
    return ServicesManager::instance;
}

void    Services::ServicesManager::exposeContentToQml(QQmlContext *context)
{
}

void    Services::ServicesManager::connectObjectToServices(QObject *serviceUser)
{
 Services::ServicesManager::getInstance()->connectObjectToServicesSlot(serviceUser);
}

void    Services::ServicesManager::disconnectObjectFromServices(QObject *serviceUser)
{
    Services::ServicesManager::getInstance()->disconnectObjectFromServicesSlot(serviceUser);
}

void    Services::ServicesManager::connectObjectToServicesSlot(QObject *serviceUser)
{
    qDebug() << "Connecting object to services";

    foreach (ServiceInterface* service, this->services)
        service->connectServiceToUser(serviceUser);
}

void    Services::ServicesManager::disconnectObjectFromServicesSlot(QObject *serviceUser)
{
    qDebug() << "Disconnecting object from services";

    foreach (ServiceInterface* service, this->services)
        service->disconnectServiceFromUser(serviceUser);
}

bool    Services::ServicesManager::loadServicesLibraries()
{
    QDir    serviceDirectory = QApplication::applicationDirPath();

    // GO TO LIB DIRECTORIES
#if defined(Q_OS_WIN)
    if (serviceDirectory.dirName().toLower() == "debug" || serviceDirectory.dirName().toLower() == "release")
        serviceDirectory.cdUp();
#elif defined(Q_OS_MAC)
    if (serviceDirectory.dirName() == "MacOS")
    {
        serviceDirectory.cdUp();
        serviceDirectory.cdUp();
        serviceDirectory.cdUp();
    }
#endif
    serviceDirectory.cdUp();
    serviceDirectory.cd(SERVICE_LIBRARIES_DIRECTORY);

    qDebug() << "SERVICE DIR " << serviceDirectory.absolutePath();
    // LOAD ALL SERVICES LIBRARIES FOUND IN DIRECTORY
    foreach (QString filename, serviceDirectory.entryList(QDir::Files))
    {
        qDebug() << "SERVICE LIBRARY " << filename;
        QPluginLoader loader(serviceDirectory.absoluteFilePath(filename));
        ServiceInterface* service = qobject_cast<ServiceInterface *>(loader.instance());
        if (service)
        {
            this->services.push_back(service);
            service->initLibraryConnection(this);
            qDebug() << "LIBRARY INITIALIZED";
        }
        else
        {
            qCritical() << "ERRORS : "<< loader.errorString();
            qCritical() << "FAILED TO LOAD LIBRARY";
        }
    }
    return true;
}

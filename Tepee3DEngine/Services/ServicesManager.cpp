#include "ServicesManager.h"

// FOR DEBUG
#include <QDebug>

/*!
 * \namespace Services
 * \brief The Services namespace contains all classes that either manage or
 * provide a service that modules of the application can register to.
 *
 * \inmodule Tepee3D
 */

/*!
 * \class Services::ServiceInterface
 *
 * \brief Interface Services have to implement defining the necessary methods services
 * libraries have to provide.
 *
 * \inmodule Tepee3D
 */

/*! \fn void        Services::ServiceInterface::initLibraryConnection(QObject *parent)
 * Initializes the service library providing the \a parent QObject if signals connections are required.
 * Note that when the library has been initialized, it must signals it to the parent by triggering the slot
 * \code
 * void libraryInitialized();
 * \endcode
 * Off the parent instance. Otherwise the Tepee3DEngine will wait undefinetely to launch the graphical interface.
 *
 */

/*! \fn bool        Services::ServiceInterface::connectServiceToUser(QObject *user)
 * Connects the signals of a service library to the \a user.
 * Returns true if the connection was succesful, false otherwise.
 */

/*! \fn bool        Services::ServiceInterface::disconnectServiceFromUser(QObject *user)
 * Disconnects the signals of a service library from the \a user.
 * Returns true if the disconnection was succesful, false otherwise.
 */

/*! \fn QObject*    Services::ServiceInterface::getLibraryQObject() = 0;
 *
 * Returns the QObject instance of the library in order to allow signal connection
 * to the service library.
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
 *
 * \inmodule Tepee3D
 */

/*!
 * \fn void  Services::ServicesManager::librariesInitialized()
 *
 * Emitted when all services libraries have been properly intialized. UI rendering
 * should only start once this signal has been emitted.
 */

Services::ServicesManager* Services::ServicesManager::instance = NULL;

/*!
 * Constructs a new ServiceManager instance with the optionnal \a parent.
 */
Services::ServicesManager::ServicesManager(QObject *parent) : QObject(parent)
{
    this->services = QList<ServiceInterface*>();
//    this->loadServicesLibraries();
}

/*!
 * Returns the singleton instance of the ServiceManager class. Constructs an instance with \a parent if it hasn't been done before.
 */
Services::ServicesManager*   Services::ServicesManager::getInstance(QObject *parent)
{
    if (ServicesManager::instance == NULL)
        ServicesManager::instance = new Services::ServicesManager(parent);
    return ServicesManager::instance;
}

/*!
 * Exposes QML content relative to the service management to the QML \a context
 */
void    Services::ServicesManager::exposeContentToQml(QQmlContext *context)
{
}

/*!
 * Suscribes \a serviceUser to all possible service libraries. It will only be connected to the services libraries
 * that match the services interface it implements.
 */
void    Services::ServicesManager::connectObjectToServices(QObject *serviceUser)
{
 Services::ServicesManager::getInstance()->connectObjectToServicesSlot(serviceUser);
}

/*!
 * Unsubscribe \a serviceUser from the service libraries it was connected to.
 */
void    Services::ServicesManager::disconnectObjectFromServices(QObject *serviceUser)
{
    Services::ServicesManager::getInstance()->disconnectObjectFromServicesSlot(serviceUser);
}

/*!
 * Suscribes \a serviceUser to all possible service libraries. It will only be connected to the services libraries
 * that match the services interface it implements.
 */
void    Services::ServicesManager::connectObjectToServicesSlot(QObject *serviceUser)
{
    qDebug() << "Connecting object to services";

    foreach (ServiceInterface* service, this->services)
        service->connectServiceToUser(serviceUser);
}

/*!
 * Unsubscribe \a serviceUser from the service libraries it was connected to.
 */
void    Services::ServicesManager::disconnectObjectFromServicesSlot(QObject *serviceUser)
{
    qDebug() << "Disconnecting object from services";

    foreach (ServiceInterface* service, this->services)
        service->disconnectServiceFromUser(serviceUser);
}

/*!
 * Triggered by each library to signal it is initialized. Keep count of libraries that have
 * signaled they were ready. It all libraries have signaled, then librariesInitialized signal is emitted.
 */
void Services::ServicesManager::libraryInitialized()
{
    static int initializedLibCount = 0;
    qDebug() << "Library Initialized Slot Triggered" ;
    initializedLibCount++;
    if (initializedLibCount == this->services.size())
        emit (librariesInitialized());
}

/*!
 * Loads and initializes the various service libraries present in the libraries directory of the application.
 */
void    Services::ServicesManager::loadServicesLibraries()
{
    QDir    serviceDirectory = QCoreApplication::applicationDirPath();

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
    foreach (const QString &filename, serviceDirectory.entryList(QDir::Files))
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
}

/****************************************************************************
**
** Copyright (C) Paul Lemire, Tepee3DTeam and/or its subsidiary(-ies).
** Contact: paul.lemire@epitech.eu
** Contact: tepee3d_2014@labeip.epitech.eu
**
** This file is part of the Tepee3D project
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
****************************************************************************/

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
    this->webServicesCallBacks[DOWNLOAD_SERVICE] = &Services::ServicesManager::dowloadServiceFromServerCallBack;
    this->webServicesCallBacks[CHECK_SERVICES_VERSION] = &Services::ServicesManager::checkForServicesUpdatesCallBack;
    //    this->loadServicesLibraries();
}

Services::ServicesManager::~ServicesManager()
{
    while (!this->services.empty())
        delete this->services.takeFirst();
    Services::ServicesManager::instance = NULL;
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
    foreach (ServiceInterface* service, this->services)
    {
        View::QmlContentExposerInterface *exposer = NULL;
        if ((exposer = qobject_cast<QmlContentExposerInterface*>(service->getLibraryQObject())) != NULL)
            exposer->exposeContentToQml(context);
    }
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
    qDebug() << "Library Initialized Slot Triggered" << initializedLibCount;
    initializedLibCount++;
    if (initializedLibCount == this->services.size())
        emit (librariesInitialized());
}

/*!
 * Loads and initializes the various service libraries present in the libraries directory of the application.
 */
void    Services::ServicesManager::loadServicesLibraries()
{
    QDir    serviceDirectory = PlatformFactory::getPlatformInitializer()->getServicesSharedLibrariesDirectory();

    qDebug() << "SERVICE DIR " << serviceDirectory.absolutePath();
    // LOAD ALL SERVICES LIBRARIES FOUND IN DIRECTORY
    foreach (const QString &filename, serviceDirectory.entryList(QDir::Files))
    {
        qDebug() << "SERVICE LIBRARY " << filename;
        QPluginLoader loader(serviceDirectory.absoluteFilePath(filename));
        ServiceInterface* service = qobject_cast<ServiceInterface *>(loader.instance());
        if (service)
            this->services.push_back(service);
        else
        {
            qCritical() << "ERRORS : "<< loader.errorString();
            qCritical() << "FAILED TO LOAD LIBRARY";
            loader.unload();
        }
    }
    foreach (ServiceInterface *service, this->services)
        service->initLibraryConnection(this);
}

/*!
 * Implementation required to receive web services response. Mainly used to retrieve service libraries updates.
 */

void Services::ServicesManager::receiveResultFromHttpRequest(QNetworkReply *reply, int requestId, void *data)
{
    (this->*this->webServicesCallBacks[requestId])(reply, data);
}

void Services::ServicesManager::checkForServicesUpdates()
{
}

void Services::ServicesManager::downloadServiceFromServer(int serviceId)
{
}

void Services::ServicesManager::checkForServicesUpdatesCallBack(QNetworkReply *reply, void *data)
{
}

void Services::ServicesManager::dowloadServiceFromServerCallBack(QNetworkReply *reply, void *data)
{
}

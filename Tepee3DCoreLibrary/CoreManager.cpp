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

#include "CoreManager.h"
// DEBUG
#include <QDebug>




/*!
 * \class CoreManager
 * \code
 * #include <CoreManager.h>
 * \endcode
 * \brief The View::CoreManager class manages the QML view and all the modules
 * needed in order to properly run Tepee3D.
 * It links services, widgets and models to the view
 *
 * It is a singleton class that hold the various singleton managers
 * needed by the modules of the Tepee3D application as well as the view
 * properties. Also, this is where qml models and utility classes are
 * exposed to the Qml Engine.
 *
 * \since 1.0
 *
 * \inmodule Tepee3D
 *
 * \sa View::QmlViewProperties
 * \sa Room::RoomManager
 * \sa Services::ServicesManager
 * \sa Plugins::PluginManager
 * */

//View::QmlViewManager* View::QmlViewManager::instance = NULL;

/*!
 * \fn void CoreManager::quit()
 *
 * Emitted to tell the QApplication it should be killed.
 */

/*!
 * Constructs a CoreManager instance and initializes the Service Manager,
 * the Room Manager and the Plugin Manager as well as the View. Platform specific initializations
 * are also handled here.
 *
 * \sa Room::RoomManager
 * \sa Plugins::PluginManager
 * \sa Services::ServicesManager
 */
CoreManager::CoreManager() : QObject()
{
    qDebug() << "Init Core Engine";
}

/*!
 * Initializes the Tepee3DEngine
 */
void CoreManager::initCoreEngine()
{
    if (PlatformFactory::getPlatformInitializer()->initPlatform())
    {
        this->viewProperties = View::QmlViewProperties::getInstance(this);
        this->servicesManager = Services::ServicesManager::getInstance(this);
        this->roomManager = Room::RoomManager::getInstance(this);
        this->pluginsManager  = Plugins::PluginManager::getInstance(this);

        QObject::connect(this->viewProperties, SIGNAL(quit()), this, SLOT(cleanBeforeClosing()));
        // ALL INSTANCES CREATED SHOULDN'T CALL OR REGISTER TO SERVICES UNTIL THOSE HAVE
        // BEEN PROPERLY INITIALIZED
        QObject::connect(this->servicesManager, SIGNAL(librariesInitialized()), this, SLOT(initView()));
        this->servicesManager->loadServicesLibraries();
    }
}

/*!
 * Return this instance as a QObject so that it can be connected to signals
 */
QObject *CoreManager::getObject()
{
    return this;
}

/*!
 * Destroys a QmlViewManager instance releasing the instances of the Service Manager,
 * the Room Manager, the Plugin Manager and the View.
 */
CoreManager::~CoreManager()
{
    delete this->servicesManager;
    delete this->roomManager;
    delete this->pluginsManager;
    delete this->viewProperties;
}

QString CoreManager::getCoreVersion()
{
    return CORE_VERSION;
}

/*!
 * Initialises the Tepee3DEngine services, view rendering and room management entities.
 * Returns true if the view was correctly initialized, false otherwise.
 * Triggered when the ServicesManagers signals the libraries have been properly initialized.
 */
bool    CoreManager::initView()
{
    qDebug() << "Init View";

    // CONNECT THE SERVICE MANAGER TO THE SERVICES
    Services::ServicesManager::connectObjectToServices(this->servicesManager);
    // CONNECT THE ROOM MANAGER TO THE SERVICE MANAGER
    Services::ServicesManager::connectObjectToServices(this->roomManager);
    // CONNECT THE PLUGIN MANAGER TO THE SERVICE MANAGER
    Services::ServicesManager::connectObjectToServices(this->pluginsManager);

    // SET QML PROPERTIES THAT CAN BE ACCESSED DIRECTLY FROM QML
    View::QmlViewProperties::exposeContentToQml(this->roomManager);
    View::QmlViewProperties::exposeContentToQml(this->servicesManager);
    View::QmlViewProperties::exposeContentToQml(this->pluginsManager);

    // TELLS ROOM MANAGER TO RESTORE ROOMS
    this->roomManager->restoreRooms();

//    qmlRegisterType<QmlAsTexture>("View", 1, 0, "QmlAsTexture");

    // CHECKS IF LOCAL PLUGINS HAVE BEEN UPDAPTED AND DOWNLOADS NEW REQUEST IF SO
    this->pluginsManager->checkForPluginsUpdates();
    this->pluginsManager->retrieveOnlinePluginsForCurrentPlatform();

    // SET STARTING QML FILE
    // RETRIEVE APP DIRECTORY TO LOAD QML INDEPENDANTLY FROM PLATFORM
    QUrl localFile = QUrl::fromLocalFile(PlatformFactory::getPlatformInitializer()->getDataDirectory().absolutePath() + "/qml/main.qml");
    if (localFile.isValid())
    {
        qDebug() << "SETTING VIEW SOURCE";
        this->viewProperties->setViewerSource(localFile);
        this->viewProperties->showView();
        return true;
    }
    qDebug() << "VIEW SOURCE NOT VALID";
    return false;
}

void CoreManager::cleanBeforeClosing()
{
    qDebug() << "CLEANING BEFORE CLOSING";
    delete this->viewProperties;
    delete this->roomManager;
    delete this->pluginsManager;
    delete this->servicesManager;
    emit quit();
}

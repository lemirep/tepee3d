#include "QmlViewManager.h"
// DEBUG
#include <QDebug>


/*!
 * \namespace View
 *
 * \brief The View namespace contains all the classes responsible
 * for the Qml view management or that interact between the view and
 * other modules such as Services or Plugins.
 *
 * \inmodule Tepee3D
 */

/*!
 * \class View::QmlContentExposerInterface
 * \code
 * #include <QmlContentExposerInterface.h>
 * \endcode
 * \brief Has to be implemented in order to expose QML content to the QML context.
 *
 * \inmodule Tepee3D
 */

/*!
 * \fn void View::QmlContentExposerInterface::exposeContentToQml(QQmlContext *context)
 *
 * Exposes QML content to the QML \a context.
 */

/*!
 * \class View::QmlViewManager
 * \code
 * #include <QmlViewManager.h>
 * \endcode
 * \brief The View::QmlViewManager class manages the QML view.
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
 * */

//View::QmlViewManager* View::QmlViewManager::instance = NULL;

/*!
 * \fn void View::QmlViewManager::quit()
 *
 * Emitted to tell the QApplication it should be killed.
 */

/*!
 * Constructs a QmlViewManager instance and initializes the Service Manager,
 * the Room Manager and the Plugin Manager as well as the View. Platform specific initializations
 * are also handled here.
 *
 * \sa Room::RoomManager
 * \sa Plugins::PluginManager
 * \sa Services::ServicesManager
 */
View::QmlViewManager::QmlViewManager() : QObject()
{
    qDebug() << "Init Core Engine";
}

/*!
 * Initializes the Tepee3DEngine
 */
void View::QmlViewManager::initCoreEngine()
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
QObject *View::QmlViewManager::getObject()
{
    return this;
}


/*!
 * Destroys a QmlViewManager instance releasing the instances of the Service Manager,
 * the Room Manager, the Plugin Manager and the View.
 */
View::QmlViewManager::~QmlViewManager()
{
    delete this->servicesManager;
    delete this->roomManager;
    delete this->pluginsManager;
    delete this->viewProperties;
}

/*!
 * Returns a singleton instance of the class.
 */
//View::QmlViewManager* View::QmlViewManager::getInstance()
//{
//    if (View::QmlViewManager::instance == NULL)
//        View::QmlViewManager::instance = new View::QmlViewManager();
//    return View::QmlViewManager::instance;
//}

/*!
 * Initialises the Tepee3DEngine services, view rendering and room management entities.
 * Returns true if the view was correctly initialized, false otherwise.
 * Triggered when the ServicesManagers signals the libraries have been properly initialized.
 */
bool    View::QmlViewManager::initView()
{
    qDebug() << "Init View";

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

    qmlRegisterType<QmlAsTexture>("View", 1, 0, "QmlAsTexture");

    qDebug() << "Testing TEPEE3D WEBSERVICES ------------- >>>>";
    this->pluginsManager->retrieveOnlinePluginsForCurrentPlatform();
    qDebug() << "Testing TEPEE3D WEBSERVICES ------------- <<<<";

    // SET STARTING QML FILE
    // RETRIEVE APP DIRECTORY TO LOAD QML INDEPENDANTLY FROM PLATFORM
    QUrl localFile = QUrl::fromLocalFile(PlatformFactory::getPlatformInitializer()->getDataDirectory().absolutePath() + "/qml/main.qml");
    if (localFile.isValid())
    {
        this->viewProperties->setViewerSource(localFile);
        this->viewProperties->showView();
        return true;
    }
    return false;
}

void View::QmlViewManager::cleanBeforeClosing()
{
    emit quit();
}

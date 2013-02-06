#include "QmlViewManager.h"
// DEBUG
#include <QDebug>


/*!
 * \namespace View
 *
 * \brief The View namespace contains all the classes responsible
 * for the Qml view management or that interact between the view and
 * other modules such as Services or Plugins.
 */

/*!
 * \class View::QmlViewManager
 *
 * \brief The View::QmlViewManager class manages the QML view.
 * It links services, widgets and models to the view
 *
 * It is a singleton class that hold the various singleton managers
 * needed by the modules of the Tepee3D application as well as the view
 * properties. Also, this is where qml models and utility classes are
 * exposed to the Qml Engine.
 *
 * \sa View::QmlViewProperties
 */

View::QmlViewManager* View::QmlViewManager::instance = NULL;

View::QmlViewManager::QmlViewManager() : QObject()
{
    this->viewProperties = View::QmlViewProperties::getInstance(this);
    this->servicesManager = Services::ServicesManager::getInstance(this);
    this->roomManager = Room::RoomManager::getInstance(this);
    this->pluginsManager  = Plugins::PluginManager::getInstance(this);
}

View::QmlViewManager::~QmlViewManager()
{
    delete this->servicesManager;
    delete this->roomManager;
    delete this->pluginsManager;
    delete this->viewProperties;
}

View::QmlViewManager* View::QmlViewManager::getInstance()
{
    if (View::QmlViewManager::instance == NULL)
        View::QmlViewManager::instance = new View::QmlViewManager();
    return View::QmlViewManager::instance;
}

bool    View::QmlViewManager::initView()
{

    // CONNECT THE ROOM MANAGER TO THE SERVICE MANAGER
    Services::ServicesManager::connectObjectToServices(this->roomManager);
    // CONNECT THE PLUGIN MANAGER TO THE SERVICE MANAGER
    Services::ServicesManager::connectObjectToServices(this->pluginsManager);
    //    // SET QML PROPERTIES THAT CAN BE ACCESSED DIRECTLY FROM QML
    View::QmlViewProperties::exposeContentToQml(this->roomManager);
    View::QmlViewProperties::exposeContentToQml(this->servicesManager);
    View::QmlViewProperties::exposeContentToQml(this->pluginsManager);

    qmlRegisterType<QmlAsTexture>("View", 1, 0, "QmlAsTexture");

    // SET STARTING QML FILE
    // RETRIEVE APP DIRECTORY TO LOAD QML INDEPENDANTLY FROM PLATFORM
    QUrl localFile = QUrl::fromLocalFile(QApplication::applicationDirPath() + "/qml/main.qml");
    if (localFile.isValid())
    {
        this->roomManager->addRoomToModel();
        this->viewProperties->setViewerSource(localFile);
        this->viewProperties->showView();
        return true;
    }
    return false;
}




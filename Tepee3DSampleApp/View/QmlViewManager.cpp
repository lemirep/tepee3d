#include "QmlViewManager.h"
// DEBUG
#include <QDebug>

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




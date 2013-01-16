#include "QmlViewManager.h"
// DEBUG
#include <QDebug>

QmlViewManager* QmlViewManager::instance = NULL;

QmlViewManager::QmlViewManager() : QObject()
{
    this->viewer = new QQuickView();                     //USED TO DISPLAY QML
    this->qmlEngine = this->viewer->engine();            //RETRIEVED FROM THE VIEWER USED TO INSTANCIATE AND INSERT NEW QML COMPONENTS FROM PLUGINS
    this->qmlContext = this->viewer->rootContext();      //USED TO SET PROPERTIES TO QML FOR MODELS
    this->desktopWidget = QApplication::desktop();       //USED TO RETRIEVE SCREEN SIZE

    this->servicesManager = Services::ServicesManager::getInstance(this);

    this->roomManager = Room::RoomManager::getInstance(this);
    QObject::connect(this->roomManager, SIGNAL(exposeContentToQml(QObject*)), this, SLOT(exposeContentToQml(QObject*)));

    this->pluginsManager  = Plugins::PluginManager::getInstance(this);
}

QmlViewManager::~QmlViewManager()
{
    delete this->viewer;
}

QmlViewManager* QmlViewManager::getInstance()
{
    if (QmlViewManager::instance == NULL)
        QmlViewManager::instance = new QmlViewManager();
    return QmlViewManager::instance;
}

bool    QmlViewManager::initView()
{

    // CONNECT THE ROOM MANAGER TO THE SERVICE MANAGER
    Services::ServicesManager::connectObjectToServices(this->roomManager);
    // CONNECT THE PLUGIN MANAGER TO THE SERVICE MANAGER
    Services::ServicesManager::connectObjectToServices(this->pluginsManager);
    //    // SET QML PROPERTIES THAT CAN BE ACCESSED DIRECTLY FROM QML
    QmlViewManager::exposeContentToQml(this->roomManager);
    QmlViewManager::exposeContentToQml(this->servicesManager);
    QmlViewManager::exposeContentToQml(this->pluginsManager);

    // REGISTER THE LISTMODEL TYPE TO THE QML ENGINE SO THAT WE CAN USE MODEL AS PROPERTIES OF QML OBJECTS
    //    qmlRegisterType<ListModel>("Model", 1, 0, "ListModel");
    //    qmlRegisterType<Room::RoomProperties>("Room", 1, 0, "RoomProperties");


    // SET STARTING QML FILE
    // RETRIEVE APP DIRECTORY TO LOAD QML INDEPENDANTLY FROM PLATFORM
    QDir applicationDir = QApplication::applicationDirPath();
    qDebug() << "application path " << applicationDir.absolutePath();
    QUrl localFile = QUrl::fromLocalFile(applicationDir.absolutePath() + "/qml/main.qml");

    if (localFile.isValid())
        qDebug() << "Local file is valid " << localFile.isEmpty();

    QStringList paths = this->qmlEngine->importPathList();
    foreach (QString p, paths)
    {
        qDebug() << "Import Path " << p;
    }

    this->roomManager->addRoomToModel();
    this->viewer->setSource(localFile);
    this->viewer->show();
    //    this->viewer->showFullScreen();

    return true;
}

void    QmlViewManager::exposeContentToQml(QObject *exposer)
{
    QmlContentExposerInterface* interface = NULL;

    if ((interface = dynamic_cast<QmlContentExposerInterface *>(exposer)) != NULL)
        interface->exposeContentToQml(QmlViewManager::getInstance()->qmlContext);
}


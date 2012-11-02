#include "QmlViewManager.h"
// DEBUG
#include <iostream>

QmlViewManager::QmlViewManager(QApplication *app) : QObject()
{
    this->viewer = new QQuickView();                     //USED TO DISPLAY QML
    this->qmlEngine = this->viewer->engine();            //RETRIEVED FROM THE VIEWER USED TO INSTANCIATE AND INSERT NEW QML COMPONENTS FROM PLUGINS
    this->qmlContext = this->viewer->rootContext();      //USED TO SET PROPERTIES TO QML FOR MODELS
    this->desktopWidget = QApplication::desktop();       //USED TO RETRIEVE SCREEN SIZE

    this->servicesManager = new Services::ServicesManager(this);
    this->roomManager = new Room::RoomManager(this);
    this->pluginsManager  = new Plugins::PluginManager(this);

    QObject::connect(this->roomManager, SIGNAL(connectObjectToServices(QObject*)), this->servicesManager, SLOT(connectObjectToServices(QObject*)));
    QObject::connect(this->roomManager, SIGNAL(disconnectObjectFromServices(QObject*)), this->servicesManager, SLOT(disconnectObjectFromServices(QObject*)));

    // CONNECT THE ROOM MANAGER TO THE SERVICE MANAGER
    this->servicesManager->connectObjectToServices(this->roomManager);
    // CONNECT THE PLUGIN MANAGER TO THE SERVICE MANAGER
    this->servicesManager->connectObjectToServices(this->pluginsManager);
    // SET QML PROPERTIES THAT CAN BE ACCESSED DIRECTLY FROM QML
    this->registerComponentsToQml();
}

QmlViewManager::~QmlViewManager()
{
    delete this->viewer;
}

bool    QmlViewManager::initView()
{
    // SET STARTING QML FILE


    // RETRIEVE APP DIRECTORY TO LOAD QML INDEPENDANTLY FROM PLATFORM
    QDir applicationDir = QApplication::applicationDirPath();
    std::cout << "application path " << applicationDir.absolutePath().toStdString() << std::endl;
    QUrl localFile = QUrl::fromLocalFile(applicationDir.absolutePath() + "/qml/main.qml");

    if (localFile.isValid())
        std::cout << "Local file is valid " << localFile.isEmpty() << std::endl;


    QStringList paths = this->qmlEngine->importPathList();
    foreach (QString p, paths)
    {
        std::cout << "Import Path " << p.toStdString() << std::endl;
    }


    //      //CONTROLLER BETWEEN QML VIEW AND MODELS
    //    this->viewer->rootContext()->setContextProperty("controller", this);
    //    // GET ROOT QML OBJECT
    //    this->rootQmlObject = this->viewer->rootObject();
    //    std::cout << "-----1.4-----" << std::endl;
    //    // SET SCREESIZE IN ROOT OBJECT
    //    this->rootQmlObject->setProperty("width", this->desktopWidget->screenGeometry(-1).width());
    //    this->rootQmlObject->setProperty("height", this->desktopWidget->screenGeometry(-1).height());
    //    std::cout << "-----1.6-----" << std::endl;
    //    // SHOW QML FILE IN FULLSCREEN
    //    std::cout << "-----2-----" << std::endl;
    //    QObject *tmpObj;
    //    if ((tmpObj = this->rootQmlObject->findChild<QObject *>("viewport")))
    //    {
    //        this->viewport = (QQuickItem*)tmpObj;
    //        std::cout << "ViewPort found" << std::endl;
    //    }
    //    if ((tmpObj = this->rootQmlObject->findChild<QObject  *>("root3dObject")))
    //    {
    //        this->root3dObject = (QQuickItem*)tmpObj;
    //        std::cout << "Root3dObject found" << std::endl;
    //    }
    //    if ((tmpObj = this->rootQmlObject->findChild<QObject  *>("glCamera")))
    //    {
    //        //        if ((this->camera = qobject_cast<QGLCamera*>(tmpObj)))
    //        //        {
    //        //            std::cout << "Camera found" << std::endl;
    //        //        std::cout << this->camera->nearPlane() << std::endl;
    //        // WHEN AVALAIBLE SAVE VIEWPORT OBJ AS VIEWPORT SO THAT WE
    //        // CAN RETRIEVE THE CAMERA AND SAVE IT IN THE CAMERA OBJ
    //        //        }
    //    }
    //    std::cout << "-----3-----" << std::endl;

    //    Plugins::PluginBase* testPlugin = Plugins::PluginManager::getAvailablePlugins().at(0)->createNewInstance();
    //    this->servicesManager->connectObjectToServices(testPlugin);
    //    testPlugin->initPlugin();

    this->roomManager->addRoomToModel();
    this->viewer->setSource(localFile);
    this->viewer->show();

    return true;
}

void    QmlViewManager::registerComponentsToQml()
{
    // THIS CAST ENSURE THAT THE OBJECT IMPLEMENT THE QmlContextExposerInterface SO THAT IT CAN REGISTER DATA
    if (dynamic_cast<QmlContentExposerInterface *>(this->roomManager))
        this->roomManager->exposeContentToQml(this->qmlContext);
    if (dynamic_cast<QmlContentExposerInterface *>(this->servicesManager))
        this->servicesManager->exposeContentToQml(this->qmlContext);
    if (dynamic_cast<QmlContentExposerInterface *>(this->pluginsManager))
        this->pluginsManager->exposeContentToQml(this->qmlContext);
}


#include <QApplication>
#include "QmlViewManager.h"



Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication *app = new QApplication(argc, argv);
    QmlViewManager* manager = QmlViewManager::getInstance(app);
    manager->initView();




    //    QmlApplicationViewer    viewer;         //USED TO DISPLAY QML
//    QQuickView              viewer;         //USED TO DISPLAY QML
//    QQmlEngine              *qmlEngine;     //RETRIVED FROM THE VIEWER USED TO INSTANCIATE AND INSERT NEW QML COMPONENTS FROM PLUGINS
//    QQmlContext             *qmlContext;    //USED TO SET PROPERTIES TO QML FOR MODELS
//    QDesktopWidget          *desktopWidget; //USED TO RETRIEVE SCREEN SIZE
//    QObject                 *rootQmlObject; //USED TO STORE ROOT QML OBJECT TO SET SCREEN SIZE

//    qmlContext = viewer.rootContext();
//    qmlEngine = viewer.engine();
//    desktopWidget = QApplication::desktop();

//    sigTest *t = new sigTest();

//    // ADD LIBRARY PATH TO APP TO TELL WHERE PLUGINS TO LOAD ARE LOCATED
//    PluginLoader::setLibraryPath(app);


//    // SET VIEWPORT TO OPENGL FOR QTQUICK3D
//    //QApplication::setGraphicsSystem("opengl");
//    // SET STARTING QML FILE
//    viewer.setSource(QUrl::fromLocalFile("qml/Tepee3DSampleApp/main.qml"));
//    // GET ROOT QML OBJECT
//    rootQmlObject = viewer.rootObject();
//    // SET SCREESIZE IN ROOT OBJECT
//    rootQmlObject->setProperty("width", desktopWidget->screenGeometry(-1).width());
//    rootQmlObject->setProperty("height", desktopWidget->screenGeometry(-1).height());
//    // SHOW QML FILE IN FULLSCREEN
//    viewer.show();


//    ///////////////////////////////PLUGINS LOADING///////////////////////////////////
//    // LOAD PLUGINS HERE
//    PluginLoader::loadPlugins();
//    std::cout << "PLUGINS WERE SUCCESSFULLY LOADED" << std::endl;
//    std::cout << "TESTING PLUGINS" << std::endl;
//    QList<PluginInterface *>plugins = PluginLoader::getPlugins();
//    foreach (PluginInterface *plugin, plugins)
//    {
//        // DO PLUGIN CONNECTIONS
//        QObject::connect(plugin->getQDeclarativePlugin(), SIGNAL(toto(QString)), t, SLOT(onSignal(QString)));
//        // INIT PLUGIN
//        plugin->initPlugin();

//        std::cout << "PLUGIN ID = " << plugin->getPluginId() << std::endl;
//        std::cout << "PLUGIN NAME = " << plugin->getPluginName().toStdString() << std::endl;
//        std::cout << "PLUGIN DESCRIPTION = " << plugin->getPluginDescription().toStdString() << std::endl;

//        // DYNAMIC CREATION OF THE QML PLUGIN
//        //            QDeclarativeComponent *component = new QDeclarativeComponent(qmlEngine, "../plugins_qml/" + plugin->getPluginDescription());
//        QQmlComponent *component = new QQmlComponent(qmlEngine, "../plugins_qml/" +plugin->getPluginName() + "/" + plugin->getPluginDescription());
//        // CREATE THE QML OBJECT
//        //            QDeclarativeItem *item = qobject_cast<QDeclarativeItem*>(component->create());
//        QQuickItem *item = qobject_cast<QQuickItem*>(component->create());
//        qDebug() << component->errors();
//        if (item)
//        {
//            // IF THE QML OBJECT WAS CREATED WE CAN INSERT IT IN THE APPLICATION
//            //                item->setParentItem(qobject_cast<QDeclarativeItem*>(rootQmlObject));
//            item->setParentItem(qobject_cast<QQuickItem*>(rootQmlObject));
//            // WE CAN MODIFY OBJECT IF WE WANT TO FROM HERE
//            item->setX(300);
//            item->setY(500);
//            std::cout << "QML COMPONENT LOADED" << std::endl;
//        }
//        else
//            std::cout << "QML COMPONENT ERROR" << std::endl;

//    }


    return app->exec();
}

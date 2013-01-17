#include "QmlViewProperties.h"
#include <QDebug>

View::QmlViewProperties* View::QmlViewProperties::instance = NULL;

View::QmlViewProperties::QmlViewProperties(QObject *parent) : QObject(parent)
{
    this->viewer = new QQuickView();                     //USED TO DISPLAY QML
    this->qmlEngine = this->viewer->engine();            //RETRIEVED FROM THE VIEWER USED TO INSTANCIATE AND INSERT NEW QML COMPONENTS FROM PLUGINS
    this->qmlContext = this->viewer->rootContext();      //USED TO SET PROPERTIES TO QML FOR MODELS
    this->desktopWidget = QApplication::desktop();       //USED TO RETRIEVE SCREEN SIZE
}

View::QmlViewProperties::~QmlViewProperties()
{
    delete this->viewer;
}

View::QmlViewProperties* View::QmlViewProperties::getInstance(QObject *parent)
{
    if (View::QmlViewProperties::instance == NULL)
        View::QmlViewProperties::instance = new View::QmlViewProperties(parent);
    return View::QmlViewProperties::instance;
}

void    View::QmlViewProperties::exposeContentToQml(QObject *exposer)
{
    qDebug() << "Exposing Qml Content";
    QmlContentExposerInterface* interface = NULL;

    if ((interface = dynamic_cast<QmlContentExposerInterface *>(exposer)) != NULL)
        interface->exposeContentToQml(View::QmlViewProperties::getInstance()->qmlContext);
}

void    View::QmlViewProperties::setViewerSource(const QUrl &sourceFile)
{
    this->viewer->setSource(sourceFile);
}

void    View::QmlViewProperties::showView()
{
    this->viewer->show();
}

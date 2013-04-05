#include "QmlViewProperties.h"
#include <QDebug>

/*!
 * \class View::QmlViewProperties
 *
 * \code
 * #include <QmlViewProperties.h>
 * \endcode
 *
 * \brief The View::QmlViewProperties class hold the properties
 * of the Qml view.
 *
 * It is a singleton class that should only be used by the View::QmlViewManager
 * class. It contains the QQuickView responsible for showing the Qml content onscreen,
 * the Qml Engine and the Qml Context. More, this is where qml content is exposed to
 * the Qml Context to later be used directly from Qml files.
 *
 * \sa View::QmlViewManager
 *
 * \inmodule Tepee3D
 */



View::QmlViewProperties* View::QmlViewProperties::instance = NULL;

/*!
 * Constructs a new View::QmlViewProperties instance with \a parent.
 */

View::QmlViewProperties::QmlViewProperties(QObject *parent) : QObject(parent)
{
    this->viewer = new QQuickView();                     //USED TO DISPLAY QML
    this->qmlEngine = this->viewer->engine();            //RETRIEVED FROM THE VIEWER USED TO INSTANCIATE AND INSERT NEW QML COMPONENTS FROM PLUGINS
    this->qmlContext = this->viewer->rootContext();      //USED TO SET PROPERTIES TO QML FOR MODELS
    qDebug() << "QmlViewProperties Constructor";
}

/*!
 * Destroys a View::QmlViewProperties instance.
 */
View::QmlViewProperties::~QmlViewProperties()
{
    delete this->viewer;
}

/*!
 * Returns a singleton instance of the class, constructing the instance, with the optionnal \a parent parameter, if it hasn't before.
 */
View::QmlViewProperties* View::QmlViewProperties::getInstance(QObject *parent)
{
    if (View::QmlViewProperties::instance == NULL)
        View::QmlViewProperties::instance = new View::QmlViewProperties(parent);
    return View::QmlViewProperties::instance;
}

/*!
 * Exposes the \a exposer instance to the QML context if exposer implements the QmlContentExposerInterface
 * \sa QmlContentExposerInterface
 */
void    View::QmlViewProperties::exposeContentToQml(QObject *exposer)
{
    qDebug() << "Exposing Qml Content";
    QmlContentExposerInterface* interface = NULL;

    if ((interface = qobject_cast<QmlContentExposerInterface *>(exposer)) != NULL)
        interface->exposeContentToQml(View::QmlViewProperties::getInstance()->qmlContext);
}

/*!
 * Sets \a sourceFile as the source of the QML viewer.
 */
void    View::QmlViewProperties::setViewerSource(const QUrl &sourceFile)
{
    this->viewer->setSource(sourceFile);
}

/*!
 * Shows the QML viewer.
 */
void    View::QmlViewProperties::showView()
{
    this->viewer->show();
//    this->viewer->showFullScreen();
}

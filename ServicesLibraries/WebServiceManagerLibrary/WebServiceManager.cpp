#include "WebServiceManager.h"
// DEBUG
#include <QDebug>

/*!
 * \class WebServiceManager
 *
 * \brief WebServiceManagerr is a Web Service Library.
 *
 * WebServiceManager::WebServiceManager is a Web Service Library. It offers users to possiblity to make PUT POST DELETE GET Http requests
 * by implementing the Services::WebServiceUserInterface interface and subscribing to the service through the Services::ServicesManager which
 * is done automatically for Tepee3D plugins.
 *
 * \inmodule Tepee3D
 *
 * \sa Services::WebServiceUserInterface
 * \sa Services::ServicesManager
 */

/*!
 * \class Services::WebServiceUserInterface
 *
 * \code
 * #include <WebServiceUserInterface.h>
 * \endcode
 *
 * \brief Interface subscribers have to implement in order to properly handle and use this service.
 *
 * \inmodule Tepee3D
 */

/*!
 * \fn void Services::WebServiceUserInterface::receiveResultFromHttpRequest(QNetworkReply *reply, int requestId, void *data)
 *
 * Receives the \a reply of the last executed request and forward the \a requestId and \a data parameters that were passed
 * when executing the request.
 */

/*!
 * \fn void Services::WebServiceUserInterface::executeHttpGetRequest(const QNetworkRequest& request, int requestId, void *data)
 *
 * Performs a GET Http \a request. \a requestId and \a data will be transmitted along with the result of the request.
 */

/*!
 * \fn void Services::WebServiceUserInterface::executeHttpDeleteRequest(const QNetworkRequest& request, int requestId, void *data)
 *
 * Performs a DELETE Http \a request. \a requestId and \a data will be transmitted along with the result of the request.
 */

/*!
 * \fn void Services::WebServiceUserInterface::executeHttpPutRequest(const QNetworkRequest& request, QHttpMultiPart* multiPart, int requestId, void *data)
 *
 * Performs a PUT Http \a request. If \a multiPart is not NULL its data will be transmitted with the request. \a requestId and \a data will be transmitted along with the result of the request.
 */

/*!
 * \fn void Services::WebServiceUserInterface::executeHttpPostRequest(const QNetworkRequest& request, QHttpMultiPart* multiPart, int requestId, void *data)
 *
 * Performs a POST Http \a request. If \a multiPart is not NULL its data will be transmitted with the request. \a requestId and \a data will be transmitted along with the result of the request.
 */


/*!
 * Constructs a WebServiceManager instance.
 */
WebServiceManager::WebServiceManager() : QObject()
{
    this->httpMethods[Services::WebServiceUserInterface::Get] = &WebServiceManager::httpGet;
    this->httpMethods[Services::WebServiceUserInterface::Delete] = &WebServiceManager::httpDelete;
    this->httpMethods[Services::WebServiceUserInterface::Post] = &WebServiceManager::httpPost;
    this->httpMethods[Services::WebServiceUserInterface::Put] = &WebServiceManager::httpPut;
}

/*!
 * Returns a singleton instance of QNetworkAccessManager to ensure all requests will go through the same instance.
 */
QNetworkAccessManager*  WebServiceManager::getInstance()
{
    if (instance == NULL)
        instance = new QNetworkAccessManager();
    return instance;
}


/*!
 * Performs a GET Http \a request, the reply will be transmitted to \a sender along with \a requestId and \a data.
 * \a multipart is not used but has to be present the the prototype of the method which is generic for all HTTP requests
 */

// NETWORK REPLYREPEATER HAS TO BE DELETED IN PLUGIN
// QNETWORKREPLY HAS TO BE DELETED USING DELETELATER
void  WebServiceManager::httpGet(QNetworkRequest &request, QHttpMultiPart*multipart, QObject *sender, int requestId, void *data)
{
    Q_UNUSED(multipart)
    qDebug() << "Executing HttpGetRequest";
    NetworkReplyRepeater *repeater = new NetworkReplyRepeater(sender, requestId, data);
    QNetworkReply *reply = this->getInstance()->get(request);
    QObject::connect(reply, SIGNAL(finished()), repeater, SLOT(receiveNetworkReply()));
}

/*!
 * Performs a DELETE Http \a request, the reply will be transmitted to \a sender along with \a requestId and \a data.
 * \a multipart is not used but has to be present the the prototype of the method which is generic for all HTTP requests
 * method.
 */
void  WebServiceManager::httpDelete(QNetworkRequest &request, QHttpMultiPart *multipart, QObject *sender, int requestId, void *data)
{
    Q_UNUSED(multipart)
    qDebug() << "Executing HttpGetDelete";
    NetworkReplyRepeater *repeater = new NetworkReplyRepeater(sender, requestId, data);
    QNetworkReply*reply = this->getInstance()->deleteResource(request);
    QObject::connect(reply, SIGNAL(finished()), repeater, SLOT(receiveNetworkReply()));
}

/*!
 * Performs a POST Http \a request, the reply will be transmitted to \a sender along with \a requestId and \a data. If \a multiPart is not NULL
 * its data will be transmitted with the request.
 */
void  WebServiceManager::httpPost(QNetworkRequest &request, QHttpMultiPart *multiPart, QObject *sender, int requestId, void *data)
{
    qDebug() << "Executing HttpGetPost";
    NetworkReplyRepeater *repeater = new NetworkReplyRepeater(sender, requestId, data);
    QNetworkReply *reply = this->getInstance()->post(request, multiPart);
    QObject::connect(reply, SIGNAL(finished()), repeater, SLOT(receiveNetworkReply()));
}

/*!
 * Performs a PUT Http \a request, the reply will be transmitted to \a sender along with \a requestId and \a data. If \a multiPart is not NULL
 * its data will be transmitted with the request.
 */
void  WebServiceManager::httpPut(QNetworkRequest &request, QHttpMultiPart *multiPart, QObject *sender, int requestId, void *data)
{
    qDebug() << "Executing HttpGetPut";
    NetworkReplyRepeater *repeater = new NetworkReplyRepeater(sender, requestId, data);
    QNetworkReply *reply = this->getInstance()->put(request, multiPart);
    QObject::connect(reply, SIGNAL(finished()), repeater, SLOT(receiveNetworkReply()));
}

/*!
 * Subscribes a \a user to the service if it implements the right interface.
 */
bool  WebServiceManager::connectServiceToUser(QObject *user)
{
    qDebug() << "Connecting user to WebServices";
    // HTTP
    if (dynamic_cast<Services::WebServiceUserInterface*>(user) != NULL)
        return QObject::connect(user, SIGNAL(executeHttpRequest(const QNetworkRequest&, int, QHttpMultiPart*, QObject*, int, void*)),
                         this, SLOT(executeHttpRequest(QNetworkRequest, int, QHttpMultiPart*, QObject*, int, void*)));
    qWarning() << "Object does not implement WebServiceUserInterface";
    return false;
}

/*!
 * Unsubscribes a \a user from the service.
 */
bool  WebServiceManager::disconnectServiceFromUser(QObject *user)
{
    // HTTP
    if (dynamic_cast<Services::WebServiceUserInterface*>(user) != NULL)
        return QObject::connect(user, SIGNAL(executeHttpRequest(const QNetworkRequest&, int, QHttpMultiPart*, QObject*, int, void*)),
                         this, SLOT(executeHttpRequest(QNetworkRequest, int, QHttpMultiPart*, QObject*, int, void*)));
    qWarning() << "Object does not implement WebServiceUserInterface";
    return false;
}


QJsonObject*    WebServiceManager::QJsonFromReply(QNetworkReply *reply)
{
    return new QJsonObject(QJsonDocument::fromJson(reply->readAll()).object());
}

/*!
 * Initializes library signal connection with \a parent.
 */
void            WebServiceManager::initLibraryConnection(QObject *parent)
{
    QObject::connect(this, SIGNAL(initialized()), parent, SLOT(libraryInitialized()));
    emit (initialized());
}

/*!
 * Executes a HTTP \a request given the type of request \a requestType and and eventually NULL \a multiPart.
 * \a sender will receive the result of the request along with \a requestId to make it easier to recognize which
 * request it was.
 */
void            WebServiceManager::executeHttpRequest(QNetworkRequest request, int requestType, QHttpMultiPart *multiPart, QObject *sender, int requestId, void *data)
{
    qDebug() << "Executing HttpRequest";
    (this->*this->httpMethods[requestType])(request, multiPart, sender, requestId, data);
}

/*!
 * Return the QObject instance of the library so that it can easily be connected to signals
 * and slots.
 */
QObject*        WebServiceManager::getLibraryQObject()
{
    return this;
}


QNetworkAccessManager* WebServiceManager::instance = NULL;

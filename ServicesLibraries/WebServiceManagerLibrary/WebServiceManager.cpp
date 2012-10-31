#include "WebServiceManager.h"
// DEBUG
#include <QDebug>

WebServiceManager::WebServiceManager() : QObject()
{
    this->httpMethods[WebServiceUserInterface::GET] = &WebServiceManager::httpGet;
    this->httpMethods[WebServiceUserInterface::DELETE] = &WebServiceManager::httpDelete;
    this->httpMethods[WebServiceUserInterface::POST] = &WebServiceManager::httpPost;
    this->httpMethods[WebServiceUserInterface::PUT] = &WebServiceManager::httpPut;
}

QNetworkAccessManager*  WebServiceManager::getInstance()
{
    if (instance == NULL)
        instance = new QNetworkAccessManager();
    return instance;
}

void  WebServiceManager::httpGet(QNetworkRequest &request, QHttpMultiPart*, QObject *sender)
{
    qDebug() << "Executing HttpGetRequest";
    NetworkReplyRepeater *repeater = new NetworkReplyRepeater(sender);
    QNetworkReply *reply = this->getInstance()->get(request);
    QObject::connect(reply, SIGNAL(finished()), repeater, SLOT(receiveNetworkReply()));
}

void  WebServiceManager::httpDelete(QNetworkRequest &request, QHttpMultiPart*, QObject *sender)
{
    qDebug() << "Executing HttpGetDelete";
    NetworkReplyRepeater *repeater = new NetworkReplyRepeater(sender);
    QNetworkReply*reply = this->getInstance()->deleteResource(request);
    QObject::connect(reply, SIGNAL(finished()), repeater, SLOT(receiveNetworkReply()));
}

void  WebServiceManager::httpPost(QNetworkRequest &request, QHttpMultiPart *multiPart, QObject *sender)
{
    qDebug() << "Executing HttpGetPost";
    NetworkReplyRepeater *repeater = new NetworkReplyRepeater(sender);
    QNetworkReply *reply = this->getInstance()->post(request, multiPart);
    QObject::connect(reply, SIGNAL(finished()), repeater, SLOT(receiveNetworkReply()));
}

void  WebServiceManager::httpPut(QNetworkRequest &request, QHttpMultiPart *multiPart, QObject *sender)
{
    qDebug() << "Executing HttpGetPut";
    NetworkReplyRepeater *repeater = new NetworkReplyRepeater(sender);
    QNetworkReply *reply = this->getInstance()->put(request, multiPart);
    QObject::connect(reply, SIGNAL(finished()), repeater, SLOT(receiveNetworkReply()));
}

QJsonObject*    WebServiceManager::QJsonFromReply(QNetworkReply *reply)
{
    return new QJsonObject(QJsonDocument::fromJson(reply->readAll()).object());
}

void            WebServiceManager::initLibraryConnection(QObject *parent)
{
    QObject::connect(parent, SIGNAL(executeHttpRequest(const QNetworkRequest &, int, QHttpMultiPart*, QObject*)),
                     this, SLOT(executeHttpRequest(QNetworkRequest, int, QHttpMultiPart*, QObject*)));
}

void            WebServiceManager::executeHttpRequest(QNetworkRequest request, int requestType, QHttpMultiPart *multiPart, QObject *sender)
{
    qDebug() << "Executing HttpRequest";
    (this->*this->httpMethods[requestType])(request, multiPart, sender);
}

QObject*        WebServiceManager::getLibraryQObject()
{
    return this;
}


QNetworkAccessManager* WebServiceManager::instance = NULL;

#include "WebServiceManager.h"
// DEBUG
#include <iostream>

WebServiceManager::WebServiceManager() : QObject()
{
    // TEST OF HTTP REQUEST
    QUrl url("http://127.0.0.1/RESTphp/index.php");
    QNetworkRequest req;

    req.setUrl(url);
    QNetworkReply *rep = this->httpGet(req);
}

QNetworkAccessManager*  WebServiceManager::getInstance()
{
    if (instance == NULL)
    {
        instance = new QNetworkAccessManager();
        QObject::connect(instance, SIGNAL(finished(QNetworkReply*)), this, SLOT(httpResponse(QNetworkReply*)));
    }
    return instance;
}

QNetworkReply*  WebServiceManager::httpGet(QNetworkRequest &request)
{
    return this->getInstance()->get(request);
}

QNetworkReply*  WebServiceManager::httpDelete(QNetworkRequest &request)
{
    return this->getInstance()->deleteResource(request);
}

QNetworkReply*  WebServiceManager::httpPost(QNetworkRequest &request, QHttpMultiPart *multiPart)
{
    return this->getInstance()->post(request, multiPart);
}

QNetworkReply*  WebServiceManager::httpPut(QNetworkRequest &request, QHttpMultiPart *multiPart)
{
    return this->getInstance()->put(request, multiPart);
}

QJsonObject*    WebServiceManager::QJsonFromReply(QNetworkReply *reply)
{
    return new QJsonObject(QJsonDocument::fromJson(reply->readAll()).object());
}

void            WebServiceManager::initLibraryConnection(QObject *parent)
{
//    QObject::connect(parent, SIGNAL(executeHttpRequest()))
}

void            WebServiceManager::httpResponse(QNetworkReply *reply)
{
    QString data = (QString)reply->readAll();
    std::cout << "RESPONSE {" << data.toStdString() << "}" << std::endl;
}

QObject*        WebServiceManager::getLibraryQObject()
{
    return this;
}


QNetworkAccessManager* WebServiceManager::instance = NULL;

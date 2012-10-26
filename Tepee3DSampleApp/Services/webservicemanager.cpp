#include "webservicemanager.h"

WebServiceManager::WebServiceManager()
{
}

QNetworkAccessManager*  WebServiceManager::getInstance()
{
    if (instance == NULL)
        instance = new QNetworkAccessManager();
    return instance;
}

QNetworkReply*  WebServiceManager::httpGet(QNetworkRequest &request)
{
    return getInstance()->get(request);
}

QNetworkReply*  WebServiceManager::httpDelete(QNetworkRequest &request)
{
    return getInstance()->deleteResource(request);
}

QNetworkReply*  WebServiceManager::httpPost(QNetworkRequest &request, QHttpMultiPart *multiPart)
{
    return getInstance()->post(request, multiPart);
}

QNetworkReply*  WebServiceManager::httpPut(QNetworkRequest &request, QHttpMultiPart *multiPart)
{
    return getInstance()->put(request, multiPart);
}

QJsonObject*    WebServiceManager::QJsonFromReply(QNetworkReply *reply)
{
    return new QJsonObject(QJsonDocument::fromJson(reply->readAll()).object());
}

QNetworkAccessManager* WebServiceManager::instance = NULL;

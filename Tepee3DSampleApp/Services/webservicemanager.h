#ifndef WEBSERVICEMANAGER_H
#define WEBSERVICEMANAGER_H

#include <stdlib.h>
#include <Qt/qnetworkaccessmanager.h>
#include <Qt/qnetworkreply.h>
#include <Qt/qjsonobject.h>
#include <Qt/qjsondocument.h>

class WebServiceManager
{
public:
    static  QNetworkReply*          httpGet(QNetworkRequest& request);
    static  QNetworkReply*          httpDelete(QNetworkRequest& request);
    static  QNetworkReply*          httpPost(QNetworkRequest& request, QHttpMultiPart*  multiPart);
    static  QNetworkReply*          httpPut(QNetworkRequest& request, QHttpMultiPart* multiPart);
    static  QJsonObject*            QJsonFromReply(QNetworkReply* reply);
private:
    WebServiceManager();
    static  QNetworkAccessManager*  instance;
    static  QNetworkAccessManager*  getInstance();
};

#endif // WEBSERVICEMANAGER_H

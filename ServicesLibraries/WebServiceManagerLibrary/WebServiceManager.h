#ifndef WEBSERVICEMANAGER_H
#define WEBSERVICEMANAGER_H

#include <QtCore/qglobal.h>
#include <stdlib.h>
#include <Qt/qnetworkaccessmanager.h>
#include <Qt/qnetworkreply.h>
#include <Qt/qjsonobject.h>
#include <Qt/qjsondocument.h>
#include "ServiceInterface.h"


class WebServiceManager : public QObject, Services::ServiceInterface
{
    Q_OBJECT
    Q_INTERFACES(Services::ServiceInterface)
    Q_PLUGIN_METADATA(IID "com.tepee3d.Services.webservices")
public:
    WebServiceManager();
    QNetworkReply*          httpGet(QNetworkRequest& request);
    QNetworkReply*          httpDelete(QNetworkRequest& request);
    QNetworkReply*          httpPost(QNetworkRequest& request, QHttpMultiPart*  multiPart);
    QNetworkReply*          httpPut(QNetworkRequest& request, QHttpMultiPart* multiPart);
    static  QJsonObject*            QJsonFromReply(QNetworkReply* reply);

    void                            initLibraryConnection(QObject *parent);
    QObject*                        getLibraryQObject();

private:
    static  QNetworkAccessManager*  instance;
    QNetworkAccessManager*  getInstance();


private slots:
    void                     httpResponse(QNetworkReply *reply);

    // DEFINE SIGNALS HERE

};



#endif // WEBSERVICEMANAGER_H

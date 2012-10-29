#ifndef WEBSERVICEMANAGER_H
#define WEBSERVICEMANAGER_H

#include <QHash>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include "ServiceInterface.h"
#include "WebServiceUserInterface.h"
#include "NetworkReplyRepeater.h"


class WebServiceManager : public QObject, Services::ServiceInterface
{
    Q_OBJECT
    Q_INTERFACES(Services::ServiceInterface)
    Q_PLUGIN_METADATA(IID "com.tepee3d.Services.webservices")
public:
    WebServiceManager();
    void          httpGet(QNetworkRequest& request, QHttpMultiPart*  multiPart, QObject *sender);
    void          httpDelete(QNetworkRequest& request, QHttpMultiPart*  multiPart, QObject *sender);
    void          httpPost(QNetworkRequest& request, QHttpMultiPart*  multiPart, QObject *sender);
    void          httpPut(QNetworkRequest& request, QHttpMultiPart* multiPart, QObject *sender);

    static  QJsonObject*    QJsonFromReply(QNetworkReply* reply);

    void                            initLibraryConnection(QObject *parent);
    QObject*                        getLibraryQObject();

private:
    static  QNetworkAccessManager*  instance;
    QNetworkAccessManager*  getInstance();
    QHash<int, void (WebServiceManager::*)(QNetworkRequest&, QHttpMultiPart*, QObject*)>       httpMethods;

private slots:
    void executeHttpRequest(QNetworkRequest &request, int requestType,
                            QHttpMultiPart *multiPart, QObject *sender);
signals:
};



#endif // WEBSERVICEMANAGER_H

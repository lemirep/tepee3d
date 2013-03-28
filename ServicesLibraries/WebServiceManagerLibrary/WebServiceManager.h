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
    void          httpGet(QNetworkRequest& request, QHttpMultiPart*  multiPart, QObject *sender, int requestId, void *data);
    void          httpDelete(QNetworkRequest& request, QHttpMultiPart*  multiPart, QObject *sender, int requestId, void *data);
    void          httpPost(QNetworkRequest& request, QHttpMultiPart*  multiPart, QObject *sender, int requestId, void *data);
    void          httpPut(QNetworkRequest& request, QHttpMultiPart* multiPart, QObject *sender, int requestId, void *data);

    static  QJsonObject*    QJsonFromReply(QNetworkReply* reply);

    void                    initLibraryConnection(QObject *parent);
    bool                    connectServiceToUser(QObject *user);
    bool                    disconnectServiceFromUser(QObject *user);
    QObject*                getLibraryQObject();


private:
    static  QNetworkAccessManager*  instance;
    QNetworkAccessManager*  getInstance();
    QHash<int, void (WebServiceManager::*)(QNetworkRequest&, QHttpMultiPart*, QObject*, int, void *)>       httpMethods;

private slots:
    void executeHttpRequest(QNetworkRequest request, int requestType,
                            QHttpMultiPart *multiPart, QObject *sender, int requestId, void *data);
signals:
    void initialized();
};



#endif // WEBSERVICEMANAGER_H

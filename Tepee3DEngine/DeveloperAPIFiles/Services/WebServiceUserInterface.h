#ifndef WEBSERVICEUSERINTERFACE_H
#define WEBSERVICEUSERINTERFACE_H

#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QNetworkRequest>

// YOU NEED TO IMPLEMENT THIS INTERFACE IN ORDER TO RECEIVE NETWORK REPLIES

namespace Services
{
class   WebServiceUserInterface
{
public :
    enum WebServiceRequestType{Get = 1, Post, Delete, Put};
    virtual void receiveResultFromHttpRequest(QNetworkReply *reply, int requestId, void *data) = 0;
//    virtual void executeHttpGetRequest(const QNetworkRequest& request, int requestId, void *data) = 0;
//    virtual void executeHttpDeleteRequest(const QNetworkRequest& request, int requestId, void *data) = 0;
//    virtual void executeHttpPutRequest(const QNetworkRequest& request, QHttpMultiPart* multiPart, int requestId, void *data) = 0;
//    virtual void executeHttpPostRequest(const QNetworkRequest& request, QHttpMultiPart* multiPart, int requestId, void *data) = 0;
    // SIGNAL
    //void executeHttpRequest(const QNetworkRequest&, int, QHttpMultiPart*, QObject* sender, int, void *);
};
}
Q_DECLARE_INTERFACE(Services::WebServiceUserInterface, "com.tepee3d.Services.WebServiceUserInterface/1.0")


#endif // WEBSERVICEUSERINTERFACE_H

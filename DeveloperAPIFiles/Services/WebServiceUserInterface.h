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
    virtual void receiveResultFromHttpRequest(QNetworkReply *reply) = 0;
    virtual void executeHttpGetRequest(const QNetworkRequest& request) = 0;
    virtual void executeHttpDeleteRequest(const QNetworkRequest& request) = 0;
    virtual void executeHttpPutRequest(const QNetworkRequest& request, QHttpMultiPart* multiPart) = 0;
    virtual void executeHttpPostRequest(const QNetworkRequest& request, QHttpMultiPart* multiPart) = 0;
    // SIGNAL
    //void executeHttpRequest(const QNetworkRequest&, int, QHttpMultiPart*, QObject* sender);
};
}

#endif // WEBSERVICEUSERINTERFACE_H

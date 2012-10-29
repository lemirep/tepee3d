#ifndef WEBSERVICEUSERINTERFACE_H
#define WEBSERVICEUSERINTERFACE_H

#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QNetworkRequest>
// YOU NEED TO IMPLEMENT THIS INTERFACE IN ORDER TO RECEIVE NETWORK REPLIES
class   WebServiceUserInterface
{
public :
    enum    WebServiceRequestType
    {
        GET = 1,
        POST,
        DELETE,
        PUT
    };

    virtual void receiveResultFromHttpRequest(QNetworkReply *) = 0;
    virtual void executeHttpGetRequest(const QNetworkRequest& request) = 0;
    virtual void executeHttpDeleteRequest(const QNetworkRequest& request) = 0;
    virtual void executeHttpPutRequest(const QNetworkRequest& request, QHttpMultiPart* multiPart) = 0;
    virtual void executeHttpPostRequest(const QNetworkRequest& request, QHttpMultiPart* multiPart) = 0;
};

#endif // WEBSERVICEUSERINTERFACE_H

#include "NetworkReplyRepeater.h"
#include "WebServiceUserInterface.h"
// DEBUG
#include <QDebug>

NetworkReplyRepeater::NetworkReplyRepeater(QObject *receiver, int requestId) : QObject()
{
    this->receiver = receiver;
    this->requestId = requestId;
}

void    NetworkReplyRepeater::receiveNetworkReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    Services::WebServiceUserInterface* wbUser = dynamic_cast<Services::WebServiceUserInterface*>(this->receiver);
    if (wbUser)
        wbUser->receiveResultFromHttpRequest(reply, this->requestId);
    else
        qDebug() << " Not an instance of WebServiceUser";

    // THE USER WILL HAVE TO SET THE REPLY TO NULL AND CALL DELETELATER ON IT

}

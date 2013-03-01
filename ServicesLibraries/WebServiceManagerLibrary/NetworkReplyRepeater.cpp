#include "NetworkReplyRepeater.h"
#include "WebServiceUserInterface.h"
// DEBUG
#include <QDebug>

NetworkReplyRepeater::NetworkReplyRepeater(QObject *receiver) : QObject()
{
    this->receiver = receiver;
}

void    NetworkReplyRepeater::receiveNetworkReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    Services::WebServiceUserInterface* wbUser = dynamic_cast<Services::WebServiceUserInterface*>(this->receiver);
    if (wbUser)
        wbUser->receiveResultFromHttpRequest(reply);
    else
        qDebug() << " Not an instance of WebServiceUser";

    // THE USER WILL HAVE TO SET THE REPLY TO NULL AND CALL DELETELATER ON IT

}

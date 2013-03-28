#include "NetworkReplyRepeater.h"
#include "WebServiceUserInterface.h"
// DEBUG
#include <QDebug>

/*!
 * \class  NetworkReplyRepeater
 *
 * \brief Stores temporarly request information to handle asynchronously the request and
 * transmit the result to the sender on completion.
 */

/*!
 * Constructs a new NetworkReplyRepeater instance given a \a receiver and \a requestId.
 */
NetworkReplyRepeater::NetworkReplyRepeater(QObject *receiver, int requestId, void *data) : QObject()
{
    this->receiver = receiver;
    this->requestId = requestId;
    this->data = data;
}

/*!
 * Triggered when a result for the request is obtained. The result is then transmitted to user who made the
 * request along with an id it provided.
 */
void    NetworkReplyRepeater::receiveNetworkReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    Services::WebServiceUserInterface* wbUser = dynamic_cast<Services::WebServiceUserInterface*>(this->receiver);
    if (wbUser)
        wbUser->receiveResultFromHttpRequest(reply, this->requestId, this->data);
    else
        qDebug() << " Not an instance of WebServiceUser";
    // THE USER WILL HAVE TO SET THE REPLY TO NULL AND CALL DELETELATER ON IT
    delete this;


}

/****************************************************************************
**
** Copyright (C) Paul Lemire, Tepee3DTeam and/or its subsidiary(-ies).
** Contact: paul.lemire@epitech.eu
** Contact: tepee3d_2014@labeip.epitech.eu
**
** This file is part of the Tepee3D project
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
****************************************************************************/

#include "NetworkReplyRepeater.h"
#include "WebServiceUserInterface.h"
// DEBUG
#include <QDebug>

/*!
 * \class  NetworkReplyRepeater
 *
 * \brief Stores temporarly request information to handle asynchronously the request and
 * transmit the result to the sender on completion.
 *
 * \inmodule Tepee3D
 */

/*!
 * Constructs a new NetworkReplyRepeater instance given a \a receiver and \a requestId.
 */
NetworkReplyRepeater::NetworkReplyRepeater(QPointer<QObject> receiver, int requestId, QPointer<QObject> data, QHttpMultiPart *multiPart)
    : QObject()
{
    this->receiver = receiver;
    this->requestId = requestId;
    this->data = data;
    this->multiPart = multiPart;
}

NetworkReplyRepeater::~NetworkReplyRepeater()
{
    delete this->multiPart;
}

/*!
 * Triggered when a result for the request is obtained. The result is then transmitted to user who made the
 * request along with an id it provided.
 */
void    NetworkReplyRepeater::receiveNetworkReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    Services::WebServiceUserInterface* wbUser = NULL;
    if (reply == NULL)
        return ;
    if (!this->receiver.isNull())
         wbUser = qobject_cast<Services::WebServiceUserInterface*>(this->receiver.data());
    if (wbUser)
        wbUser->receiveResultFromHttpRequest(reply, this->requestId, this->data);
    else
        qDebug() << " Not an instance of WebServiceUser";
    // THE USER WILL HAVE TO SET THE REPLY TO NULL AND CALL DELETELATER ON IT
    delete this;
}

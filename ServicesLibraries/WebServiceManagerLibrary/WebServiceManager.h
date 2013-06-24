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

#define SERVICE_ID 1
#define SERVICE_VERSION "1.0.0"

class WebServiceManager : public QObject, Services::ServiceInterface
{
    Q_OBJECT
    Q_INTERFACES(Services::ServiceInterface)
    Q_PLUGIN_METADATA(IID "com.tepee3d.Services.webservices")
public:
    WebServiceManager();
    ~WebServiceManager();
    void          httpGet(QNetworkRequest& request, QHttpMultiPart*  multiPart, QObject *sender, int requestId, void *data);
    void          httpDelete(QNetworkRequest& request, QHttpMultiPart*  multiPart, QObject *sender, int requestId, void *data);
    void          httpPost(QNetworkRequest& request, QHttpMultiPart*  multiPart, QObject *sender, int requestId, void *data);
    void          httpPut(QNetworkRequest& request, QHttpMultiPart* multiPart, QObject *sender, int requestId, void *data);

    static  QJsonObject*    QJsonFromReply(QNetworkReply* reply);

    int                     getServiceId() const;
    void                    initLibraryConnection(QObject *parent);
    bool                    connectServiceToUser(QObject *user);
    bool                    disconnectServiceFromUser(QObject *user);
    QObject*                getLibraryQObject();
    QString                 getServiceVersion() const;

private:
    static  QNetworkAccessManager*  instance;
    QNetworkAccessManager*          getInstance();
    QHash<Services::WebServiceUserInterface::WebServiceRequestType, void (WebServiceManager::*)(QNetworkRequest&, QHttpMultiPart*, QObject*, int, void *)>       httpMethods;

private slots:
    void executeHttpRequest(QNetworkRequest request, Services::WebServiceUserInterface::WebServiceRequestType requestType,
                            QHttpMultiPart *multiPart, QObject *sender, int requestId, void *data);
signals:
    void initialized();
};



#endif // WEBSERVICEMANAGER_H

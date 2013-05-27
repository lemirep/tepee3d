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

#ifndef SERVICESMANAGER_H
#define SERVICESMANAGER_H

#include <QObject>
#include <QLibrary>
#include <QDir>
#include <QCoreApplication>
#include <QPluginLoader>
#include <QSqlRecord>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <Utils.h>
#include "ServiceInterface.h"
#include "DatabaseServiceUserInterface.h"
#include "WebServiceUserInterface.h"
#include "QmlContentExposerInterface.h"
#include "PlatformFactory.h"

// THIS CLASS WILL BE THE INTERMEDIARY BETWEEN ALL SERVICES (APART FROM STATIC FUNCTIONS)
// IT WILL CONNECT ALL THE NECESSARY SIGNAL
// LOAD THE SHARED LIBRARIES CONTAINING THE PLUGINS AND SO ON
// ADDITIONALLY THIS CLASS WILL CONTAIN Q_INVOKABLE METHODS AND BE EXPOSED TO THE QML ENGINE SO THAT
// QML CAN INVOKE METHODS DIRECTLY IF NEEDED



namespace Services
{

class ServicesManager : public QObject, public View::QmlContentExposerInterface
{
    Q_OBJECT
    Q_INTERFACES(View::QmlContentExposerInterface)

public:
    void    exposeContentToQml(QQmlContext *context);
    static  ServicesManager*        getInstance(QObject *parent = 0);
    static  void                    connectObjectToServices(QObject *serviceUser);
    static  void                    disconnectObjectFromServices(QObject *serviceUser);
    void                               loadServicesLibraries();

private:
    ServicesManager(QObject *parent = 0);
    QList<ServiceInterface*>        services;
    static ServicesManager          *instance;


public slots :
    void                            connectObjectToServicesSlot(QObject *serviceUser);
    void                            disconnectObjectFromServicesSlot(QObject *serviceUser);
    void                            libraryInitialized();

signals :
    void                            librariesInitialized();

};

}
#endif // SERVICESMANAGER_H

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

#ifndef PLUGINBASE_H
#define PLUGINBASE_H

#include <QPointer>
#include <QQuickItem>
#include <QNetworkRequest>
#include <QQmlExtensionPlugin>
#include <QHash>
#include <QVector3D>
#include <QJsonObject>
#include "Utils.h"
#include "PluginEnums.h"
#include "PluginInterface.h"
#include "DatabaseServiceUserInterface.h"
#include "WebServiceUserInterface.h"
#include "QmlContentExposerInterface.h"

namespace Plugins
{

class PluginBase : public QObject,
        Plugins::PluginInterface,
        public Services::DatabaseServiceUserInterface,
        public Services::WebServiceUserInterface,
        private View::QmlContentExposerInterface
{
    Q_OBJECT
    Q_INTERFACES(Plugins::PluginInterface)
    Q_INTERFACES(Services::DatabaseServiceUserInterface)
    Q_INTERFACES(Services::WebServiceUserInterface)
    Q_INTERFACES(View::QmlContentExposerInterface)

protected:
    // PLUGINS CANNOT BE INSTANCIATED DIRECTLY ONLY CREATED BY getPluginBase
    explicit PluginBase();
public:
    virtual  ~PluginBase();     // AS THE CLASS IS SUBJECT TO DYNAMIC CAST, THIS IS NECESSARY
    virtual int                         getPluginId()                    const  = 0;
    virtual bool                        needsUpdating()                  const;  // BY DEFAULT RETURNS FALSE
    virtual void                        updatePlugin();
    virtual void                        initPlugin()                            = 0;        //PERFORM NECESSARY INITIALIZATION HERE (HelperClasses, QmlModelClasses ...)
    virtual void                        clearPluginBeforeRemoval()              = 0;
    virtual QString                     getPluginVersion()               const  = 0;
    virtual QString                     getPluginName()                  const  = 0;
    virtual QString                     getPluginRepoName()              const  = 0;
    virtual QString                     getPluginDescription()           const  = 0;
    virtual QString                     getRoomPluginQmlFile()           const  = 0;
    virtual QString                     getMenuPluginQmlFile()           const  = 0;
    virtual PluginBase*                 createNewInstance()                     = 0;
    virtual QJsonObject                 toJsonRepresentation()           const;

    // IS IMPLEMENTED HERE TO EXPOSE THE SUBCLASS
    // LETTING PLUGINS IMPLEMENT IT IS TOO DANGEROUS
    void                                exposeContentToQml(QQmlContext *context);
    PluginBase*                         getPluginBase();
    PluginEnums::PluginState            getFocusState()                  const;
    void                                askForFocusState(PluginEnums::PluginState requestedState);
    // IMPLEMENTATIONS SHOULDN'T BE ABLE TO CHANGE THE PLUGIN POSITION THEMSELVES
    QVector3D                           getPluginPosition()              const;
    void                                setPluginPosition(const QVector3D &position);

protected:
    // VARIABLES
    PluginEnums::PluginState            focusState;
    // HANDLE FOCUS STATE CHANGES
    virtual void                onIdleFocusState();
    virtual void                onSelectedFocusState();
    virtual void                onFocusedFocusState();

private:
    QHash<Plugins::PluginEnums::PluginState, void (Plugins::PluginBase::*)()>  focusHandler;
    QVector3D                   m_position;
    // SQL
protected:
    virtual void receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, QPointer<QObject> data) = 0;

    // WEB SERVICES
protected:
    void    executeHttpGetRequest(const QNetworkRequest& request, int requestId, QPointer<QObject> data = QPointer<QObject>());
    void    executeHttpDeleteRequest(const QNetworkRequest& request, int requestId, QPointer<QObject> data = QPointer<QObject>());
    void    executeHttpPutRequest(const QNetworkRequest& request, QHttpMultiPart* multiPart, int requestId, QPointer<QObject> data = QPointer<QObject>());
    void    executeHttpPostRequest(const QNetworkRequest& request, QHttpMultiPart* multiPart, int requestId, QPointer<QObject> data = QPointer<QObject>());

    virtual void receiveResultFromHttpRequest(QNetworkReply *reply, int requestId, QPointer<QObject> data) = 0;

    // Defines all signals that a plugin can emit or receive
signals :
    void    executeSQLQuery(const QString& query, QPointer<QObject> sender, int id, const QString &dbName, QPointer<QObject> data = QPointer<QObject>());
    void    executeHttpRequest(const QNetworkRequest &request,
                               Services::WebServiceUserInterface::WebServiceRequestType requestType,
                               QHttpMultiPart *multipart,
                               QPointer<QObject> sender,
                               int requestId,
                               QPointer<QObject> data);
    void    askForFocusState(Plugins::PluginEnums::PluginState requestedState, QObject *sender);
    void    focusStateChanged(QVariant focusState, QVariant previousFocusState);
    void    roomEntered();
    void    roomLeft();

public slots :
    // SLOTS CAN BE VIRTUAL
    virtual void    onRoomEntered();
    virtual void    onRoomLeft();
    void            setFocusState(Plugins::PluginEnums::PluginState requestedState);
};

}
#endif // PLUGINBASE_H

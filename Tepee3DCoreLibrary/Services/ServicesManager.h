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
#include "ServiceInterface.h"
#include "DatabaseServiceUserInterface.h"
#include "WebServiceUserInterface.h"
#include "QmlContentExposerInterface.h"

// THIS CLASS WILL BE THE INTERMEDIARY BETWEEN ALL SERVICES (APART FROM STATIC FUNCTIONS)
// IT WILL CONNECT ALL THE NECESSARY SIGNAL
// LOAD THE SHARED LIBRARIES CONTAINING THE PLUGINS AND SO ON
// ADDITIONALLY THIS CLASS WILL CONTAIN Q_INVOKABLE METHODS AND BE EXPOSED TO THE QML ENGINE SO THAT
// QML CAN INVOKE METHODS DIRECTLY IF NEEDED


#define SERVICE_LIBRARIES_DIRECTORY "libraries/services_lib"

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
    void                            loadServicesLibraries();

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

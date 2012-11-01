#include "ServicesManager.h"

// FOR DEBUG
#include <QDebug>

Services::ServicesManager::ServicesManager(QObject *parent) : QObject(parent)
{
    this->services = QList<ServiceInterface*>();
    this->loadServicesLibraries();
}

void    Services::ServicesManager::exposeContentToQml(QQmlContext *context)
{
}

void    Services::ServicesManager::connectObjectToServices(QObject *serviceUser)
{
    qDebug() << "Connecting object to services";

    foreach (ServiceInterface* service, this->services)
        service->connectServiceToUser(serviceUser);

//        service->

//    // SQL
//    if (dynamic_cast<DatabaseServiceUserInterface*>(serviceUser) != NULL)
//        QObject::connect(serviceUser, SIGNAL(executeSQLQuery(const QString &, QObject *)),
//                         this, SIGNAL(executeSQLQuery(const QString&,QObject*)));
//    // HTTP
//    if (dynamic_cast<WebServiceUserInterface*>(serviceUser) != NULL)
//        QObject::connect(serviceUser, SIGNAL(executeHttpRequest(const QNetworkRequest&, int, QHttpMultiPart*, QObject*)),
//                         this, SIGNAL(executeHttpRequest(const QNetworkRequest&, int, QHttpMultiPart*, QObject*)));
}

void    Services::ServicesManager::disconnectObjectFromServices(QObject *serviceUser)
{
    qDebug() << "Disconnecting object from services";

    foreach (ServiceInterface* service, this->services)
        service->disconnectServiceFromUser(serviceUser);
//    // SQL
//    if (dynamic_cast<DatabaseServiceUserInterface*>(serviceUser) != NULL)
//        QObject::disconnect(serviceUser, SIGNAL(executeSQLQuery(const QString &, QObject *)),
//                            this, SIGNAL(executeSQLQuery(const QString&,QObject*)));
    // HTTP
//    if (dynamic_cast<WebServiceUserInterface*>(serviceUser) != NULL)
//        QObject::connect(serviceUser, SIGNAL(executeHttpRequest(const QNetworkRequest&, int, QHttpMultiPart*, QObject*)),
//                         this, SIGNAL(executeHttpRequest(const QNetworkRequest&, int, QHttpMultiPart*, QObject*)));
}

bool    Services::ServicesManager::loadServicesLibraries()
{
    QDir    serviceDirectory = QApplication::applicationDirPath();

    // GO TO LIB DIRECTORIES
#if defined(Q_OS_WIN)
    if (serviceDirectory.dirName().toLower() == "debug" || serviceDirectory.dirName().toLower() == "release")
        serviceDirectory.cdUp();
#elif defined(Q_OS_MAC)
    if (serviceDirectory.dirName() == "MacOS")
    {
        serviceDirectory.cdUp();
        serviceDirectory.cdUp();
        serviceDirectory.cdUp();
    }
#endif
    serviceDirectory.cdUp();
    serviceDirectory.cd(SERVICE_LIBRARIES_DIRECTORY);

    qDebug() << "SERVICE DIR " << serviceDirectory.absolutePath();
    // LOAD ALL SERVICES LIBRARIES FOUND IN DIRECTORY
    foreach (QString filename, serviceDirectory.entryList(QDir::Files))
    {
        qDebug() << "SERVICE LIBRARY " << filename;
        QPluginLoader loader(serviceDirectory.absoluteFilePath(filename));
        ServiceInterface* service = qobject_cast<ServiceInterface *>(loader.instance());
        if (service)
        {
            this->services.push_back(service);
            service->initLibraryConnection(this);
            qDebug() << "LIBRARY INITIALIZED";
        }
        else
        {
            qCritical() << "ERRORS : "<< loader.errorString();
            qCritical() << "FAILED TO LOAD LIBRARY";
        }
    }
    return true;
}

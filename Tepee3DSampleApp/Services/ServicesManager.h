#ifndef SERVICESMANAGER_H
#define SERVICESMANAGER_H

#include <QObject>
#include <QLibrary>
#include <QDir>
#include <QApplication>
#include <QPluginLoader>
#include <QSqlRecord>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSignalMapper>
#include "ServiceInterface.h"
#include "QmlContentExposerInterface.h"

// THIS CLASS WILL BE THE INTERMEDIARY BETWEEN ALL SERVICES (APART FROM STATIC FUNCTIONS)
// IT WILL CONNECT ALL THE NECESSARY SIGNAL
// LOAD THE SHARED LIBRARIES CONTAINING THE PLUGINS AND SO ON
// ADDITIONALLY THIS CLASS WILL CONTAIN Q_INVOKABLE METHODS AND BE EXPOSED TO THE QML ENGINE SO THAT
// QML CAN INVOKE METHODS DIRECTLY


#define SERVICE_LIBRARIES_DIRECTORY "libraries/services_lib"

namespace Services
{

class ServicesManager : public QObject, public QmlContentExposerInterface
{
public:
    ServicesManager(QObject *parent = 0);

    void    exposeContentToQml(QQmlContext *context);

private:


    bool    loadServicesLibraries();


signals :
    void executeSQLQuery(QString query, QObject *sender);
// wiil send to sender ->  void resultFromSQLQuery(QList<QSqlRecord>, int pluginId);

    void executeHttpRequest(QNetworkRequest *, QObject *sender);
// will send to sender ->  void resultFromHttpRequest(QNetworkReply *);

};

}
#endif // SERVICESMANAGER_H

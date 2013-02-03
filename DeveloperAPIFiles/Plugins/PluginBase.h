#ifndef PLUGINBASE_H
#define PLUGINBASE_H

#include <QObject>
#include <QNetworkRequest>
#include <QQmlExtensionPlugin>
#include "PluginEnums.h"
#include "PluginInterface.h"
#include "DatabaseServiceUserInterface.h"
#include "WebServiceUserInterface.h"
#include "QmlContentExposerInterface.h"

namespace Plugins
{

class PluginBase : public QObject,
        Plugins::PluginInterface,
        public DatabaseServiceUserInterface,
        public WebServiceUserInterface,
        public QmlContentExposerInterface
{
    Q_OBJECT
    Q_INTERFACES(Plugins::PluginInterface)

public:

    PluginBase();
    virtual int                 getPluginId()               = 0;
    virtual bool                needsUpdating()             const;                    // BY DEFAULT RETURNS FALSE
    virtual void                initPlugin()                = 0;    //PERFORM NECESSARY INITIALIZATION HERE (HelperClasses, QmlModelClasses ...)
    virtual QString             getPluginName()             = 0;
    virtual QString             getPluginDescription()      = 0;
    virtual QString             getRoomPluginQmlFile()      const = 0;
    virtual QString             getMenuPluginQmlFile()      const = 0;
    virtual PluginBase*         createNewInstance()         = 0;
    virtual void                exposeContentToQml(QQmlContext *context) = 0;
    PluginBase*                 getPluginBase();
    PluginEnums::PluginState    getFocusState()             const;
    void                        askForFocusState(PluginEnums::PluginState requestedState);
    // VARIABLES
protected:
    PluginEnums::PluginState            focusState;

    // SQL
protected:
    virtual void receiveResultFromSQLQuery(const QList<QSqlRecord> &result, int id) = 0;

    // WEB SERVICES
protected:
    void executeHttpGetRequest(const QNetworkRequest& request);
    void executeHttpDeleteRequest(const QNetworkRequest& request);
    void executeHttpPutRequest(const QNetworkRequest& request, QHttpMultiPart* multiPart);
    void executeHttpPostRequest(const QNetworkRequest& request, QHttpMultiPart* multiPart);

    virtual void receiveResultFromHttpRequest(QNetworkReply *) = 0;

    // Defines all signals that a plugin can emit or receive
signals :
    void    executeSQLQuery(const QString& query, QObject *sender, int id);
    void    executeHttpRequest(const QNetworkRequest &request, int requestType, QHttpMultiPart *multipart, QObject *sender);
    void    askForFocusState(Plugins::PluginEnums::PluginState requestedState, QObject *sender);
    void    focusStateChanged(QVariant focusState);
    void    roomEntered();
    void    roomLeft();


public slots :
    // Define slots as virtual so that developpers can subclass them if necessary
    virtual void    resultFromSQL(); // EXAMPLE SLOT NOT USED
    void            setFocusState(Plugins::PluginEnums::PluginState requestedState);
    void            onRoomEntered();
};

}
#endif // PLUGINBASE_H

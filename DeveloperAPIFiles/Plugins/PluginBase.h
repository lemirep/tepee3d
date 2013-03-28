#ifndef PLUGINBASE_H
#define PLUGINBASE_H

#include <QQuickItem>
#include <QNetworkRequest>
#include <QQmlExtensionPlugin>
#include <QHash>
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
        public View::QmlContentExposerInterface
{
    Q_OBJECT
    Q_INTERFACES(Plugins::PluginInterface)

public:

    explicit PluginBase();
    virtual int                 getPluginId()               = 0;
    virtual bool                needsUpdating()             const;  // BY DEFAULT RETURNS FALSE
    virtual void                initPlugin()                = 0;    //PERFORM NECESSARY INITIALIZATION HERE (HelperClasses, QmlModelClasses ...)
    virtual QString             getPluginName()             = 0;
    virtual QString             getPluginDescription()      = 0;
    virtual QString             getRoomPluginQmlFile()      const = 0;
    virtual QString             getMenuPluginQmlFile()      const = 0;
    virtual PluginBase*         createNewInstance()         = 0;

    // IS IMPLEMENTED HERE TO EXPOSE THE SUBCLASS
    // LETTING PLUGINS IMPLEMENT IT IS TO DANGEROUS
    void                        exposeContentToQml(QQmlContext *context);
    PluginBase*                 getPluginBase();
    PluginEnums::PluginState    getFocusState()             const;
    void                        askForFocusState(PluginEnums::PluginState requestedState);
    // VARIABLES
protected:
    PluginEnums::PluginState            focusState;
    // HANDLE FOCUS STATE CHANGES
    virtual void                onIdleFocusState();
    virtual void                onSelectedFocusState();
    virtual void                onFocusedFocusState();

private:
    QHash<Plugins::PluginEnums::PluginState, void (Plugins::PluginBase::*)()>  focusHandler;

    // SQL
protected:
    virtual void receiveResultFromSQLQuery(QList<QSqlRecord> result, int id) = 0;

    // WEB SERVICES
protected:
    void executeHttpGetRequest(const QNetworkRequest& request, int requestId, void *data = 0);
    void executeHttpDeleteRequest(const QNetworkRequest& request, int requestId, void *data = 0);
    void executeHttpPutRequest(const QNetworkRequest& request, QHttpMultiPart* multiPart, int requestId, void *data = 0);
    void executeHttpPostRequest(const QNetworkRequest& request, QHttpMultiPart* multiPart, int requestId, void *data = 0);

    virtual void receiveResultFromHttpRequest(QNetworkReply *reply, int requestId, void *data) = 0;

    // Defines all signals that a plugin can emit or receive
signals :
    void    executeSQLQuery(const QString& query, QObject *sender, int id);
    void    executeHttpRequest(const QNetworkRequest &request, int requestType, QHttpMultiPart *multipart, QObject *sender, int requestId, void *data);
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

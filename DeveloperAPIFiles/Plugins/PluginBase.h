#ifndef PLUGINBASE_H
#define PLUGINBASE_H

#include <QObject>
#include <QNetworkRequest>
#include "PluginInterface.h"
#include "DatabaseServiceUserInterface.h"
#include "WebServiceUserInterface.h"

namespace Plugins
{

class PluginBase : public QObject,
                   Plugins::PluginInterface,
                   public DatabaseServiceUserInterface,
                   public WebServiceUserInterface
{
    Q_OBJECT
    Q_INTERFACES(Plugins::PluginInterface)
public:
    PluginBase();
    virtual int             getPluginId()               = 0;
    virtual void            initPlugin()                = 0;    //PERFORM NECESSARY INITIALIZATION HERE (HelperClasses, QmlModelClasses ...)
    virtual QString         getPluginName()             = 0;
    virtual QString         getPluginDescription()      = 0;
    PluginBase*             getPluginBase();
    virtual PluginBase*     createNewInstance()         = 0;
    virtual bool            needsUpdating()             const;                    // BY DEFAULT RETURNS FALSE
    virtual QString         getRoomPluginQmlFile()      const = 0;
    virtual QString         getFocusedPluginQmlFile()   const = 0;


    // SQL

protected:
    virtual void receiveResultFromSQLQuery(const QList<QSqlRecord> &result) = 0;


    // WEB SERVICES
protected:
    void executeHttpGetRequest(const QNetworkRequest& request);
    void executeHttpDeleteRequest(const QNetworkRequest& request);
    void executeHttpPutRequest(const QNetworkRequest& request, QHttpMultiPart* multiPart);
    void executeHttpPostRequest(const QNetworkRequest& request, QHttpMultiPart* multiPart);

    virtual void receiveResultFromHttpRequest(QNetworkReply *) = 0;


// Define all signals that a plugin can emit or receive
signals :
    void    executeSQLQuery(const QString& query, QObject *sender);
    void    executeHttpRequest(const QNetworkRequest &request, int requestType, QHttpMultiPart *multipart, QObject *sender);

public slots :
    // Define slots as virtual so that developpers can subclass them if necessary
    virtual void    resultFromSQL(); // EXAMPLE SLOT NOT USED
};

}
#endif // PLUGINBASE_H

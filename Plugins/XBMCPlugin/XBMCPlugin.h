#ifndef XBMCPLUGIN_H
#define XBMCPLUGIN_H

#include <QObject>
#include <QtGui>
#include "QtQml"
#include <QQuickView>
#include <QQuickItem>
#include <QHash>
#include "PluginBase.h"
#include "DatabaseServiceUserInterface.h"
#include "WebServiceUserInterface.h"
#include "IWebRequestDispatcher.h"

#define PLUGIN_ID 12

class XBMCPlugin  : public Plugins::PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.tepee3d.plugins.xbmcplugin")

public:
    XBMCPlugin();
    int                          getPluginId();
    void                        initPlugin();
    void                        clearPluginBeforeRemoval();

    Q_INVOKABLE QString         getPluginName();

    QString                     getPluginDescription();

    PluginBase*                 getPluginBase();
    PluginBase*                 createNewInstance();

    QString                     getRoomPluginQmlFile() const;
    QString                     getMenuPluginQmlFile() const;
    // DatabaseServiceUserInterface
    void                        receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, void *data);
    // WebServiceUserInterface
    void                        receiveResultFromHttpRequest(QNetworkReply * reply,int id, void *data);

private:
    QHash<int, void (IWebRequestDispatcher::*)(QNetworkReply *, int, void *)> networkRequestResultDispatch;
};

#endif // XBMCPLUGIN_H

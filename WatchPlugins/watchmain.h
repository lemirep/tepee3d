#ifndef WATCHMAIN_H
#define WATCHMAIN_H

#include "PluginBase.h"
#include <iostream>
#include <QObject>
#include <QDebug>
#include <QtGui>
#include "QtQml"
#include <QQuickView>
#include <QQuickItem>
#include "DatabaseServiceUserInterface.h"
#include "WebServiceUserInterface.h"

class watchMain  : public Plugins::PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.tepee3d.plugins.watchplugin")

public:
    watchMain();
    int                     getPluginId();
    void                    initPlugin();
    Q_INVOKABLE QString     getPluginName();
    QString                 getPluginDescription();
    PluginBase*             getPluginBase();
    PluginBase*             createNewInstance();
    QString                 getRoomPluginQmlFile() const;
    QString                 getMenuPluginQmlFile() const;
    void                    receiveResultFromSQLQuery(QList<QSqlRecord> result, int id);
    void                    receiveResultFromHttpRequest(QNetworkReply * reply);
    void                    exposeContentToQml(QQmlContext *context);
};

#endif // WATCHMAIN_H

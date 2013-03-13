#ifndef DUMMY_H
#define DUMMY_H

#include "PluginBase.h"
#include <iostream>
#include <QObject>
#include <QtGui>
#include "QtQml"
#include <QQuickView>
#include <QQuickItem>
#include "DatabaseServiceUserInterface.h"
#include "WebServiceUserInterface.h"

class Dummy  : public Plugins::PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.tepee3d.plugins.dummyproject")

public:
    Dummy();
    int                          getPluginId();
    void                        initPlugin();
    Q_INVOKABLE QString         getPluginName();
    QString                     getPluginDescription();
    PluginBase*                 getPluginBase();
    PluginBase*                 createNewInstance();
    QString                     getRoomPluginQmlFile() const;
    QString                     getMenuPluginQmlFile() const;
    // DatabaseServiceUserInterface
    void                        receiveResultFromSQLQuery(QList<QSqlRecord> result, int id);
    // WebServiceUserInterface
    void                        receiveResultFromHttpRequest(QNetworkReply * reply,int id);
    void                        exposeContentToQml(QQmlContext *context);
};

#endif // DUMMY_H

#ifndef DUMMYPROJECT_H
#define DUMMYPROJECT_H

#include <QObject>
#include <QtGui>
#include "QtQml"
#include <QQuickView>
#include <QQuickItem>
#include "PluginBase.h"
#include "DatabaseServiceUserInterface.h"
#include "WebServiceUserInterface.h"

class DummyProject  : public Plugins::PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.tepee3d.plugins.dummyproject")

public:
    DummyProject();
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

#endif // DUMMYPROJECT_H

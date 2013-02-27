#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>
#include <QtPlugin>

#include <iostream>
#include <QObject>
#include <QDebug>
#include <QtGui>
#include "QtQml"
#include <QQuickView>
#include <QQuickItem>
#include "PluginBase.h"
#include "DatabaseServiceUserInterface.h"
#include "WebServiceUserInterface.h"
#include "widgetmodel.h"


#define  ASSIGNCOLOR 2

class TestPlugin : public Plugins::PluginBase          // MANDATORY FOR PLUGIN DEVELOPMENT
{
    Q_OBJECT                        // NECESSARY FOR QOBJECT INHERITANCE
    Q_PLUGIN_METADATA(IID "com.tepee3d.plugins.testplugin")

private:
    QString colorSelect;
    QQmlContext *context;

public:
    TestPlugin();
    int                     getPluginId();
    void                    initPlugin();
    Q_INVOKABLE QString                 getPluginName();
    QString                 getPluginDescription();
    PluginBase*             getPluginBase();
    PluginBase*             createNewInstance();

    QString                 getRoomPluginQmlFile() const;
    QString                 getMenuPluginQmlFile() const;
    // DatabaseServiceUserInterface
    void                    receiveResultFromSQLQuery(QList<QSqlRecord> result, int id);
    // WebServiceUserInterface
    void                    receiveResultFromHttpRequest(QNetworkReply * reply);
    void                    exposeContentToQml(QQmlContext *context);
    void setColor(QString color);
    Q_INVOKABLE void selectColor(QString color);
    Q_INVOKABLE QString getColor();


};

#endif // PLUGIN_H

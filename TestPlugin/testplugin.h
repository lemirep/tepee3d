#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>
#include <QtPlugin>
<<<<<<< HEAD
=======
#include <iostream>
#include <QObject>
#include <QDebug>
#include <QtGui>
#include "QtQml"
>>>>>>> 79f3df03274d66b07efe1845e744f5d881c3dc68
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
<<<<<<< HEAD
\
=======

>>>>>>> 79f3df03274d66b07efe1845e744f5d881c3dc68
public:
    TestPlugin();
    int                     getPluginId();
    void                    initPlugin();
    QString                 getPluginName();
    QString                 getPluginDescription();
    PluginBase*             getPluginBase();
    PluginBase*             createNewInstance();

    QString                 getRoomPluginQmlFile() const;
    QString                 getMenuPluginQmlFile() const;
    // DatabaseServiceUserInterface
    void                    receiveResultFromSQLQuery(const QList<QSqlRecord> &result, int id);
    // WebServiceUserInterface
    void                    receiveResultFromHttpRequest(QNetworkReply * reply);
<<<<<<< HEAD
    void                    exposeContentToQml(QQmlContext *context);

     Q_INVOKABLE void selectColor(QString color);
=======

signals :
    void qmlSignal();
public slots:
    void cppSlot();
>>>>>>> 79f3df03274d66b07efe1845e744f5d881c3dc68
};

#endif // PLUGIN_H

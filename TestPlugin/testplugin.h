#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QQuickView>
#include <QQuickItem>
#include "PluginBase.h"
#include "DatabaseServiceUserInterface.h"
#include "WebServiceUserInterface.h"

class TestPlugin : public Plugins::PluginBase          // MANDATORY FOR PLUGIN DEVELOPMENT
{
    Q_OBJECT                        // NECESSARY FOR QOBJECT INHERITANCE
    Q_PLUGIN_METADATA(IID "com.tepee3d.plugins.testplugin")
\
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
    void                    receiveResultFromSQLQuery(const QList<QSqlRecord> &result);
    // WebServiceUserInterface
    void                    receiveResultFromHttpRequest(QNetworkReply * reply);

signals :
    void selectColorSignal(QString color);
public slots:
    void SaveColorDB(QString color);

};

#endif // PLUGIN_H

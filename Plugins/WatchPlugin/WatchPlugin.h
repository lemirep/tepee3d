#ifndef WATCHPLUGIN_H
#define WATCHPLUGIN_H

#include <QtPlugin>
#include <QDebug>
#include <QQuickItem>
#include <PluginBase.h>
#include <QDateTime>
#include <QLCDNumber>
class WatchPlugin : public Plugins::PluginBase          // MANDATORY FOR PLUGIN DEVELOPMENT
{
    Q_OBJECT                        // NECESSARY FOR QOBJECT INHERITANCE
    Q_PLUGIN_METADATA(IID "com.tepee3d.plugins.WatchPlugin")

private:
    QQmlContext *context;

protected:
    void                onIdleFocusState();
    void                onSelectedFocusState();
    void                onFocusedFocusState();

public:
    WatchPlugin();
    int                     getPluginId();
    void                    initPlugin();
    Q_INVOKABLE QString     getPluginName();
    Q_INVOKABLE QString     getPluginDescription();
    PluginBase*             getPluginBase();
    PluginBase*             createNewInstance();
    QString                 getRoomPluginQmlFile() const;
    QString                 getMenuPluginQmlFile() const;
    // DatabaseServiceUserInterface
    void                    receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, void *data);
    // WebServiceUserInterface
    void                    receiveResultFromHttpRequest(QNetworkReply * reply, int requestId, void *data);
    Q_INVOKABLE QString     getTime();
private slots :

    void                    onFocusStateChanged();


};
#endif // WATCHPLUGIN_H

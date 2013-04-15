#ifndef WATCHPLUGIN_H
#define WATCHPLUGIN_H

#include <QDebug>
#include <QQuickItem>
#include <PluginBase.h>
#include <QDateTime>
#include <QLCDNumber>
#include <QObject>
#include <QtGui>
#include "QtQml"
#include <QQuickView>
#include <QQuickItem>
#include <QHash>
#include <PluginBase.h>
#include <DatabaseServiceUserInterface.h>
#include <WebServiceUserInterface.h>
#include <SubListedListModel.h>
#include <Utils.h>
#include "ClockListItem.h"

#define DATABASE_NAME "WatchPlugin.sql"
#define RETRIEVE_CLOCK 0


class WatchPlugin : public Plugins::PluginBase          // MANDATORY FOR PLUGIN DEVELOPMENT
{
    Q_OBJECT                        // NECESSARY FOR QOBJECT INHERITANCE
    Q_PLUGIN_METADATA(IID "com.tepee3d.plugins.WatchPlugin")

protected:
    void                onIdleFocusState();
    void                onSelectedFocusState();
    void                onFocusedFocusState();

public:
    WatchPlugin();
    int                     getPluginId();
    void                    initPlugin();
    void                    clearPluginBeforeRemoval();
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
    Q_INVOKABLE                 QObject* getClockModel() const;

private slots :
    void                    onFocusStateChanged();

private:
    QQmlContext *context;
    Models::ListModel* clockModel;
    QHash<int, void (WatchPlugin::*)(QList<QSqlRecord>, void*)> databaseCallBacks;
    void                    retrieveClocksFromDatabaseCallBack(QList<QSqlRecord> result, void *data);
    void retrieveClocksFromDababase();

};
#endif // WATCHPLUGIN_H

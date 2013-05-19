#ifndef AGENDAPLUGIN_H
#define AGENDAPLUGIN_H


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
#include <QJsonDocument>
#include <Utils.h>

#define PLUGIN_ID 11

#define DATABASE_NAME "AgendaPlugin.sql"

class AgendaPlugin : public Plugins::PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.tepee3d.plugins.AgendaPlugin")

    Q_PROPERTY(QString pluginState WRITE setPluginState READ pluginState NOTIFY pluginStateChanged)
    Q_PROPERTY(QString sickBeardUrl WRITE setSickBeardUrl READ sickBeardUrl NOTIFY sickBeardUrlChanged)
    Q_PROPERTY(QString sickBeardApi WRITE setSickBeardApi READ sickBeardApi NOTIFY sickBeardApiChanged)
    Q_PROPERTY(bool addToSickBeard WRITE setAddToSickBeard READ addToSickBeard NOTIFY addToSickBeardChanged)
    Q_PROPERTY(bool synchingWebServices READ getSynching NOTIFY synchingChanged)
public:
    AgendaPlugin();
    int                         getPluginId();
    void                        initPlugin();
    void                        clearPluginBeforeRemoval();
    Q_INVOKABLE QString         getPluginName();
    QString                     getPluginDescription();
    PluginBase*                 getPluginBase();
    PluginBase*                 createNewInstance();
    QString                     getRoomPluginQmlFile() const;
    QString                     getMenuPluginQmlFile() const;

    // QML called function
    Q_INVOKABLE QString getMonth() const;
    Q_INVOKABLE int getBeginDayOfTheMonth() const;
    Q_INVOKABLE int getMonthLength() const;

    // FOCUS STATE HANDLERS
    void                onIdleFocusState();
    void                onSelectedFocusState();
    void                onFocusedFocusState();

    // DatabaseServiceUserInterface
    void                        receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, void *data);
    // WebServiceUserInterface
    void                        receiveResultFromHttpRequest(QNetworkReply * reply,int id, void *data);

    QString                              pluginState() const;
    void                                 setPluginState(const QString& value);

    QString                              sickBeardApi() const;
    QString                              sickBeardUrl() const;
    bool                                 addToSickBeard() const;
    void                                 setSickBeardUrl(const QString &sickBeardUrl);
    void                                 setSickBeardApi(const QString &sickBeardApi);
    void                                 setAddToSickBeard(bool value);

    bool                                 getSynching() const;

private:
    int                         currentWebQueriesCount;
    QString                     m_sickBeardUrl;
    QString                     m_sickBeardApiKey;
    QString                     m_pluginState;
    bool                        m_addToSickBeard;
    bool                        m_synchingWithSB;

    QDate                       currentDate;


    QHash<int, void (AgendaPlugin::*)(QNetworkReply*, void*)> webServicesCallBacks;
    QHash<int, void (AgendaPlugin::*)(QList<QSqlRecord>, void*)> databaseCallBacks;


private slots :

    void                        webQueryEmitted();

signals :

    void                        pluginStateChanged();
    void                        sickBeardUrlChanged();
    void                        sickBeardApiChanged();
    void                        addToSickBeardChanged();
    void                        synchingChanged();
};

#endif // AGENDAPLUGIN_H

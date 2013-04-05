#ifndef TWITTERPLUGIN_H
#define TWITTERPLUGIN_H

#include <QtPlugin>
#include <QDebug>
#include <QQuickItem>
#include "oauthtwitter.h"
#include "qtweethometimeline.h"
#include "qtweetmentions.h"
#include "qtweetusertimeline.h"
#include "qtweetdirectmessages.h"
#include "qtweetstatus.h"
#include "qtweetdmstatus.h"
#include "qtweetuser.h"
#include <PluginBase.h>

class TwitterPlugin : public Plugins::PluginBase          // MANDATORY FOR PLUGIN DEVELOPMENT
{
    Q_OBJECT                        // NECESSARY FOR QOBJECT INHERITANCE
    Q_PLUGIN_METADATA(IID "com.tepee3d.plugins.TwitterPlugin")

private:
    QQmlContext *context;
    OAuthTwitter *m_oauthTwitter;

protected:
    void                onIdleFocusState();
    void                onSelectedFocusState();
    void                onFocusedFocusState();

public:
    TwitterPlugin();
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
private slots :

    void                    onFocusStateChanged();
    void                    xauthFinished();
    void                    xauthError();
};


#endif // TWITTERPLUGIN_H

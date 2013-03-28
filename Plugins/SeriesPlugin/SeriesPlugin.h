#ifndef SERIESPLUGIN_H
#define SERIESPLUGIN_H

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

#include "SerieSubListedItem.h"

#define PLUGIN_ID 10
#define SEARCH_SHOW_REQUEST 0
#define SEARCH_EPISODE_REQUEST 1
#define GET_SEASONS 2
#define GET_EPISODES_FOR_SEASON 3
#define TRAKT_API_KEY "9a67e6b3bc1cbd1d92fdc56a03b51267"

class SeriesPlugin  : public Plugins::PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.tepee3d.plugins.SeriesPlugin")

public:
    SeriesPlugin();
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

    Q_INVOKABLE                 QObject* getFollowedSeriesModel();
    Q_INVOKABLE                 void               searchForShow(QString showName);
    Q_INVOKABLE                 void               searchForEpisode(QString episodeName);
    Q_INVOKABLE                 QObject* getSeasonsForShow(QString title);
    Q_INVOKABLE                 QObject* getEpisodesForShowSeason(QString title, int season);

private:
    Models::SubListedListModel* followedSeriesModel;
    QHash<int, void (SeriesPlugin::*)(QNetworkReply*)> webServicesCallBacks;

    void                        searchForShowCallBack(QNetworkReply *reply);
    void                        searchForEpisodeBack(QNetworkReply *reply);
    void                        getSeasonsForShowCallBack(QNetworkReply *reply);
    void                        getEpisodesForSeasonCallBack(QNetworkReply *reply);

};

#endif // SERIESPLUGIN_H

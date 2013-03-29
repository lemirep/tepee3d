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

#define RETRIEVE_SHOWS 0
#define RETRIEVE_SEASONS_FOR_SHOW 1
#define RETRIEVE_EPISODES_FOR_SHOW_SEASON 2
#define CHECK_IF_DATABASE_FORMAT_EXISTS 3
#define GENERIC_REQUEST 4

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
    void                        receiveResultFromHttpRequest(QNetworkReply * reply,int id, void *data);

    Q_INVOKABLE                 QObject* getFollowedSeriesModel();
    Q_INVOKABLE                 QObject* getSeasonsModelFromSerieId(int serieId);
    Q_INVOKABLE                 QObject* getEpisodesFromSeasonAndShowId(int serieId, int seasonId);
    Q_INVOKABLE                 void     searchForShow(QString showName);
    Q_INVOKABLE                 void     searchForEpisode(QString episodeName);

private:
    Models::SubListedListModel* followedSeriesModel;
    QHash<int, void (SeriesPlugin::*)(QNetworkReply*, void*)> webServicesCallBacks;
    QHash<int, void (SeriesPlugin::*)(QList<QSqlRecord>)> databaseCallBacks;

    void                        getSeasonsForShow(SerieSubListedItem *show);
    void                        getEpisodesForShowAndSeason(QString showName, SeasonSubListedItem *season);

    // WEBSERVICES CALLBACK
    void                        searchForShowCallBack(QNetworkReply *reply, void *data);
    void                        searchForEpisodeCallBack(QNetworkReply *reply, void *data);
    void                        getSeasonsForShowCallBack(QNetworkReply *reply, void *data);
    void                        getEpisodesForSeasonCallBack(QNetworkReply *reply, void *data);

    // DATABASE CALLBACK
    void                        retrieveShowsFromDatabaseCallBack(QList<QSqlRecord> result);
    void                        retrieveSeasonsForShowDatabaseCallBack(QList<QSqlRecord> result);
    void                        retrieveEpisodesForShowSeasonDatabaseCallBack(QList<QSqlRecord> result);
    void                        checkIfDatabaseSchemaExists(QList<QSqlRecord> result);
    void                        genericDatabaseCallBack(QList<QSqlRecord> result);
};

#endif // SERIESPLUGIN_H

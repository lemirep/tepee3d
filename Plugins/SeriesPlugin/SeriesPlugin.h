/****************************************************************************
**
** Copyright (C) Paul Lemire, Tepee3DTeam and/or its subsidiary(-ies).
** Contact: paul.lemire@epitech.eu
** Contact: tepee3d_2014@labeip.epitech.eu
**
** This file is part of the Tepee3D project
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
****************************************************************************/

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
#include <Utils.h>

#include "SerieSubListedItem.h"

#define PLUGIN_ID 10

#define SEARCH_SHOW_REQUEST 0
#define GET_SHOW_SUMMARY 1
#define UPDATE_SHOW_SUMMARY 2
#define GET_SICKBEARD_SHOWS 3
#define UPDATE_SICKBEARD_SHOW 4
#define ADD_SHOW_TO_SICKBEARD 5
#define UPDATE_SEASON_EPISODES_SICKBEARD 6
#define UPDATE_UPDATED_SHOW 7

#define RETRIEVE_SHOWS 0
#define RETRIEVE_SEASONS_FOR_SHOW 1
#define RETRIEVE_EPISODES_FOR_SHOW_SEASON 2
#define GENERIC_REQUEST 3
#define RETRIEVE_SICKBEARD_CONFIG 4


#define DATABASE_NAME "SeriesPlugin.sql"
#define TRAKT_API_KEY "9a67e6b3bc1cbd1d92fdc56a03b51267"

class SeriesPlugin  : public Plugins::PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.tepee3d.plugins.SeriesPlugin")

    Q_PROPERTY(QString pluginState WRITE setPluginState READ pluginState NOTIFY pluginStateChanged)
    Q_PROPERTY(QString sickBeardUrl WRITE setSickBeardUrl READ sickBeardUrl NOTIFY sickBeardUrlChanged)
    Q_PROPERTY(QString sickBeardApi WRITE setSickBeardApi READ sickBeardApi NOTIFY sickBeardApiChanged)
    Q_PROPERTY(bool addToSickBeard WRITE setAddToSickBeard READ addToSickBeard NOTIFY addToSickBeardChanged)
public:
    SeriesPlugin();
    int                         getPluginId();
    void                        initPlugin();
    void                        clearPluginBeforeRemoval();
    Q_INVOKABLE QString         getPluginName();
    QString                     getPluginDescription();
    PluginBase*                 getPluginBase();
    PluginBase*                 createNewInstance();
    QString                     getRoomPluginQmlFile() const;
    QString                     getMenuPluginQmlFile() const;


    // FOCUS STATE HANDLERS
    void                onIdleFocusState();
    void                onSelectedFocusState();
    void                onFocusedFocusState();

    // DatabaseServiceUserInterface
    void                        receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, void *data);
    // WebServiceUserInterface
    void                        receiveResultFromHttpRequest(QNetworkReply * reply,int id, void *data);

    Q_INVOKABLE                 QObject* getFollowedSeriesModel() const;
    Q_INVOKABLE                 QObject* getSeasonsModelFromSerieId(int serieId) const;
    Q_INVOKABLE                 QObject* getEpisodesFromSeasonAndShowId(int serieId, int seasonId) const;
    Q_INVOKABLE                 QObject* getSearchSeriesModel() const;
    Q_INVOKABLE                 QObject* getShowsToAppearInTheWeek();
    Q_INVOKABLE                 void     markEpisodeAsSeen(int serieId, int seasonId, int episodeId);
    Q_INVOKABLE                 void     markSeasonAsSeen(int serieId, int seasonId);
    Q_INVOKABLE                 void     updateFollowedShows();
    Q_INVOKABLE                 void     searchForShow(QString showName);
    Q_INVOKABLE                 void     addShowToFollow(int serieId);
    Q_INVOKABLE                 void     removeShowFromSearchResult(int showId);
    Q_INVOKABLE                 void     removeShowFromFollowedModel(int showId);
    Q_INVOKABLE                 void     refreshSickbeardShow(int showId);
    Q_INVOKABLE                 void     retrieveSickBeardShows();
    Q_INVOKABLE                 void     saveSickBeardConfig();
    void                                 addShowToSickBeard(QString showId);
    void                                 updateShowSeasonFromSickBeard(int showId, int seasonId);
    void                                 updateOnlineUpdatedShows();

    QString                              pluginState() const;
    void                                 setPluginState(const QString& value);

    QString                              sickBeardApi() const;
    QString                              sickBeardUrl() const;
    bool                                 addToSickBeard() const;
    void                                 setSickBeardUrl(const QString &sickBeardUrl);
    void                                 setSickBeardApi(const QString &sickBeardApi);
    void                                 setAddToSickBeard(bool value);

private:
    Models::SubListedListModel* followedSeriesModel;
    Models::SubListedListModel* searchSeriesModel;
    Models::SubListedListModel* showsOfTheWeek;
    QString                     m_sickBeardUrl;
    QString                     m_sickBeardApiKey;
    QString                     m_pluginState;
    bool                        m_addToSickBeard;
    bool                        m_synchingWithSB;

    QHash<int, void (SeriesPlugin::*)(QNetworkReply*, void*)> webServicesCallBacks;
    QHash<int, void (SeriesPlugin::*)(QList<QSqlRecord>, void*)> databaseCallBacks;

    void                        updateShowSummary(SerieSubListedItem *show);
    SerieSubListedItem *        parseShow(const QJsonObject& showObj);
    SeasonSubListedItem*        parseShowSeason(const QJsonObject& seasonObj);
    EpisodeListItem    *        parseShowEpisode(const QJsonObject& episodeObj);

    // WEBSERVICES CALLBACK
    void                        searchForShowCallBack(QNetworkReply *reply, void *data);
    void                        getShowSummaryCallBack(QNetworkReply *reply, void *data);
    void                        updateShowSummaryCallBack(QNetworkReply *reply, void *data);
    void                        retrieveSickBeardShowsCallBack(QNetworkReply *reply, void *data);
    void                        updateSickbeardShowCallBack(QNetworkReply *reply, void *data);
    void                        updateShowSeasonFromSickNeardCallBack(QNetworkReply *reply, void *data);
    void                        addShowToSickBeardCallBack(QNetworkReply *reply, void *data);
    void                        updateOnlineUpdatedShowsCallBack(QNetworkReply *reply, void *data);

    // DATABASE
    void                        retrieveSickBeardConfig();
    void                        addShowToDatabase(SerieSubListedItem *show);
    void                        addSeasonToDatabase(SeasonSubListedItem *season, const QString &showSlug);
    void                        addEpisodeToDatabase(EpisodeListItem *episode, const QString &showSlug, int season);

    void                        updateShowInDatabase(SerieSubListedItem *show);
    void                        updateSeasonInDatabase(SeasonSubListedItem *season, int serieId);
    void                        updateEpisodeInDatabase(EpisodeListItem *episode, int serieId, int season);

    void                        removeShowFromDatabase(const QString &showSlug);

    void                        retrieveShowsFromDababase();
    void                        retrieveShowSeasonsFromDatabase(int showDbId, SerieSubListedItem *show);
    void                        retrieveShowEpisodesFromDatabase(int showDbId, int seasonDbId, SeasonSubListedItem* season);

    // DATABASE CALLBACK
    void                        retrieveShowsFromDatabaseCallBack(QList<QSqlRecord> result, void *data);
    void                        retrieveSeasonsForShowDatabaseCallBack(QList<QSqlRecord> result, void *data);
    void                        retrieveEpisodesForShowSeasonDatabaseCallBack(QList<QSqlRecord> result, void *data);
    void                        genericDatabaseCallBack(QList<QSqlRecord> result, void *data);
    void                        retrieveSickBeardConfigCallBack(QList<QSqlRecord> result, void *data);

signals :

    void                        pluginStateChanged();
    void                        sickBeardUrlChanged();
    void                        sickBeardApiChanged();
    void                        addToSickBeardChanged();
};

#endif // SERIESPLUGIN_H

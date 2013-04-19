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

#include "SeriesPlugin.h"

SeriesPlugin::SeriesPlugin() : PluginBase()
{
    // WEBSERVICES CALLBACKS HASH
    this->webServicesCallBacks[SEARCH_SHOW_REQUEST] = &SeriesPlugin::searchForShowCallBack;
    this->webServicesCallBacks[GET_SHOW_SUMMARY] = &SeriesPlugin::getShowSummaryCallBack;
    this->webServicesCallBacks[UPDATE_SHOW_SUMMARY] = &SeriesPlugin::updateShowSummaryCallBack;
    this->webServicesCallBacks[GET_SICKBEARD_SHOWS] = &SeriesPlugin::retrieveSickBeardShowsCallBack;
    this->webServicesCallBacks[UPDATE_SICKBEARD_SHOW] = &SeriesPlugin::updateSickbeardShowCallBack;
    this->webServicesCallBacks[UPDATE_SEASON_EPISODES_SICKBEARD] = &SeriesPlugin::updateShowSeasonFromSickNeardCallBack;
    this->webServicesCallBacks[ADD_SHOW_TO_SICKBEARD] = &SeriesPlugin::addShowToSickBeardCallBack;
    this->webServicesCallBacks[UPDATE_UPDATED_SHOW] = &SeriesPlugin::updateOnlineUpdatedShowsCallBack;
    this->webServicesCallBacks[SEARCH_SICKBEARD_SHOW] = &SeriesPlugin::searchSickBeardEpisodeCallBack;
    // DATABASE CALLBACKS HASH
    this->databaseCallBacks[RETRIEVE_SHOWS] = &SeriesPlugin::retrieveShowsFromDatabaseCallBack;
    this->databaseCallBacks[RETRIEVE_SEASONS_FOR_SHOW] = &SeriesPlugin::retrieveSeasonsForShowDatabaseCallBack;
    this->databaseCallBacks[RETRIEVE_EPISODES_FOR_SHOW_SEASON] = &SeriesPlugin::retrieveEpisodesForShowSeasonDatabaseCallBack;
    this->databaseCallBacks[GENERIC_REQUEST] = &SeriesPlugin::genericDatabaseCallBack;
    this->databaseCallBacks[RETRIEVE_SICKBEARD_CONFIG] = &SeriesPlugin::retrieveSickBeardConfigCallBack;
    // CREATE SERIES MODEL
    this->followedSeriesModel = new Models::SubListedListModel(new SerieSubListedItem());
    // THIS MODEL IS USED WHEN SEARCHING FOR SHOWS, SEASONS AND EPISODES SUBMODELS ARE NOT FILLED
    this->searchSeriesModel = new Models::SubListedListModel(new SerieSubListedItem());
    // MODELS CONTAINING SHOWS TO APPEAR THIS WEEK
    this->showsOfTheWeek = new Models::SubListedListModel(new SerieSubListedItem());
}
// ALL the function should be implemented

int SeriesPlugin::getPluginId()
{
    return PLUGIN_ID;
}

void SeriesPlugin::initPlugin()
{
    this->m_synchingWithSB = false;
    this->retrieveShowsFromDababase();
    this->retrieveSickBeardConfig();
    this->setPluginState("shows_view");
    this->currentWebQueriesCount = 0;
    QObject::connect(this, SIGNAL(executeHttpRequest(QNetworkRequest,int,QHttpMultiPart*,QObject*,int,void*)),
                     this, SLOT(webQueryEmitted()));
}

void SeriesPlugin::clearPluginBeforeRemoval()
{
}

QString SeriesPlugin::getPluginName()
{
    return QString("SeriesPlugin");
}

QString SeriesPlugin::getPluginDescription()
{
    return QString("SeriesPlugin.qml");
}

Plugins::PluginBase* SeriesPlugin::getPluginBase()
{
    return this;
}

QString SeriesPlugin::getRoomPluginQmlFile() const
{
    return QString("SeriesPlugin.qml");
}

QString SeriesPlugin::getMenuPluginQmlFile() const
{
    return QString("Menu.qml");
}

void SeriesPlugin::onIdleFocusState()
{
    qDebug() << "SeriesPlugin idling";
}

void SeriesPlugin::onSelectedFocusState()
{
    qDebug() << "SeriesPlugin Selected";
}

void SeriesPlugin::onFocusedFocusState()
{
    qDebug() << "SeriesPlugin Focused";
    this->updateOnlineUpdatedShows();
}

Plugins::PluginBase* SeriesPlugin::createNewInstance()
{
    return new SeriesPlugin();
}

void    SeriesPlugin::receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, void *data)
{
    qDebug() << "Received DATABASE CallBack";
    (this->*this->databaseCallBacks[id])(result, data);
}

void    SeriesPlugin::receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data)
{
    qDebug() << "Received WebService CallBack " << this->currentWebQueriesCount;
    this->currentWebQueriesCount--;
    (this->*this->webServicesCallBacks[id])(reply, data);
    emit synchingChanged();
}

// INVOKABLE AND UTILITY METHODS

QObject    *SeriesPlugin::getFollowedSeriesModel() const
{
    return this->followedSeriesModel;
}

QObject *SeriesPlugin::getSeasonsModelFromSerieId(int serieId) const
{
    SerieSubListedItem *serie = (SerieSubListedItem *)this->followedSeriesModel->find(serieId);
    if (serie)
        return serie->submodel();
    return NULL;
}

QObject *SeriesPlugin::getEpisodesFromSeasonAndShowId(int serieId, int seasonId) const
{
    SerieSubListedItem *serie = (SerieSubListedItem *)this->followedSeriesModel->find(serieId);
    SeasonSubListedItem *season = NULL;
    if (serie != NULL && (season = (SeasonSubListedItem *)serie->submodel()->find(seasonId)) != NULL)
        return season->submodel();
    return NULL;
}

QObject *SeriesPlugin::getSearchSeriesModel() const
{
    return this->searchSeriesModel;
}

QObject *SeriesPlugin::getShowsToAppearInTheWeek()
{
    // TIME AT THE END OF THE WEEK
    QDateTime nowTime = QDateTime::currentDateTime();
    QDateTime endWeekTime = nowTime.addDays(7);
    this->showsOfTheWeek->clear();

    foreach (Models::ListItem *showItem, this->followedSeriesModel->toList())
    {
        SerieSubListedItem* show = reinterpret_cast<SerieSubListedItem*>(showItem);
        // BASED ON LAST SEASON ONLY
        SeasonSubListedItem *lastSeason = reinterpret_cast<SeasonSubListedItem *>(show->submodel()->toList().first());
        bool showIsThisWeek = false;
        foreach (Models::ListItem *episodeItem, lastSeason->submodel()->toList())
        {
            EpisodeListItem *episode = reinterpret_cast<EpisodeListItem*>(episodeItem);
            if (episode->data(EpisodeListItem::episodeAiring).toDateTime() > nowTime &&
                    episode->data(EpisodeListItem::episodeAiring).toDateTime() < endWeekTime)
            {
                showIsThisWeek = true;
                break;
            }
        }
        if (showIsThisWeek)
            this->showsOfTheWeek->appendRow(show);
    }
    return this->showsOfTheWeek;
}

void SeriesPlugin::markEpisodeAsSeen(int serieId, int seasonId, int episodeId, bool value)
{
    Models::SubListedListItem *serieItem = NULL;
    Models::SubListedListItem *seasonItem = NULL;
    if ((serieItem = reinterpret_cast<Models::SubListedListItem*>(this->followedSeriesModel->find(serieId))) != NULL &&
            serieItem->submodel() != NULL &&
            (seasonItem = reinterpret_cast<Models::SubListedListItem*>(serieItem->submodel()->find(seasonId))) != NULL &&
            seasonItem->submodel() != NULL)
    {
        EpisodeListItem *episodeItem = reinterpret_cast<EpisodeListItem *>(seasonItem->submodel()->find(episodeId));
        if (episodeItem != NULL)
        {
            episodeItem->setEpisodeSeen(value);
            this->updateEpisodeInDatabase(episodeItem, serieId, seasonId);
        }
    }
}

void SeriesPlugin::markSeasonAsSeen(int serieId, int seasonId)
{
    Models::SubListedListItem *serieItem = NULL;
    Models::SubListedListItem *seasonItem = NULL;
    if ((serieItem = reinterpret_cast<Models::SubListedListItem*>(this->followedSeriesModel->find(serieId))) != NULL &&
            serieItem->submodel() != NULL &&
            (seasonItem = reinterpret_cast<Models::SubListedListItem*>(serieItem->submodel()->find(seasonId))) != NULL &&
            seasonItem->submodel() != NULL)
    {
        foreach (Models::ListItem *episodeItem, seasonItem->submodel()->toList())
        {
            EpisodeListItem *episode = reinterpret_cast<EpisodeListItem *>(episodeItem);
            if (episode != NULL)
            {
                episode->setEpisodeSeen(true);
                this->updateEpisodeInDatabase(episode, serieId, seasonId);
            }
        }
    }
}

void SeriesPlugin::updateFollowedShows()
{
    foreach (Models::ListItem *showItem, this->followedSeriesModel->takeRows())
    {
        this->updateShowSummary(reinterpret_cast<SerieSubListedItem *>(showItem));
    }
}

void SeriesPlugin::updateShowSummary(SerieSubListedItem *show)
{
    PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl("http://api.trakt.tv/show/summary.json/"\
                                                           + QString(TRAKT_API_KEY)\
                                                           + "/" + show->data(SerieSubListedItem::slug).toString()\
                                                           + "/true")), UPDATE_SHOW_SUMMARY, (void *)show);
}

void SeriesPlugin::searchForShow(QString showName)
{
    this->searchSeriesModel->clear();
    PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl("http://api.trakt.tv/search/shows.json/"\
                                                           + QString(TRAKT_API_KEY)\
                                                           + "/" + showName.replace(" ", "-"))),
                                      SEARCH_SHOW_REQUEST);
}

void SeriesPlugin::addShowToFollow(int serieId)
{
    PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl("http://api.trakt.tv/show/summary.json/"\
                                                           + QString(TRAKT_API_KEY)\
                                                           + "/" + QString::number(serieId)
                                                           + "/true")), GET_SHOW_SUMMARY);
    if (!this->m_synchingWithSB && this->m_addToSickBeard)
        this->addShowToSickBeard(QString::number(serieId));
}

void SeriesPlugin::removeShowFromSearchResult(int showId)
{
    int idx = -1;
    if ((idx = this->searchSeriesModel->rowIndexFromId(showId)) != -1)
        this->searchSeriesModel->removeRow(idx);
}

void SeriesPlugin::removeShowFromFollowedModel(int showId)
{
    int idx = -1;
    SerieSubListedItem *showToRemove = reinterpret_cast<SerieSubListedItem *>(this->followedSeriesModel->find(showId));
    if (showToRemove != NULL && (idx = this->followedSeriesModel->getRowFromItem(showToRemove)) != -1)
    {
        this->removeShowFromDatabase(showToRemove->data(SerieSubListedItem::slug).toString());
        this->followedSeriesModel->removeRow(idx);
    }
}

void SeriesPlugin::refreshSickbeardShow(int showId)
{
    SerieSubListedItem *sbShow = reinterpret_cast<SerieSubListedItem *>(this->followedSeriesModel->find(showId));
    if (sbShow != NULL)
        Plugins::PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl(this->m_sickBeardUrl + "/api/" +
                                                                        this->m_sickBeardApiKey + "/?cmd=show&tvdbid="
                                                                        + QString::number(sbShow->id()))),
                                                   UPDATE_SICKBEARD_SHOW, (void *)sbShow);
}

void SeriesPlugin::retrieveSickBeardShows()
{
    Plugins::PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl(this->m_sickBeardUrl + "/api/" +
                                                                    this->m_sickBeardApiKey + "/?cmd=shows")),
                                               GET_SICKBEARD_SHOWS);
}

void SeriesPlugin::searchSickBeardEpisode(int serieId, int seasonId, int episodeId)
{
    Plugins::PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl(this->m_sickBeardUrl + "/api/" +
                                                                    this->m_sickBeardApiKey +
                                                                    QString("/?cmd=episode.search&tvdbid=%1&season=%2&episode=%3")
                                                                    .arg(QString::number(serieId),
                                                                         QString::number(seasonId),
                                                                         QString::number(episodeId)))),
                                               SEARCH_SICKBEARD_SHOW);
}

void SeriesPlugin::addShowToSickBeard(QString showId)
{
    qDebug() << this->m_sickBeardUrl + "/api/" +
                this->m_sickBeardApiKey + "/?cmd=show.addnew&tvdbid="
                + showId;
    Plugins::PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl(this->m_sickBeardUrl + "/api/" +
                                                                    this->m_sickBeardApiKey + "/?cmd=show.addnew&tvdbid="
                                                                    + showId)),
                                               ADD_SHOW_TO_SICKBEARD);
}

void SeriesPlugin::updateShowSeasonFromSickBeard(int showId, int seasonId)
{
    Plugins::PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl(this->m_sickBeardUrl + "/api/" +
                                                                    this->m_sickBeardApiKey + "/?cmd=show.seasons&tvdbid="
                                                                    + QString::number(showId)
                                                                    + "&season="
                                                                    + QString::number(seasonId))),
                                               UPDATE_SEASON_EPISODES_SICKBEARD, (void *)new QPoint(showId, seasonId));
}

void SeriesPlugin::updateOnlineUpdatedShows()
{
    Plugins::PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl("http://api.trakt.tv/shows/updated.json/"\
                                                                    + QString(TRAKT_API_KEY)
                                                                    + "/" + QString::number(QDateTime::currentDateTime().addDays(-7).toTime_t())))
                                               , UPDATE_UPDATED_SHOW);
}


void SeriesPlugin::saveSickBeardConfig()
{
    QString saveSBConfig = QString("UPDATE config SET sickbeard_url = '%1', sickbeard_api_key = '%2', add_to_sickbeard = %3;")
            .arg(Utils::escapeSqlQuery(this->sickBeardUrl()),
                 Utils::escapeSqlQuery(this->sickBeardApi()),
                 this->m_addToSickBeard ? "1" : "0");
    Plugins::PluginBase::executeSQLQuery(saveSBConfig, this, GENERIC_REQUEST, DATABASE_NAME);
}

// SERIESPLUGIN PROPERTIES

QString SeriesPlugin::pluginState() const
{
    return this->m_pluginState;
}

void SeriesPlugin::setPluginState(const QString& value)
{
    this->m_pluginState = value;
    emit pluginStateChanged();
}

QString SeriesPlugin::sickBeardApi() const
{
    return this->m_sickBeardApiKey;
}

QString SeriesPlugin::sickBeardUrl() const
{
    return this->m_sickBeardUrl;
}

bool SeriesPlugin::addToSickBeard() const
{
    return this->m_addToSickBeard;
}

void SeriesPlugin::setSickBeardUrl(const QString &sickBeardUrl)
{
    this->m_sickBeardUrl = sickBeardUrl;
    if (this->m_sickBeardUrl.endsWith("/"))
        this->m_sickBeardUrl.chop(1);
    emit sickBeardUrlChanged();
}

void SeriesPlugin::setSickBeardApi(const QString &sickBeardApi)
{
    this->m_sickBeardApiKey = sickBeardApi;
    emit sickBeardApiChanged();
}

void SeriesPlugin::setAddToSickBeard(bool value)
{
    this->m_addToSickBeard = value;
    emit addToSickBeardChanged();
}

bool SeriesPlugin::getSynching() const
{
    return (this->currentWebQueriesCount != 0);
}

// JSON PARSING OF TRAKTV SHOWS

SerieSubListedItem *SeriesPlugin::parseShow(const QJsonObject& showObj)
{
    if (!showObj.isEmpty())
    {
        QJsonObject imageObj = showObj.value("images").toObject();
        int tvDbId = 0;
        if (showObj.value("tvdb_id").isDouble())
            tvDbId = showObj.value("tvdb_id").toDouble();
        else
            tvDbId = showObj.value("tvdb_id").toString().toInt();

        SerieSubListedItem *showItem =  new SerieSubListedItem(tvDbId,
                                                               showObj.value("url").toString().replace("http://trakt.tv/show/", ""),
                                                               showObj.value("title").toString(),
                                                               imageObj.value("poster").toString(),
                                                               showObj.value("overview").toString(),
                                                               QString::number(showObj.value("year").toDouble()),
                                                               showObj.value("network").toString(),
                                                               QDateTime::fromTime_t(showObj.value("last_updated").toDouble()),
                                                               showObj.value("air_day").toString(),
                                                               showObj.value("air_time").toString());
        QJsonArray seasonsArray = showObj.value("seasons").toArray();
        foreach (QJsonValue seasonObj, seasonsArray)
        {
            SeasonSubListedItem *seasonItem = parseShowSeason(seasonObj.toObject());
            if (seasonItem != NULL)
                showItem->submodel()->appendRow(seasonItem);
        }
        return showItem;
    }
    return NULL;
}

SeasonSubListedItem *SeriesPlugin::parseShowSeason(const QJsonObject& seasonObj)
{
    if (!seasonObj.isEmpty())
    {
        QJsonObject image = seasonObj.value("images").toObject();
        QJsonArray episodesArray = seasonObj.value("episodes").toArray();
        SeasonSubListedItem *season = new SeasonSubListedItem(static_cast<int>(seasonObj.value("season").toDouble()),
                                                              episodesArray.count(),
                                                              image.value("poster").toString());
        foreach (QJsonValue episodeObj, episodesArray)
        {
            EpisodeListItem *episodeItem = parseShowEpisode(episodeObj.toObject());
            if (episodeItem != NULL)
                season->submodel()->appendRow(episodeItem);
        }
        return season;
    }
    return NULL;
}

EpisodeListItem *SeriesPlugin::parseShowEpisode(const QJsonObject& episodeObj)
{
    if (!episodeObj.isEmpty())
    {
        QJsonObject image = episodeObj.value("images").toObject();

        return new EpisodeListItem(static_cast<int>(episodeObj.value("episode").toDouble()),
                                   static_cast<int>(episodeObj.value("number").toDouble()),
                                   static_cast<int>(episodeObj.value("season").toDouble()),
                                   episodeObj.value("title").toString(),
                                   episodeObj.value("overview").toString(),
                                   image.value("screen").toString(),
                                   QDateTime::fromTime_t(episodeObj.value("first_aired").toDouble()));
    }
    return NULL;
}

// WEB SERVICES CALL BACKS
void SeriesPlugin::searchForShowCallBack(QNetworkReply *reply, void *data)
{
    Q_UNUSED(data)
    if (reply != NULL)
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        // DO NOT FORGET TO DELETE THE REPLY
        delete reply;
        if (!jsonDoc.isNull() && !jsonDoc.isEmpty() && jsonDoc.isArray())
        {
            QJsonArray showsResultArray = jsonDoc.array();
            foreach (QJsonValue showObj, showsResultArray)
            {
                SerieSubListedItem *showItem = parseShow(showObj.toObject());
                if (showItem != NULL && showItem->id() > 0)
                    this->searchSeriesModel->appendRow(showItem);
            }
        }
        else
            qDebug() << "An error occured when retrieving the JSON";
    }
}

void SeriesPlugin::getShowSummaryCallBack(QNetworkReply *reply, void *data)
{
    Q_UNUSED(data)
    if (reply != NULL)
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        // DO NOT FORGET TO DELETE THE REPLY
        delete reply;
        if (!jsonDoc.isNull() && !jsonDoc.isEmpty() && jsonDoc.isObject())
        {
            SerieSubListedItem *showItem = parseShow(jsonDoc.object());
            if (showItem != NULL && this->followedSeriesModel->find(showItem->id()) == NULL)
            {
                qDebug() << "Show Summary Callback";
                this->followedSeriesModel->appendRow(showItem);
                this->addShowToDatabase(showItem);
            }
        }
        else
            qDebug() << "An error occured when retrieving the JSON";
    }
}

void SeriesPlugin::fillMissingInfoFromPrevious(SerieSubListedItem *oldShow, SerieSubListedItem *updatedShow)
{
    if (oldShow != NULL && updatedShow != NULL)
    {
        updatedShow->setSerieOnSickBeard(oldShow->data(SerieSubListedItem::serieOnSickbeard).toBool());
        Models::SubListedListModel *oldSeasonModel = reinterpret_cast<Models::SubListedListModel*>(oldShow->submodel());
        Models::SubListedListModel *updatedSeasonModel = reinterpret_cast<Models::SubListedListModel*>(updatedShow->submodel());

        if (oldSeasonModel != NULL && updatedSeasonModel != NULL)
            foreach (Models::ListItem *oldSeasonItem, oldSeasonModel->toList())
            {
                Models::ListItem* updatedSeasonItem = updatedSeasonModel->find(oldSeasonItem->id());
                if (updatedSeasonItem != NULL)
                {
                    Models::ListModel *oldEpisodeModel = reinterpret_cast<Models::SubListedListItem*>(oldSeasonItem)->submodel();
                    Models::ListModel *updatedEpisodeModel = reinterpret_cast<Models::SubListedListItem*>(updatedSeasonItem)->submodel();
                    if (oldEpisodeModel != NULL && updatedEpisodeModel != NULL)
                        foreach (Models::ListItem* oldEpisodeItem, oldEpisodeModel->toList())
                        {
                            EpisodeListItem *oldEpisode = reinterpret_cast<EpisodeListItem*>(oldEpisodeItem);
                            EpisodeListItem *newEpisode = reinterpret_cast<EpisodeListItem*>(updatedEpisodeModel->find(oldEpisode->id()));
                            if (newEpisode == NULL)
                                continue;
                            newEpisode->setEpisodeSeen(oldEpisode->data(EpisodeListItem::episodeSeen).toBool());
                            newEpisode->setSickbeardStatus(oldEpisodeItem->data(EpisodeListItem::episodeSickbeardStatus).toString());
                        }
                }
            }
    }
}

void SeriesPlugin::updateShowSummaryCallBack(QNetworkReply *reply, void *data)
{
    if (reply != NULL && data != NULL)
    {
        SerieSubListedItem *oldShow = reinterpret_cast<SerieSubListedItem *>(data);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        // DO NOT FORGET TO DELETE THE REPLY
        delete reply;
        if (!jsonDoc.isNull() && !jsonDoc.isEmpty() && jsonDoc.isObject())
        {
            SerieSubListedItem *showItem = parseShow(jsonDoc.object());
            if (showItem != NULL)
            {
                // REPLACE OLDSHOW_ITEM BY SHOWITEM
                // RESTORE DATA FROM OLDSHOW THAT ARE NOT OBTAINED IN THE WEB STREAM
                this->fillMissingInfoFromPrevious(oldShow, showItem);
                delete oldShow;
                this->followedSeriesModel->appendRow(showItem);
                this->updateShowInDatabase(showItem);
            }
        }
        else
        {
            qDebug() << "An error occured when retrieving the JSON";
            // RESTORES THE OLD SHOW ITEM
            this->followedSeriesModel->appendRow(oldShow);
        }
    }
}

// SICKBEARD WEB CALLBACKS
void SeriesPlugin::retrieveSickBeardShowsCallBack(QNetworkReply *reply, void *data)
{
    Q_UNUSED(data)
    if (reply != NULL)
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        delete reply;
        if (!jsonDoc.isNull() && !jsonDoc.isEmpty() && jsonDoc.isObject())
        {
            QJsonObject mainObj = jsonDoc.object();
            if (mainObj.value("result").toString().compare("success") == 0)
            {
                QJsonObject showsArray = mainObj.value("data").toObject();
                // THAT WAY IN ADD SHOW, SHOWS ARE NOT ADDED TO SB
                this->m_synchingWithSB = true;
                foreach (QString key, showsArray.keys())
                {
                    if (this->followedSeriesModel->find(key.toInt()) == NULL)
                        this->addShowToFollow(key.toInt());
                    this->refreshSickbeardShow(key.toInt());
                }
                this->m_synchingWithSB = false;
            }
        }
        else
            qDebug() << "Failed to Retrieve SickBeardShows";
    }
}

void SeriesPlugin::updateSickbeardShowCallBack(QNetworkReply *reply, void *data)
{
    if (reply != NULL && data != NULL)
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        delete reply;
        if (!jsonDoc.isNull() && !jsonDoc.isEmpty() && jsonDoc.isObject())
        {
            QJsonObject mainObj = jsonDoc.object();
            if (mainObj.value("result").toString().compare("success") == 0)
            {
                QJsonObject dataObj = mainObj.take("data").toObject();
                if (!dataObj.isEmpty())
                {
                    SerieSubListedItem *sbShow = reinterpret_cast<SerieSubListedItem *>(data);
                    sbShow->setSerieOnSickBeard(true);
                    QJsonArray seasons = dataObj.take("season_list").toArray();
                    foreach (QJsonValue value, seasons)
                    {
                        if (sbShow->submodel()->find(value.toDouble()) != NULL)
                            this->updateShowSeasonFromSickBeard(sbShow->id(), value.toDouble());
                    }
                }
            }
        }
    }
}

void SeriesPlugin::updateShowSeasonFromSickNeardCallBack(QNetworkReply *reply, void *data)
{
    if (reply != NULL && data != NULL)
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        delete reply;
        if (!jsonDoc.isNull() && !jsonDoc.isEmpty() && jsonDoc.isObject())
        {
            QJsonObject mainObj = jsonDoc.object();
            if (mainObj.value("result").toString().compare("success") == 0)
            {
                QPoint *p = reinterpret_cast<QPoint*>(data);
                Models::ListModel *episodesModel = NULL;
                Models::SubListedListModel *seasonsModel = NULL;
                QJsonObject showsArray = mainObj.value("data").toObject();
                if ((seasonsModel = reinterpret_cast<Models::SubListedListModel*>
                     (this->followedSeriesModel->subModelFromId(p->x()))) != NULL &&
                        (episodesModel = reinterpret_cast<Models::ListModel*>(seasonsModel->subModelFromId(p->y()))) != NULL)
                {
                    foreach (QString key, showsArray.keys())
                    {
                        QJsonObject episodeObj = showsArray.take(key).toObject();
                        EpisodeListItem *episode = reinterpret_cast<EpisodeListItem*>(episodesModel->find(key.toInt()));
                        if (episode && !episodeObj.isEmpty())
                            episode->setSickbeardStatus(episodeObj.take("status").toString());
                        else
                            qDebug() << "Episode Not Found";
                    }
                    // UPDATE SHOW IN DB IF THIS IS THE WE HAVE DONE ALL THE SEASONS
                    if (p->y() == seasonsModel->toList().last()->id())
                        this->updateShowInDatabase(reinterpret_cast<SerieSubListedItem*>(this->followedSeriesModel->find(p->x())));
                }
                delete p;
            }
        }
    }
}

void SeriesPlugin::addShowToSickBeardCallBack(QNetworkReply *reply, void *data)
{
    Q_UNUSED(data)
    if (reply != NULL)
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        delete reply;
        if (!jsonDoc.isNull() && !jsonDoc.isEmpty() && jsonDoc.isObject())
        {
            QJsonObject mainObj = jsonDoc.object();
            if (mainObj.value("result").toString().compare("success") == 0)
                return;
        }
    }
    qDebug() << "Error adding show to Sickbeard";
}

void SeriesPlugin::updateOnlineUpdatedShowsCallBack(QNetworkReply *reply, void *data)
{
    Q_UNUSED(data)
    if (reply != NULL)
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        delete reply;
        if (!jsonDoc.isNull() && !jsonDoc.isEmpty() && jsonDoc.isObject())
        {
            QJsonObject mainObj = jsonDoc.object();
            QJsonArray  showsArray = mainObj.take("shows").toArray();
            foreach (QJsonValue value, showsArray)
            {
                QJsonObject showObj = value.toObject();
                if (!showObj.isEmpty())
                {
                    Models::ListItem *showItem = NULL;
                    if ((showItem = this->followedSeriesModel->find(showObj.value("tvdb_id").toDouble())) != NULL)
                    {
                        if (showItem->data(SerieSubListedItem::serieLastUpdate).toDateTime() <
                                QDateTime::fromTime_t(showObj.value("last_updated").toDouble()))
                        {
                            qDebug() << "Updating shows " << showItem->data(SerieSubListedItem::serieName).toString() << "Show " << showItem->data(SerieSubListedItem::serieLastUpdate).toDateTime() << "Stream "   << QDateTime::fromTime_t(showObj.value("last_updated").toDouble());
                            this->updateShowSummary(reinterpret_cast<SerieSubListedItem*>(
                                                        this->followedSeriesModel->takeRow(
                                                            this->followedSeriesModel->rowIndexFromId(showItem->id()))));
                        }
                    }
                }
            }
        }
    }
}

void SeriesPlugin::searchSickBeardEpisodeCallBack(QNetworkReply *reply, void *data)
{
    Q_UNUSED(reply)
    Q_UNUSED(data)
}

void SeriesPlugin::retrieveSickBeardConfig()
{
    QString sickbeardConfigRequest = "SELECT sickbeard_url, sickbeard_api_key, add_to_sickbeard FROM config WHERE id = 0;";
    emit executeSQLQuery(sickbeardConfigRequest, this, RETRIEVE_SICKBEARD_CONFIG, DATABASE_NAME);
}

// DATABASE

void SeriesPlugin::addShowToDatabase(SerieSubListedItem *show)
{
    if (show != NULL)
    {
        emit executeSQLQuery("BEGIN;", this, GENERIC_REQUEST, DATABASE_NAME);
        QString insertShowRequest = QString("INSERT OR REPLACE INTO show "
                                            "(serieTitle, serieSlug, serieImage,"
                                            " serieOverview, serieYear, serieNetwork, "
                                            "serieLastUpdate, serieAirDay, serieAirTime,"
                                            " serieTvDbId, serieSickBeard) VALUES ('%1', '%2', '%3', '%4','%5','%6',%7, '%8', '%9', %10, %11);")
                .arg(Utils::escapeSqlQuery(show->data(SerieSubListedItem::serieName).toString()),
                     Utils::escapeSqlQuery(show->data(SerieSubListedItem::slug).toString()),
                     Utils::escapeSqlQuery(show->data(SerieSubListedItem::imageUrl).toString()),
                     Utils::escapeSqlQuery(show->data(SerieSubListedItem::serieOverview).toString()),
                     Utils::escapeSqlQuery(show->data(SerieSubListedItem::serieYear).toString()),
                     Utils::escapeSqlQuery(show->data(SerieSubListedItem::serieNetwork).toString()),
                     QString::number(show->data(SerieSubListedItem::serieLastUpdate).toDateTime().toTime_t()),
                     Utils::escapeSqlQuery(show->data(SerieSubListedItem::serieAirDay).toString()),
                     Utils::escapeSqlQuery(show->data(SerieSubListedItem::serieAirTime).toString()))
                .arg(QString::number(show->data(SerieSubListedItem::serieTvdbId).toInt()),
                     show->data(SerieSubListedItem::serieOnSickbeard).toBool() ? "1" : "0");

        emit executeSQLQuery(insertShowRequest, this, GENERIC_REQUEST, DATABASE_NAME);
        foreach (Models::ListItem* season, show->submodel()->toList())
        {
            this->addSeasonToDatabase(reinterpret_cast<SeasonSubListedItem *>(season),
                                      show->data(SerieSubListedItem::slug).toString());
        }
        emit executeSQLQuery("COMMIT;", this, GENERIC_REQUEST, DATABASE_NAME);
    }
}

void SeriesPlugin::addSeasonToDatabase(SeasonSubListedItem *season, const QString &showSlug)
{
    if (season != NULL)
    {
        QString insertSeasonRequest = QString("INSERT OR REPLACE INTO seasons "
                                              "(showId, seasonNumber, seasonEpisodesCount, seasonImage) "
                                              "VALUES ((SELECT serieId FROM show WHERE serieSlug = '%1'), "
                                              " %2, %3, '%4');")
                .arg(Utils::escapeSqlQuery(showSlug),
                     QString::number(season->data(SeasonSubListedItem::seasonId).toInt()),
                     QString::number(season->data(SeasonSubListedItem::episodeCount).toInt()),
                     Utils::escapeSqlQuery(season->data(SeasonSubListedItem::imageUrl).toString()));

        emit executeSQLQuery(insertSeasonRequest, this, GENERIC_REQUEST, DATABASE_NAME);
        foreach (Models::ListItem* episode, season->submodel()->toList())
        {
            this->addEpisodeToDatabase(reinterpret_cast<EpisodeListItem *>(episode),
                                       showSlug,
                                       season->data(SeasonSubListedItem::seasonId).toInt());
        }
    }
}

void SeriesPlugin::addEpisodeToDatabase(EpisodeListItem *episode, const QString& showSlug, int season)
{
    if (episode != NULL)
    {
        QString getShowIdRequest = QString("(SELECT serieId FROM show WHERE serieSlug = '%1')")
                .arg(Utils::escapeSqlQuery(showSlug));
        QString getSeasonIdRequest = QString("(SELECT seasonId FROM seasons WHERE showId = %1 AND seasonNumber = %2)")
                .arg(getShowIdRequest,
                     QString::number(season));
        QString insertEpisodeRequest = QString("INSERT OR REPLACE INTO episodes (showId, seasonId, episodeTitle, "
                                               "episodeNumber, episodeSummary, episodeAiring, episodeSeen, episodeImage, episodeSickbeardStatus)"
                                               "VALUES (%1, %2, '%3', '%4', '%5', %6, %7, '%8', '%9');")
                .arg(getShowIdRequest,
                     getSeasonIdRequest,
                     Utils::escapeSqlQuery(episode->data(EpisodeListItem::episodeTitle).toString()),
                     episode->data(EpisodeListItem::episodeNumber).toString(),
                     Utils::escapeSqlQuery(episode->data(EpisodeListItem::episodeSummary).toString()),
                     QString::number(episode->data(EpisodeListItem::episodeAiring).toDateTime().toTime_t()),
                     episode->data(EpisodeListItem::episodeSeen).toBool() ? "1": "0",
                     Utils::escapeSqlQuery(episode->data(EpisodeListItem::imageUrl).toString()),
                     Utils::escapeSqlQuery(episode->data(EpisodeListItem::episodeSickbeardStatus).toString()));

        emit executeSQLQuery(insertEpisodeRequest, this, GENERIC_REQUEST, DATABASE_NAME);
    }
}

void SeriesPlugin::updateShowInDatabase(SerieSubListedItem *show)
{
    if (show != NULL)
    {
        emit executeSQLQuery("BEGIN;", this, GENERIC_REQUEST, DATABASE_NAME);
        QString updateShowRequest = QString("UPDATE show SET serieImage = '%1', serieSickBeard = %2, serieLastUpdate = %3 WHERE serieTvDbId = %4;")
                .arg(Utils::escapeSqlQuery(show->data(SerieSubListedItem::imageUrl).toString()),
                     show->data(SerieSubListedItem::serieOnSickbeard).toBool() ? "1" : "0",
                     QString::number(show->data(SerieSubListedItem::serieLastUpdate).toDateTime().toTime_t()),
                     QString::number(show->id()));
        emit executeSQLQuery(updateShowRequest, this, GENERIC_REQUEST, DATABASE_NAME);
        foreach (Models::ListItem* season, show->submodel()->toList())
        {
            this->updateSeasonInDatabase(reinterpret_cast<SeasonSubListedItem *>(season),
                                         show->id());
        }
        emit executeSQLQuery("COMMIT;", this, GENERIC_REQUEST, DATABASE_NAME);
    }
}

void SeriesPlugin::updateSeasonInDatabase(SeasonSubListedItem *season,int serieId)
{
    if (season != NULL)
    {
        QString updateSeasonRequest = QString("UPDATE seasons SET seasonEpisodesCount = %1, seasonImage = '%2'"
                                              " WHERE showId = (SELECT serieId FROM show WHERE serieTvDbId = %3)"
                                              " AND seasonNumber = %4 ;")
                .arg(QString::number(season->data(SeasonSubListedItem::episodeCount).toInt()),
                     Utils::escapeSqlQuery(season->data(SeasonSubListedItem::imageUrl).toString()),
                     QString::number(serieId),
                     QString::number(season->data(SeasonSubListedItem::seasonId).toInt()));
        emit (executeSQLQuery(updateSeasonRequest, this, GENERIC_REQUEST, DATABASE_NAME));
        foreach (Models::ListItem* episode, season->submodel()->toList())
        {
            this->updateEpisodeInDatabase(reinterpret_cast<EpisodeListItem *>(episode),
                                          serieId,
                                          season->data(SeasonSubListedItem::seasonId).toInt());
        }
    }
}

void SeriesPlugin::updateEpisodeInDatabase(EpisodeListItem *episode, int serieId, int season)
{
    if (episode != NULL)
    {
        QString getShowIdRequest = QString("(SELECT serieId FROM show WHERE serieTvDbId = %1)")
                .arg(QString::number(serieId));
        QString getSeasonIdRequest = QString("(SELECT seasonId FROM seasons WHERE showId = %1 AND seasonNumber = %2)")
                .arg(getShowIdRequest,
                     QString::number(season));
        QString updateEpisodeRequest = QString("UPDATE episodes SET episodeTitle = '%1', episodeSummary = '%2'"
                                               ", episodeAiring = %3, episodeImage = '%4', episodeSeen = %5"
                                               ", episodeSickbeardStatus = '%6'"
                                               " WHERE showId = %7 AND seasonId = %8 AND episodeNumber = %9;")
                .arg(Utils::escapeSqlQuery(episode->data(EpisodeListItem::episodeTitle).toString()),
                     Utils::escapeSqlQuery(episode->data(EpisodeListItem::episodeSummary).toString()),
                     QString::number(episode->data(EpisodeListItem::episodeAiring).toDateTime().toTime_t()),
                     Utils::escapeSqlQuery(episode->data(EpisodeListItem::imageUrl).toString()),
                     episode->data(EpisodeListItem::episodeSeen).toBool() ? "1" : "0",
                     Utils::escapeSqlQuery(episode->data(EpisodeListItem::episodeSickbeardStatus).toString()),
                     getShowIdRequest,
                     getSeasonIdRequest,
                     QString::number(episode->data(EpisodeListItem::episodeNumber).toInt()));
        emit executeSQLQuery(updateEpisodeRequest, this, GENERIC_REQUEST, DATABASE_NAME);
    }
}

void SeriesPlugin::removeShowFromDatabase(const QString &showSlug)
{
    QString removeEpisodesRequest = QString("DELETE FROM episodes WHERE showId = "
                                            "(SELECT serieId FROM show WHERE serieSlug = '%1');")
            .arg(Utils::escapeSqlQuery(showSlug));

    QString removeSeasonRequest = QString("DELETE FROM seasons WHERE showId = "
                                          "(SELECT serieId FROM show WHERE serieSlug = '%1');")
            .arg(Utils::escapeSqlQuery(showSlug));

    QString removeShowRequest = QString("DELETE FROM show WHERE serieSlug = '%1';")
            .arg(Utils::escapeSqlQuery(showSlug));

    emit executeSQLQuery(removeEpisodesRequest, this, GENERIC_REQUEST, DATABASE_NAME);
    emit executeSQLQuery(removeSeasonRequest, this, GENERIC_REQUEST, DATABASE_NAME);
    emit executeSQLQuery(removeShowRequest, this, GENERIC_REQUEST, DATABASE_NAME);
}

void SeriesPlugin::retrieveShowsFromDababase()
{
    QString retrieveShowsRequest = QString("SELECT serieId, serieTitle, serieSlug, serieImage, "
                                           "serieOverview, serieYear, serieNetwork, "
                                           "serieLastUpdate, serieAirDay, serieAirTime, serieTvDbId, serieSickBeard"
                                           " FROM show;");
    emit executeSQLQuery(retrieveShowsRequest, this, RETRIEVE_SHOWS, DATABASE_NAME);
}

void SeriesPlugin::retrieveShowSeasonsFromDatabase(int showDbId, SerieSubListedItem *show)
{
    QString retrieveSeasonsRequest = QString("SELECT showId, seasonId, seasonNumber, seasonEpisodesCount, "
                                             "seasonImage FROM seasons WHERE showId = %1;")
            .arg(QString::number(showDbId));
    emit executeSQLQuery(retrieveSeasonsRequest, this, RETRIEVE_SEASONS_FOR_SHOW, DATABASE_NAME, (void *)show);
}

void SeriesPlugin::retrieveShowEpisodesFromDatabase(int showDbId, int seasonDbId, SeasonSubListedItem *season)
{
    QString retrieveEpisodesRequest = QString("SELECT episodeTitle, episodeNumber, episodeSummary, "
                                              "episodeAiring, episodeSeen, episodeImage, episodeSickbeardStatus FROM episodes "
                                              "WHERE seasonId = %1 AND showId = %2;")
            .arg(QString::number(seasonDbId),
                 QString::number(showDbId));
    emit executeSQLQuery(retrieveEpisodesRequest, this, RETRIEVE_EPISODES_FOR_SHOW_SEASON, DATABASE_NAME, (void *)season);
}

// DATABASE CALLBACKS

void SeriesPlugin::retrieveShowsFromDatabaseCallBack(QList<QSqlRecord> result, void *data)
{
    Q_UNUSED(data)
    if (result.size() > 1)
    {
        result.pop_front();
        foreach (QSqlRecord record, result)
        {
            int showId = record.value(0).toInt();
            SerieSubListedItem *show = new SerieSubListedItem(record.value(10).toInt(),
                                                              record.value(2).toString(),
                                                              record.value(1).toString(),
                                                              record.value(3).toString(),
                                                              record.value(4).toString(),
                                                              record.value(5).toString(),
                                                              record.value(6).toString(),
                                                              QDateTime::fromTime_t(record.value(7).toDouble()),
                                                              record.value(8).toString(),
                                                              record.value(9).toString(),
                                                              record.value(11).toBool());
            this->retrieveShowSeasonsFromDatabase(showId, show);
            this->followedSeriesModel->appendRow(show);
        }
    }
}

void SeriesPlugin::retrieveSeasonsForShowDatabaseCallBack(QList<QSqlRecord> result, void *data)
{
    if (result.size() > 1 && data != NULL)
    {
        result.pop_front();
        SerieSubListedItem *show = reinterpret_cast<SerieSubListedItem*>(data);
        foreach (QSqlRecord record, result)
        {
            int showId = record.value(0).toInt();
            int seasonId = record.value(1).toInt();
            SeasonSubListedItem *season = new SeasonSubListedItem(record.value(2).toInt(),
                                                                  record.value(3).toInt(),
                                                                  record.value(4).toString());
            this->retrieveShowEpisodesFromDatabase(showId, seasonId, season);
            show->submodel()->appendRow(season);
        }
    }
}

void SeriesPlugin::retrieveEpisodesForShowSeasonDatabaseCallBack(QList<QSqlRecord> result, void *data)
{
    if (result.size() > 1 && data != NULL)
    {
        result.pop_front();
        SeasonSubListedItem *season = reinterpret_cast<SeasonSubListedItem *>(data);
        foreach (QSqlRecord record, result)
        {
            season->submodel()->appendRow(new EpisodeListItem(record.value(1).toInt(),
                                                              record.value(1).toInt(),
                                                              season->data(SeasonSubListedItem::seasonId).toInt(),
                                                              record.value(0).toString(),
                                                              record.value(2).toString(),
                                                              record.value(5).toString(),
                                                              QDateTime::fromTime_t(record.value(3).toInt()),
                                                              record.value(4).toBool(),
                                                              record.value(6).toString()));
        }
    }
}

void SeriesPlugin::genericDatabaseCallBack(QList<QSqlRecord> result, void *data)
{
    Q_UNUSED(result)
    Q_UNUSED(data)
}

void SeriesPlugin::retrieveSickBeardConfigCallBack(QList<QSqlRecord> result, void *data)
{
    Q_UNUSED(data)
    if (result.size() == 2)
    {
        result.pop_front();
        this->setSickBeardUrl(result.first().value(0).toString());
        this->setSickBeardApi(result.first().value(1).toString());
        this->setAddToSickBeard(result.first().value(2).toBool());
    }
}

void SeriesPlugin::webQueryEmitted()
{
    this->currentWebQueriesCount++;
    emit synchingChanged();
}





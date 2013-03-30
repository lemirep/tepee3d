#include "SeriesPlugin.h"

SeriesPlugin::SeriesPlugin() : PluginBase()
{
    // WEBSERVICES CALLBACKS HASH
    this->webServicesCallBacks[SEARCH_SHOW_REQUEST] = &SeriesPlugin::searchForShowCallBack;
    this->webServicesCallBacks[SEARCH_EPISODE_REQUEST] = &SeriesPlugin::searchForEpisodeCallBack;
    this->webServicesCallBacks[GET_SHOW_SUMMARY] = &SeriesPlugin::getShowSummaryCallBack;
    // DATABASE CALLBACKS HASH
    this->databaseCallBacks[RETRIEVE_SHOWS] = &SeriesPlugin::retrieveShowsFromDatabaseCallBack;
    this->databaseCallBacks[RETRIEVE_SEASONS_FOR_SHOW] = &SeriesPlugin::retrieveSeasonsForShowDatabaseCallBack;
    this->databaseCallBacks[RETRIEVE_EPISODES_FOR_SHOW_SEASON] = &SeriesPlugin::retrieveEpisodesForShowSeasonDatabaseCallBack;
    this->databaseCallBacks[CHECK_IF_DATABASE_FORMAT_EXISTS] = &SeriesPlugin::checkIfDatabaseSchemaExists;
    this->databaseCallBacks[GENERIC_REQUEST] = &SeriesPlugin::genericDatabaseCallBack;
    // CREATE SERIES MODEL
    this->followedSeriesModel = new Models::SubListedListModel(new SerieSubListedItem("", "", "", ""));
    // THIS MODEL IS USED WHEN SEARCHING FOR SHOWS, SEASONS AND EPISODES SUBMODELS ARE NOT FILLED
    this->searchSeriesModel = new Models::SubListedListModel(new SerieSubListedItem("", "", "", ""));
}
// ALL the function should be implemented

int SeriesPlugin::getPluginId()
{
    return PLUGIN_ID;
}

void SeriesPlugin::initPlugin()
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

Plugins::PluginBase* SeriesPlugin::createNewInstance()
{
    return new SeriesPlugin();
}

void    SeriesPlugin::receiveResultFromSQLQuery(QList<QSqlRecord> result, int id, void *data)
{
    qDebug() << "Received DATABASE CallBack";
    (this->*this->databaseCallBacks[id])(result);
}

void    SeriesPlugin::receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data)
{
    qDebug() << "Received WebService CallBack";
    (this->*this->webServicesCallBacks[id])(reply, data);
}

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



void SeriesPlugin::searchForShow(QString showName)
{
    this->searchSeriesModel->clear();
    PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl("http://api.trakt.tv/search/shows.json/"\
                                                           + QString(TRAKT_API_KEY)\
                                                           + "/" + showName.replace(" ", "-"))),
                                      SEARCH_SHOW_REQUEST);
}

void SeriesPlugin::addShowToFollow(QString slug)
{
    qDebug() << "SLug " << slug;
    PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl("http://api.trakt.tv/show/summary.json/"\
                                                           + QString(TRAKT_API_KEY)\
                                                           + "/" + slug\
                                                           + "/true")), GET_SHOW_SUMMARY);
}

void SeriesPlugin::searchForEpisode(QString episodeName)
{
    PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl("http://api.trakt.tv/search/episodes.json/"\
                                                           + QString(TRAKT_API_KEY) + "/"\
                                                           + episodeName)),
                                      SEARCH_EPISODE_REQUEST);
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
    if ((idx = this->followedSeriesModel->rowIndexFromId(showId)) != -1)
        this->followedSeriesModel->removeRow(idx);
}

SerieSubListedItem *SeriesPlugin::parseShow(const QJsonObject& showObj)
{
    if (!showObj.isEmpty())
    {
        QJsonObject imageObj = showObj.value("images").toObject();
        SerieSubListedItem *showItem =  new SerieSubListedItem(showObj.value("url").toString().replace("http://trakt.tv/show/", ""),
                                                               showObj.value("imdb_id").toString(),
                                                               showObj.value("title").toString(),
                                                               imageObj.value("poster").toString());
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
        SeasonSubListedItem *season = new SeasonSubListedItem(static_cast<int>(seasonObj.value("season").toDouble()),
                                                              static_cast<int>(seasonObj.value("episodes").toDouble()),
                                                              image.value("poster").toString());
        QJsonArray episodesArray = seasonObj.value("episodes").toArray();
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
    if (reply != NULL)
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        // DO NOT FORGET TO DELETE THE REPLY
        delete reply;
        qDebug() << "searchShowCallBack";
        if (!jsonDoc.isNull() && !jsonDoc.isEmpty() && jsonDoc.isArray())
        {
            QJsonArray showsResultArray = jsonDoc.array();
            foreach (QJsonValue showObj, showsResultArray)
            {
                SerieSubListedItem *showItem = parseShow(showObj.toObject());
                if (showItem != NULL)
                    this->searchSeriesModel->appendRow(showItem);
            }
        }
        else
            qDebug() << "An error occured when retrieving the JSON";
    }
}

void SeriesPlugin::getShowSummaryCallBack(QNetworkReply *reply, void *data)
{
    if (reply != NULL)
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        // DO NOT FORGET TO DELETE THE REPLY
        delete reply;
        qDebug() << "getShowSummary CallBack";
        if (!jsonDoc.isNull() && !jsonDoc.isEmpty() && jsonDoc.isObject())
        {
            SerieSubListedItem *showItem = parseShow(jsonDoc.object());
            if (showItem != NULL)
                this->followedSeriesModel->appendRow(showItem);
        }
        else
            qDebug() << "An error occured when retrieving the JSON";
    }
}

void SeriesPlugin::searchForEpisodeCallBack(QNetworkReply *reply, void *data)
{
}



// DATABASE CALLBACKS

void SeriesPlugin::retrieveShowsFromDatabaseCallBack(QList<QSqlRecord> result)
{
}

void SeriesPlugin::retrieveSeasonsForShowDatabaseCallBack(QList<QSqlRecord> result)
{
}

void SeriesPlugin::retrieveEpisodesForShowSeasonDatabaseCallBack(QList<QSqlRecord> result)
{
}

void SeriesPlugin::checkIfDatabaseSchemaExists(QList<QSqlRecord> result)
{
}

void SeriesPlugin::genericDatabaseCallBack(QList<QSqlRecord> result)
{
}



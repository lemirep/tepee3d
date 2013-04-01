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
    this->followedSeriesModel = new Models::SubListedListModel(new SerieSubListedItem("", "", ""));
    // THIS MODEL IS USED WHEN SEARCHING FOR SHOWS, SEASONS AND EPISODES SUBMODELS ARE NOT FILLED
    this->searchSeriesModel = new Models::SubListedListModel(new SerieSubListedItem("", "", ""));
}
// ALL the function should be implemented

int SeriesPlugin::getPluginId()
{
    return PLUGIN_ID;
}

void SeriesPlugin::initPlugin()
{
    this->retrieveShowsFromDababase();
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
    (this->*this->databaseCallBacks[id])(result, data);
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
            {
                this->followedSeriesModel->appendRow(showItem);
                this->addShowToDatabase(showItem);
            }
        }
        else
            qDebug() << "An error occured when retrieving the JSON";
    }
}

void SeriesPlugin::searchForEpisodeCallBack(QNetworkReply *reply, void *data)
{
}

// DATABASE

void SeriesPlugin::addShowToDatabase(SerieSubListedItem *show)
{
    if (show != NULL)
    {
        QString insertShowRequest = "INSERT INTO show (serieTitle, serieSlug, serieImage) VALUES (\"";
        insertShowRequest += show->data(SerieSubListedItem::serieName).toString();
        insertShowRequest += "\", \"";
        insertShowRequest +=  show->data(SerieSubListedItem::slug).toString();
        insertShowRequest += "\", \"";
        insertShowRequest +=  show->data(SerieSubListedItem::imageUrl).toString();
        insertShowRequest += "\");";

        emit executeSQLQuery(insertShowRequest, this, GENERIC_REQUEST, DATABASE_NAME);
        foreach (Models::ListItem* season, show->submodel()->toList())
        {
            this->addSeasonToDatabase(reinterpret_cast<SeasonSubListedItem *>(season),
                                      show->data(SerieSubListedItem::slug).toString());
        }
    }
}

void SeriesPlugin::addSeasonToDatabase(SeasonSubListedItem *season, const QString &showSlug)
{
    if (season != NULL)
    {
        QString insertSeasonRequest = "INSERT INTO seasons (showId, seasonNumber, seasonEpisodesCount, seasonImage) VALUES (";
        insertSeasonRequest += "(SELECT serieId FROM show WHERE serieSlug = \"";
        insertSeasonRequest += showSlug;
        insertSeasonRequest += "\"), ";
        insertSeasonRequest += QString::number(season->data(SeasonSubListedItem::seasonId).toInt());
        insertSeasonRequest += ", ";
        insertSeasonRequest += QString::number(season->data(SeasonSubListedItem::episodeCount).toInt());
        insertSeasonRequest += ", \"";
        insertSeasonRequest += season->data(SeasonSubListedItem::imageUrl).toString();
        insertSeasonRequest += "\");";

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
        QString insertEpisodeRequest = "INSERT INTO episodes (showId, seasonId, episodeTitle, ";
        insertEpisodeRequest += "episodeNumber, episodeSummary, episodeAiring, episodeSeen, episodeImage) VALUES (";
        insertEpisodeRequest += "(SELECT serieId FROM show WHERE serieSlug = \"";
        insertEpisodeRequest += showSlug;
        insertEpisodeRequest += "\"), ";
        insertEpisodeRequest += "(SELECT seasonId FROM seasons WHERE showId = ";
        insertEpisodeRequest += "(SELECT serieId FROM show WHERE serieSlug = \"";
        insertEpisodeRequest += showSlug;
        insertEpisodeRequest += "\") AND seasonNumber = ";
        insertEpisodeRequest += QString::number(season);
        insertEpisodeRequest += "), \"";
        insertEpisodeRequest += episode->data(EpisodeListItem::episodeTitle).toString();
        insertEpisodeRequest += "\", ";
        insertEpisodeRequest += episode->data(EpisodeListItem::episodeNumber).toString();
        insertEpisodeRequest += ", \"";
        insertEpisodeRequest += episode->data(EpisodeListItem::episodeSummary).toString();
        insertEpisodeRequest += "\", ";
        insertEpisodeRequest += QString::number(episode->data(EpisodeListItem::episodeAiring).toDateTime().toTime_t());
        insertEpisodeRequest += ", ";
        insertEpisodeRequest += episode->data(EpisodeListItem::episodeSeen).toBool() ? "1": "0";
        insertEpisodeRequest += ", \"";
        insertEpisodeRequest += episode->data(EpisodeListItem::imageUrl).toString();
        insertEpisodeRequest += "\");";
        emit executeSQLQuery(insertEpisodeRequest, this, GENERIC_REQUEST, DATABASE_NAME);
    }
}

void SeriesPlugin::retrieveShowsFromDababase()
{
    QString retrieveShowsRequest = "SELECT serieId, serieTitle, serieSlug, serieImage FROM show;";
    emit executeSQLQuery(retrieveShowsRequest, this, RETRIEVE_SHOWS, DATABASE_NAME);
}

void SeriesPlugin::retrieveShowSeasonsFromDatabase(int showDbId, SerieSubListedItem *show)
{
    QString retrieveSeasonsRequest = "SELECT showId, seasonId, seasonNumber, seasonEpisodesCount, seasonImage ";
    retrieveSeasonsRequest += "FROM seasons WHERE showId = ";
    retrieveSeasonsRequest += QString::number(showDbId);
    retrieveSeasonsRequest += ";";
    emit executeSQLQuery(retrieveSeasonsRequest, this, RETRIEVE_SEASONS_FOR_SHOW, DATABASE_NAME, (void *)show);
}

void SeriesPlugin::retrieveShowEpisodesFromDatabase(int showDbId, int seasonDbId, SeasonSubListedItem *season)
{
    QString retrieveEpisodesRequest = "SELECT episodeTitle, episodeNumber, episodeSummary, ";
    retrieveEpisodesRequest += "episodeAiring, episodeSeen, episodeImage FROM episodes ";
    retrieveEpisodesRequest += "WHERE seasonId = ";
    retrieveEpisodesRequest += QString::number(seasonDbId);
    retrieveEpisodesRequest += " AND showId = ";
    retrieveEpisodesRequest += QString::number(showDbId);
    retrieveEpisodesRequest += ";";
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
            SerieSubListedItem *show = new SerieSubListedItem(record.value(2).toString(),
                                                              record.value(1).toString(),
                                                              record.value(3).toString());
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
                                                              (record.value(4).toInt() != 0)));
        }
    }
}

void SeriesPlugin::checkIfDatabaseSchemaExists(QList<QSqlRecord> result, void *data)
{
}

void SeriesPlugin::genericDatabaseCallBack(QList<QSqlRecord> result, void *data)
{
}




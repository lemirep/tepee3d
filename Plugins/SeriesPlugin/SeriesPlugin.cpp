#include "SeriesPlugin.h"

SeriesPlugin::SeriesPlugin() : PluginBase()
{
    // WEBSERVICES CALLBACKS HASH
    this->webServicesCallBacks[SEARCH_SHOW_REQUEST] = &SeriesPlugin::searchForShowCallBack;
    this->webServicesCallBacks[SEARCH_EPISODE_REQUEST] = &SeriesPlugin::searchForEpisodeCallBack;
    this->webServicesCallBacks[GET_SEASONS] = &SeriesPlugin::getSeasonsForShowCallBack;
    this->webServicesCallBacks[GET_EPISODES_FOR_SEASON] = &SeriesPlugin::getEpisodesForSeasonCallBack;
    // DATABASE CALLBACKS HASH
    this->databaseCallBacks[RETRIEVE_SHOWS] = &SeriesPlugin::retrieveShowsFromDatabaseCallBack;
    this->databaseCallBacks[RETRIEVE_SEASONS_FOR_SHOW] = &SeriesPlugin::retrieveSeasonsForShowDatabaseCallBack;
    this->databaseCallBacks[RETRIEVE_EPISODES_FOR_SHOW_SEASON] = &SeriesPlugin::retrieveEpisodesForShowSeasonDatabaseCallBack;
    this->databaseCallBacks[CHECK_IF_DATABASE_FORMAT_EXISTS] = &SeriesPlugin::checkIfDatabaseSchemaExists;
    this->databaseCallBacks[GENERIC_REQUEST] = &SeriesPlugin::genericDatabaseCallBack;
    // CREATE SERIES MODEL
    this->followedSeriesModel = new Models::SubListedListModel(new SerieSubListedItem("", "", ""));

    this->initPlugin();
}
// ALL the function should be implemented

int SeriesPlugin::getPluginId()
{
    return PLUGIN_ID;
}

void SeriesPlugin::initPlugin()
{
    //    this->executeHttpGetRequest(QNetworkRequest(QUrl("http://127.0.0.1/RESTphp/index.php")),1);
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

void    SeriesPlugin::receiveResultFromSQLQuery(QList<QSqlRecord> result, int id)
{
    qDebug() << "Received DATABASE CallBack";
    (this->*this->databaseCallBacks[id])(result);
}

void    SeriesPlugin::receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data)
{
    qDebug() << "Received WebService CallBack";
    (this->*this->webServicesCallBacks[id])(reply, data);
}

QObject    *SeriesPlugin::getFollowedSeriesModel()
{
    if (this->followedSeriesModel->rowCount() == 0)
        this->searchForShow("the walking dead");
    return this->followedSeriesModel;
}

QObject *SeriesPlugin::getSeasonsModelFromSerieId(int serieId)
{
    SerieSubListedItem *serie = (SerieSubListedItem *)this->followedSeriesModel->find(serieId);
    if (serie)
        return serie->submodel();
    return NULL;
}

QObject *SeriesPlugin::getEpisodesFromSeasonAndShowId(int serieId, int seasonId)
{
    SerieSubListedItem *serie = (SerieSubListedItem *)this->followedSeriesModel->find(serieId);
    SeasonSubListedItem *season = NULL;
    if (serie != NULL && (season = (SeasonSubListedItem *)serie->submodel()->find(seasonId)) != NULL)
        return season->submodel();
    return NULL;
}

void SeriesPlugin::searchForShow(QString showName)
{
    PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl("http://api.trakt.tv/search/shows.json/"\
                                                           + QString(TRAKT_API_KEY)\
                                                           + "/" + showName.replace(" ", "-"))), SEARCH_SHOW_REQUEST);
}

void SeriesPlugin::searchForEpisode(QString episodeName)
{
    PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl("http://api.trakt.tv/search/episodes.json/"\
                                                           + QString(TRAKT_API_KEY) + "/"\
                                                           + episodeName.replace(" ", "-"))),
                                                             SEARCH_EPISODE_REQUEST);
}

void SeriesPlugin::getSeasonsForShow(SerieSubListedItem *show)
{
    QString showName = show->data(SerieSubListedItem::serieName).toString();
    qDebug() << "showName " << showName;
    PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl("http://api.trakt.tv/show/seasons.json/"\
                                                           + QString(TRAKT_API_KEY)\
                                                           + "/"+ showName.replace(" ", "-"))),
                                                            GET_SEASONS, (void *)show);
}

void SeriesPlugin::getEpisodesForShowAndSeason(QString showName, SeasonSubListedItem *season)
{
    PluginBase::executeHttpGetRequest(QNetworkRequest(QUrl("http://api.trakt.tv/show/season.json/"\
                                                           + QString(TRAKT_API_KEY) + "/" + showName.replace(" ", "-")\
                                                           + "/" +  QString::number(season->data(SeasonSubListedItem::seasonId).toInt()))),\
                                                            GET_EPISODES_FOR_SEASON, (void *)season);
}



// WEB SERVICES CALL BACKS
void SeriesPlugin::searchForShowCallBack(QNetworkReply *reply, void *data)
{
    if (reply != NULL)
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        // DO NOT FORGET TO DELETE THE REPLY
        delete reply;
        if (!jsonDoc.isNull() && !jsonDoc.isEmpty() && jsonDoc.isArray())
        {
            QJsonArray showsArray = jsonDoc.array();
            foreach (QJsonValue arrayVal, showsArray)
            {
                if (arrayVal.isObject())
                {
                    QJsonObject show = arrayVal.toObject();
                    if (!show.isEmpty())
                    {
                        QJsonObject imageObj = show.take("images").toObject();
                        SerieSubListedItem *showItem =  new SerieSubListedItem(show.value("imdb_id").toString(),
                                                                                    show.value("title").toString(),
                                                                                    imageObj.value("poster").toString());
                        this->followedSeriesModel->appendRow(showItem);
                        this->getSeasonsForShow(showItem);
                    }
                }
            }
        }
        else
            qDebug() << "An error occured when retrieving the JSON";
    }
}

void SeriesPlugin::searchForEpisodeCallBack(QNetworkReply *reply, void *data)
{
}

void SeriesPlugin::getSeasonsForShowCallBack(QNetworkReply *reply, void *data)
{
    if (reply != NULL)
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        // DO NOT FORGET TO DELETE THE REPLY
        delete reply;
        if (!jsonDoc.isNull() && !jsonDoc.isEmpty() && jsonDoc.isArray())
        {
            QJsonArray showsArray = jsonDoc.array();
            QList<Models::ListItem *> seasons;
            SerieSubListedItem *show = reinterpret_cast<SerieSubListedItem*>(data);
            foreach (QJsonValue arrayVal, showsArray)
            {
                QJsonObject seasonObj = arrayVal.toObject();
                if (!seasonObj.isEmpty())
                {
                    QJsonObject image = seasonObj.value("images").toObject();
                    SeasonSubListedItem* tmpSeason = new SeasonSubListedItem(static_cast<int>(seasonObj.value("season").toDouble()),
                                                       static_cast<int>(seasonObj.value("episodes").toDouble()),
                                                       image.value("poster").toString());
                    seasons << (Models::ListItem*)tmpSeason;
                    this->getEpisodesForShowAndSeason(show->data(SerieSubListedItem::serieName).toString(), tmpSeason);
                }
            }
            // APPEND SEASONS MODEL TO SHOW MODEL
            show->submodel()->appendRows(seasons);
        }
    }
}

void SeriesPlugin::getEpisodesForSeasonCallBack(QNetworkReply *reply, void *data)
{
    if (reply != NULL)
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        // DO NOT FORGET TO DELETE THE REPLY
        delete reply;
        if (!jsonDoc.isNull() && !jsonDoc.isEmpty() && jsonDoc.isArray())
        {
            QJsonArray showsArray = jsonDoc.array();
            QList<Models::ListItem *> episodes;
            SeasonSubListedItem *season = reinterpret_cast<SeasonSubListedItem*>(data);
            foreach (QJsonValue arrayVal, showsArray)
            {
                QJsonObject episodeObj = arrayVal.toObject();
                if (!episodeObj.isEmpty())
                {
                    QJsonObject image = episodeObj.value("images").toObject();
                    episodes << (Models::ListItem*)new EpisodeListItem(static_cast<int>(episodeObj.value("episode").toDouble()),
                                                    static_cast<int>(episodeObj.value("number").toDouble()),
                                                    static_cast<int>(episodeObj.value("season").toDouble()),
                                                    episodeObj.value("title").toString(),
                                                    episodeObj.value("overview").toString(),
                                                    image.value("screen").toString(),
                                                    QDateTime::fromMSecsSinceEpoch(episodeObj.value("first_aired").toDouble()));
                }
            }
            // APPEND EPISODE TO SEASON SUBMODEL
            season->submodel()->appendRows(episodes);
        }
    }
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



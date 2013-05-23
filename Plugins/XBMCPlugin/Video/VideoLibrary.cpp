#include "VideoLibrary.h"

VideoLibrary::VideoLibrary(QObject *parent) : QObject(parent)
{
    this->webCallBacks[RETRIEVE_MOVIES] = &VideoLibrary::retrieveMoviesCallBack;
    this->webCallBacks[RETRIEVE_TVSHOWS] = &VideoLibrary::retrieveTVShowsCallBack;
    this->webCallBacks[RETRIEVE_TVSHOW_SEASONS] = &VideoLibrary::retrieveTVShowSeasonsCallBack;
    this->webCallBacks[RETRIEVE_TVSHOW_EPISODES] = &VideoLibrary::retrieveTVShowEpisodesCallBack;

    this->tvShowsLibraryModel = new Models::SubListedListModel(new TVShowModel());
    this->moviesLibraryModel = new Models::ListModel(new MovieModel());
}

int VideoLibrary::getMajorIDRequestHandled() const
{
    return MAJOR_ID_REQUEST;
}

void VideoLibrary::receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data)
{
    (this->*this->webCallBacks[id])(reply, data);
}

void VideoLibrary::retrieveMovies(void *dataModel)
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("VideoLibrary.GetMovies")));

    QJsonObject paramObj;
    QJsonArray   properties;

    properties.prepend(QJsonValue(QString("title")));
    properties.prepend(QJsonValue(QString("genre")));
    properties.prepend(QJsonValue(QString("studio")));
    properties.prepend(QJsonValue(QString("thumbnail")));
    properties.prepend(QJsonValue(QString("plot")));
    properties.prepend(QJsonValue(QString("year")));
    properties.prepend(QJsonValue(QString("rating")));
    properties.prepend(QJsonValue(QString("file")));
    properties.prepend(QJsonValue(QString("streamdetails")));
    paramObj.insert("properties", QJsonValue(properties));

    requestJson.insert("params", QJsonValue(paramObj));
    // "ID IS TRANSMITTED BACK WITH RESPONSE TO IDENTITFY THE QUERY
    requestJson.insert("id", QJsonValue(QString("movies")));

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(RETRIEVE_MOVIES), dataModel);
}

void VideoLibrary::retrieveTVShows(void *dataModel)
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("VideoLibrary.GetTVShows")));

    QJsonObject paramObj;
    QJsonArray   properties;

    properties.prepend(QJsonValue(QString("title")));
    properties.prepend(QJsonValue(QString("year")));
    properties.prepend(QJsonValue(QString("rating")));
    properties.prepend(QJsonValue(QString("playcount")));
    properties.prepend(QJsonValue(QString("episode")));
    properties.prepend(QJsonValue(QString("season")));
    properties.prepend(QJsonValue(QString("file")));
    properties.prepend(QJsonValue(QString("thumbnail")));
    paramObj.insert("properties", QJsonValue(properties));

    requestJson.insert("params", QJsonValue(paramObj));
    // "ID IS TRANSMITTED BACK WITH RESPONSE TO IDENTITFY THE QUERY
    requestJson.insert("id", QJsonValue(QString("tvshows")));

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(RETRIEVE_TVSHOWS), dataModel);
}

void VideoLibrary::retrieveTVShowSeasons(int tvShowId, void *dataModel)
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("VideoLibrary.GetSeasons")));

    QJsonObject paramObj;
    QJsonArray   properties;

    paramObj.insert("tvshowid", QJsonValue(tvShowId));

    properties.prepend(QJsonValue(QString("season")));
    properties.prepend(QJsonValue(QString("episode")));
    properties.prepend(QJsonValue(QString("thumbnail")));
    properties.prepend(QJsonValue(QString("tvshowid")));
    paramObj.insert("properties", QJsonValue(properties));

    requestJson.insert("params", QJsonValue(paramObj));
    // "ID IS TRANSMITTED BACK WITH RESPONSE TO IDENTITFY THE QUERY
    requestJson.insert("id", QJsonValue(QString("tvshows_seasons")));

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(RETRIEVE_TVSHOW_SEASONS), dataModel);
}

void VideoLibrary::retrieveTVShowEpisodes(int tvShowId, int season, void *dataModel)
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("VideoLibrary.GetEpisodes")));

    QJsonObject paramObj;
    QJsonArray   properties;

    paramObj.insert("tvshowid", QJsonValue(tvShowId));
    paramObj.insert("season", QJsonValue(season));

    properties.prepend(QJsonValue(QString("title")));
    properties.prepend(QJsonValue(QString("file")));
    properties.prepend(QJsonValue(QString("thumbnail")));
    properties.prepend(QJsonValue(QString("rating")));
    properties.prepend(QJsonValue(QString("resume")));
    properties.prepend(QJsonValue(QString("season")));
    properties.prepend(QJsonValue(QString("tvshowid")));
    properties.prepend(QJsonValue(QString("firstaired")));
    properties.prepend(QJsonValue(QString("episode")));
    paramObj.insert("properties", QJsonValue(properties));

    requestJson.insert("params", QJsonValue(paramObj));
    // "ID IS TRANSMITTED BACK WITH RESPONSE TO IDENTITFY THE QUERY
    requestJson.insert("id", QJsonValue(QString("tvshows")));

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(RETRIEVE_TVSHOW_EPISODES), dataModel);
}

Models::ListModel *VideoLibrary::getMoviesLibraryModel() const
{
    return this->moviesLibraryModel;
}

Models::ListModel *VideoLibrary::getTVShowsLibraryModel() const
{
    return this->tvShowsLibraryModel;
}

void VideoLibrary::retrieveMoviesCallBack(QNetworkReply *reply, void *data)
{
    if (reply != NULL && data != NULL)
    {
        QJsonDocument jsonResponse = Utils::QJsonDocumentFromReply(reply);
        if (!jsonResponse.isNull() && !jsonResponse.isEmpty() && jsonResponse.isObject())
        {
//            qDebug() << jsonResponse.toJson();
            QJsonObject resultObj = jsonResponse.object().value("result").toObject();
            QJsonArray  moviesArray;
            if (!resultObj.isEmpty())
            {
                moviesArray = resultObj.value("movies").toArray();
                foreach (QJsonValue movieObj, moviesArray)
                {
                    MovieModel *movie = this->parseMovie(movieObj.toObject());
                    if (movie != NULL)
                        reinterpret_cast<Models::ListModel *>(data)->appendRow(movie);

                }
            }
        }
    }
}

void VideoLibrary::retrieveTVShowsCallBack(QNetworkReply *reply, void *data)
{
    if (reply != NULL && data != NULL)
    {
        QJsonDocument jsonResponse = Utils::QJsonDocumentFromReply(reply);
        if (!jsonResponse.isNull() && !jsonResponse.isEmpty() && jsonResponse.isObject())
        {
            QJsonObject resultObj = jsonResponse.object().value("result").toObject();
            QJsonArray  tvShowsArray;
            if (!resultObj.isEmpty())
            {
                tvShowsArray = resultObj.value("tvshows").toArray();
                foreach (QJsonValue tvShowObj, tvShowsArray)
                {
                    TVShowModel *tvShow = this->parseTVShow(tvShowObj.toObject());
                    if (tvShow != NULL)
                    {
                        this->retrieveTVShowSeasons(tvShow->id(), (void *)tvShow->submodel());
                        reinterpret_cast<Models::ListModel *>(data)->appendRow(tvShow);
                    }
                }
            }
        }
    }
}

void VideoLibrary::retrieveTVShowSeasonsCallBack(QNetworkReply *reply, void *data)
{
    if (reply != NULL && data != NULL)
    {
        QJsonDocument jsonResponse = Utils::QJsonDocumentFromReply(reply);
        if (!jsonResponse.isNull() && !jsonResponse.isEmpty() && jsonResponse.isObject())
        {
            QJsonObject resultObj = jsonResponse.object().value("result").toObject();
            QJsonArray  tvShowsSeasonsArray;
            if (!resultObj.isEmpty())
            {
                tvShowsSeasonsArray = resultObj.value("seasons").toArray();
                foreach (QJsonValue seasonObj, tvShowsSeasonsArray)
                {
                    TVShowSeasonModel *season = this->parseTVShowSeason(seasonObj.toObject());
                    if (season != NULL)
                    {
                        this->retrieveTVShowEpisodes(season->getTVShowId(), season->id(), season->submodel());
                        reinterpret_cast<Models::ListModel *>(data)->appendRow(season);
                    }
                }
            }
        }
    }
}

void VideoLibrary::retrieveTVShowEpisodesCallBack(QNetworkReply *reply, void *data)
{
    if (reply != NULL && data != NULL)
    {
        QJsonDocument jsonResponse = Utils::QJsonDocumentFromReply(reply);
        if (!jsonResponse.isNull() && !jsonResponse.isEmpty() && jsonResponse.isObject())
        {
            QJsonObject resultObj = jsonResponse.object().value("result").toObject();
            QJsonArray  tvShowEpisodesArray;
            if (!resultObj.isEmpty())
            {
                tvShowEpisodesArray = resultObj.value("episodes").toArray();
                foreach (QJsonValue episodeObj, tvShowEpisodesArray)
                {
                    TVShowEpisodeModel *episode = this->parseTVShowEpisode(episodeObj.toObject());
                    if (episode != NULL)
                    {
                        reinterpret_cast<Models::ListModel *>(data)->appendRow(episode);
                    }
                }
            }
        }
    }
}

TVShowModel *VideoLibrary::parseTVShow(const QJsonObject &tvShowObj)
{
    if (!tvShowObj.isEmpty())
    {
        TVShowModel *show = new TVShowModel(NULL, tvShowObj.value("tvshowid").toDouble());
        show->setFile(tvShowObj.value("file").toString());
        show->setTitle(tvShowObj.value("title").toString());
        show->setYear(tvShowObj.value("year").toDouble());
        show->setThumbnail(tvShowObj.value("thumbnail").toString());
        show->setRating(tvShowObj.value("rating").toDouble());
        show->setEpisode(tvShowObj.value("episode").toDouble());
        show->setPlaycount(tvShowObj.value("playcount").toDouble());
        return show;
    }
    return NULL;
}

TVShowSeasonModel *VideoLibrary::parseTVShowSeason(const QJsonObject &tvShowSeasonObj)
{
    if (!tvShowSeasonObj.isEmpty())
    {
        TVShowSeasonModel *season = new TVShowSeasonModel(NULL, tvShowSeasonObj.value("season").toDouble());
        season->setEpisode(tvShowSeasonObj.value("episode").toDouble());
        season->setTVShowId(tvShowSeasonObj.value("tvshowid").toDouble());
        season->setThumbnail(tvShowSeasonObj.value("thumbnail").toString());
        return season;
    }
    return NULL;
}

TVShowEpisodeModel *VideoLibrary::parseTVShowEpisode(const QJsonObject &tvShowEpisodeObj)
{
    if (!tvShowEpisodeObj.isEmpty())
    {
        TVShowEpisodeModel *episode = new TVShowEpisodeModel(NULL, tvShowEpisodeObj.value("episodeid").toDouble());
        episode->setSeason(tvShowEpisodeObj.value("season").toDouble());
        episode->setRating(tvShowEpisodeObj.value("rating").toDouble());
        episode->setFile(tvShowEpisodeObj.value("file").toString());
        episode->setTitle(tvShowEpisodeObj.value("title").toString());
        episode->setThumbnail(tvShowEpisodeObj.value("thumbnail").toString());
        episode->setTVShowId(tvShowEpisodeObj.value("tvshowid").toDouble());
        episode->setAired(tvShowEpisodeObj.value("firstaired").toString());
        return episode;
    }
    return NULL;
}

MovieModel *VideoLibrary::parseMovie(const QJsonObject &movieObj)
{
    if (!movieObj.isEmpty())
    {
        MovieModel *movie = new MovieModel(NULL, movieObj.value("movieid").toDouble());
        movie->setTitle(movieObj.value("title").toString());
        movie->setGenre(movieObj.value("genre").toArray().first().toString());
        movie->setStudio(movieObj.value("studio").toArray().first().toString());
        movie->setThumbnail(movieObj.value("thumbnail").toString());
        movie->setPlot(movieObj.value("plot").toString());
        movie->setYear(movieObj.value("year").toDouble());
        movie->setRating(movieObj.value("rating").toDouble());
        movie->setFile(movieObj.value("file").toString());
        // PARSE STREAM DETAILS LATERS
        return movie;
    }
    return NULL;
}


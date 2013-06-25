#include "VideoLibrary.h"

VideoLibrary::VideoLibrary(QObject *parent) : QObject(parent)
{
    this->webCallBacks[RETRIEVE_MOVIES] = &VideoLibrary::retrieveMoviesCallBack;
    this->webCallBacks[RETRIEVE_TVSHOWS] = &VideoLibrary::retrieveTVShowsCallBack;
    this->webCallBacks[RETRIEVE_TVSHOW_SEASONS] = &VideoLibrary::retrieveTVShowSeasonsCallBack;
    this->webCallBacks[RETRIEVE_TVSHOW_EPISODES] = &VideoLibrary::retrieveTVShowEpisodesCallBack;
    this->webCallBacks[REFRESH_VIDEO_LIBRARY] = &VideoLibrary::refreshVideoLibraryCallBack;

    this->tvShowsLibraryModel = new Models::SubListedListModel(new TVShowModel());
    this->moviesLibraryModel = new Models::ListModel(new MovieModel());
    this->m_asyncRequests = 0;
    QObject::connect(this, SIGNAL(asyncRequestChanged()), this, SLOT(checkForRemoval()));
}

int VideoLibrary::getMajorIDRequestHandled() const
{
    return MAJOR_ID_REQUEST_VIDEO;
}

void VideoLibrary::receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data)
{
    (this->*this->webCallBacks[id])(reply, data);
}

void VideoLibrary::retrieveMovies(Models::ListModel *dataModel)
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
    properties.prepend(QJsonValue(QString("runtime")));
    properties.prepend(QJsonValue(QString("rating")));
    properties.prepend(QJsonValue(QString("file")));
    properties.prepend(QJsonValue(QString("streamdetails")));
    paramObj.insert("properties", QJsonValue(properties));

    requestJson.insert("params", QJsonValue(paramObj));
    // "ID IS TRANSMITTED BACK WITH RESPONSE TO IDENTITFY THE QUERY
    requestJson.insert("id", QJsonValue(QString("movies")));
    this->increaseAsyncRequest();
    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_VIDEO, RETRIEVE_MOVIES), dataModel);
}

void VideoLibrary::retrieveTVShows(Models::ListModel *dataModel)
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
    this->increaseAsyncRequest();
    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_VIDEO, RETRIEVE_TVSHOWS), dataModel);
}

void VideoLibrary::retrieveTVShowSeasons(int tvShowId, Models::ListModel *dataModel)
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
    this->increaseAsyncRequest();
    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_VIDEO, RETRIEVE_TVSHOW_SEASONS), dataModel);
}

void VideoLibrary::retrieveTVShowEpisodes(int tvShowId, int season, Models::ListModel *dataModel)
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
    properties.prepend(QJsonValue(QString("runtime")));

    paramObj.insert("properties", QJsonValue(properties));

    requestJson.insert("params", QJsonValue(paramObj));
    // "ID IS TRANSMITTED BACK WITH RESPONSE TO IDENTITFY THE QUERY
    requestJson.insert("id", QJsonValue(QString("tvshows")));
    this->increaseAsyncRequest();
    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_VIDEO, RETRIEVE_TVSHOW_EPISODES), dataModel);
}

void VideoLibrary::refreshVideoLibrary()
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("VideoLibrary.Scan")));

    // "ID IS TRANSMITTED BACK WITH RESPONSE TO IDENTITFY THE QUERY
    requestJson.insert("id", QJsonValue(QString("refresh")));
    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_VIDEO, REFRESH_VIDEO_LIBRARY));
}

void VideoLibrary::reloadDataModels()
{
    // MODELS ARE SAVED IN CASE THEY ARE STILL SYNCHRONOUS REQUESTS GOING ON
    this->dirtyModelItem.append(this->moviesLibraryModel->takeRows());
    this->dirtyModelItem.append(this->tvShowsLibraryModel->takeRows());

    this->retrieveMovies(this->moviesLibraryModel);
    this->retrieveTVShows(this->tvShowsLibraryModel);
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
        this->decreaseAsyncRequest();
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
                        this->retrieveTVShowSeasons(tvShow->id(), tvShow->submodel());
                        reinterpret_cast<Models::ListModel *>(data)->appendRow(tvShow);
                    }
                }
            }
        }
        this->decreaseAsyncRequest();
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
        this->decreaseAsyncRequest();
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
        this->decreaseAsyncRequest();
    }
}

void VideoLibrary::refreshVideoLibraryCallBack(QNetworkReply *reply, void *data)
{
    Q_UNUSED(data)
    if (reply != NULL)
    {
        QJsonDocument jsonResponse = Utils::QJsonDocumentFromReply(reply);
        if (!jsonResponse.isNull() && !jsonResponse.isEmpty() && jsonResponse.isObject())
        {
            QString result = jsonResponse.object().value("result").toString();
            if (result.compare("OK") == 0)
                this->reloadDataModels();
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
        episode->setRuntime(tvShowEpisodeObj.value("runtime").toDouble());
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
        movie->setRuntime(movieObj.value("runtime").toDouble());
        // PARSE STREAM DETAILS LATERS
        return movie;
    }
    return NULL;
}

void VideoLibrary::increaseAsyncRequest()
{
    this->m_asyncRequests++;
    emit asyncRequestChanged();
}

void VideoLibrary::decreaseAsyncRequest()
{
    this->m_asyncRequests--;
    emit asyncRequestChanged();
}

void VideoLibrary::checkForRemoval()
{
    if (this->m_asyncRequests == 0 && !this->dirtyModelItem.empty())
    {
        qDebug() << "Freeing Video Models >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>..";
        foreach (QList<Models::ListItem *> dirtyList, this->dirtyModelItem)
        {
            qDebug() << "VIDEO TO RREMOVE : " << dirtyList.size();
            //            while (!dirtyList.empty())
            //                delete dirtyList.takeFirst();
        }
    }
}


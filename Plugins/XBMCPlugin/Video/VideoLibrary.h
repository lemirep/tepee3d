#ifndef VIDEOLIBRARY_H
#define VIDEOLIBRARY_H

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <IWebRequestDispatcher.h>
#include <ListModel.h>
#include "TVShowModel.h"
#include "MovieModel.h"
#include <QDebug>

#define MAJOR_ID_REQUEST 4
#define REQUEST_ID_BUILDER(id) ((MAJOR_ID_REQUEST * 10) + id)
#define RETRIEVE_MOVIES 0
#define RETRIEVE_TVSHOWS 1
#define RETRIEVE_TVSHOW_SEASONS 2
#define RETRIEVE_TVSHOW_EPISODES 3

class VideoLibrary : public QObject, public IWebRequestDispatcher
{
    Q_OBJECT
public:
    VideoLibrary(QObject *parent = 0);

    int                     getMajorIDRequestHandled()  const;
    void                  receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data);

    void                retrieveMovies(void *dataModel);
    void                retrieveTVShows(void *dataModel);
    void                retrieveTVShowSeasons(int tvShowId, void *dataModel);
    void                retrieveTVShowEpisodes(int tvShowId, int season, void *dataModel);

    Models::ListModel *getMoviesLibraryModel() const;
    Models::ListModel *getTVShowsLibraryModel() const;

private:

    QHash<int , void (VideoLibrary::*)(QNetworkReply *, void *data)>    webCallBacks;

    Models::ListModel   *moviesLibraryModel;
    Models::ListModel   *tvShowsLibraryModel;

    void            retrieveMoviesCallBack(QNetworkReply *reply, void *data);
    void            retrieveTVShowsCallBack(QNetworkReply *reply, void *data);
    void            retrieveTVShowSeasonsCallBack(QNetworkReply *reply, void *data);
    void            retrieveTVShowEpisodesCallBack(QNetworkReply *reply, void *data);

    TVShowModel *parseTVShow(const QJsonObject& tvShowObj);
    TVShowSeasonModel *parseTVShowSeason(const QJsonObject &tvShowSeasonObj);
    TVShowEpisodeModel *parseTVShowEpisode(const QJsonObject &tvShowEpisodeObj);
    MovieModel *parseMovie(const QJsonObject &movieObj);

signals:
    void        performJsonRPCRequest(const QJsonObject &request, int requestId, void *data = NULL);
};

#endif // VIDEOLIBRARY_H

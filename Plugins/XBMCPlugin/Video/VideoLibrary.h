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

#define MAJOR_ID_REQUEST_VIDEO 4
#define RETRIEVE_MOVIES 0
#define RETRIEVE_TVSHOWS 1
#define RETRIEVE_TVSHOW_SEASONS 2
#define RETRIEVE_TVSHOW_EPISODES 3
#define REFRESH_VIDEO_LIBRARY 4

class VideoLibrary : public QObject, public IWebRequestDispatcher
{
    Q_OBJECT
public:
    VideoLibrary(QObject *parent = 0);

    int                 getMajorIDRequestHandled()  const;
    void                receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data);

    void                retrieveMovies(Models::ListModel *dataModel);
    void                retrieveTVShows(Models::ListModel *dataModel);
    void                retrieveTVShowSeasons(int tvShowId, Models::ListModel *dataModel);
    void                retrieveTVShowEpisodes(int tvShowId, int season, Models::ListModel *dataModel);
    void                refreshVideoLibrary();
    void                reloadDataModels();

    Models::ListModel   *getMoviesLibraryModel() const;
    Models::ListModel   *getTVShowsLibraryModel() const;

private:

    QHash<int , void (VideoLibrary::*)(QNetworkReply *, void *data)>    webCallBacks;

    Models::ListModel   *moviesLibraryModel;
    Models::ListModel   *tvShowsLibraryModel;
    int                       m_asyncRequests;
    QList< QList<Models::ListItem *> > dirtyModelItem;


    void                retrieveMoviesCallBack(QNetworkReply *reply, void *data);
    void                retrieveTVShowsCallBack(QNetworkReply *reply, void *data);
    void                retrieveTVShowSeasonsCallBack(QNetworkReply *reply, void *data);
    void                retrieveTVShowEpisodesCallBack(QNetworkReply *reply, void *data);
    void                refreshVideoLibraryCallBack(QNetworkReply *reply, void *data);

    TVShowModel         *parseTVShow(const QJsonObject& tvShowObj);
    TVShowSeasonModel   *parseTVShowSeason(const QJsonObject &tvShowSeasonObj);
    TVShowEpisodeModel  *parseTVShowEpisode(const QJsonObject &tvShowEpisodeObj);
    MovieModel          *parseMovie(const QJsonObject &movieObj);

    void                      increaseAsyncRequest();
    void                      decreaseAsyncRequest();
private slots:
    void                      checkForRemoval();

signals:
    void                performJsonRPCRequest(const QJsonObject &request, int requestId, void *data = NULL);
    void                asyncRequestChanged();

};

#endif // VIDEOLIBRARY_H

#ifndef AUDIOLIBRARY_H
#define AUDIOLIBRARY_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QHash>
#include <IWebRequestDispatcher.h>
#include <SubListedListModel.h>
#include "Models/AlbumModel.h"
#include "Models/ArtistModel.h"
#include "Models/SongModel.h"

#define MAJOR_ID_REQUEST 1
#define RETRIEVE_ALBUMS 0
#define RETRIEVE_ARTISTS 1
#define RETRIEVE_SONGS 2
#define RETRIEVE_PLAYLIST 3

#define REQUEST_ID_BUILDER(id) ((MAJOR_ID_REQUEST * 10) + id)

class AudioLibrary : public QObject, public IWebRequestDispatcher
{
    Q_OBJECT
public:
    AudioLibrary(QObject *parent = 0);

    int                         getMajorIDRequestHandled() const;
    void                      receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data);

    void                      retrieveAudioAlbums(void *dataModel);
    void                      retrieveAudioArtists(void *dataModel);
    void                      retrieveAudioPlaylist();
    void                      retrieveAllSongs(void *dataModel);
    void                      retrieveSongsForAlbum(int albumId,void *dataModel);
    void                      retrieveSongsForArtist(int artistId, void *dataModel);
    void                      retrieveSongsForGenre(int genreId, void *dataModel);

    Models::ListModel *getArtistsLibraryModel() const;
    Models::ListModel *getAlbumsLibraryModel() const;
    Models::ListModel *getSongsLibraryModel() const;

private:

    QHash<int, void (AudioLibrary::*)(QNetworkReply *reply, void *data)> webCallBacks;

    Models::SubListedListModel  *artistsLibraryModel;
    Models::SubListedListModel  *albumsLibraryModel;
    Models::ListModel                  *songsLibraryModel;
    Models::ListModel                  *songsPlayListModel;

    void                     retrieveAudioAlbumsCallBack(QNetworkReply *reply, void *data);
    void                     retrieveAudioArtistsCallBack(QNetworkReply *reply, void *data);
    void                     retrieveSongsCallBack(QNetworkReply *reply, void *data);
    void                     retrieveAudioPlaylistCallBack(QNetworkReply *reply, void *data);

    QJsonObject      getSongsRequestBaseJSON();

   AlbumModel*       parseJsonAlbum(const QJsonObject & jsonAlbum);
   ArtistModel*         parseJsonArtist(const QJsonObject & jsonArtist);
   SongModel*         parseJsonSong(const QJsonObject & jsonSong);

signals:
    void                     performJsonRPCRequest(const QJsonObject &request, int requestId, void *data = NULL);
};

#endif // AUDIOLIBRARY_H

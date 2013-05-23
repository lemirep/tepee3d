#include "AudioLibrary.h"
#include <QDebug>

AudioLibrary::AudioLibrary(QObject *parent) : QObject(parent)
{
    this->webCallBacks[RETRIEVE_ALBUMS] = &AudioLibrary::retrieveAudioAlbumsCallBack;
    this->webCallBacks[RETRIEVE_ARTISTS] = &AudioLibrary::retrieveAudioArtistsCallBack;
    this->webCallBacks[RETRIEVE_SONGS] = &AudioLibrary::retrieveSongsCallBack;

    this->artistsLibraryModel = new Models::SubListedListModel(new ArtistModel());
    this->albumsLibraryModel = new Models::SubListedListModel(new AlbumModel());
    this->songsLibraryModel = new Models::ListModel(new SongModel());
}

int AudioLibrary::getMajorIDRequestHandled() const
{
    return MAJOR_ID_REQUEST;
}

void AudioLibrary::receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data)
{
    qDebug() << "Receiving Request Result";
    (this->*this->webCallBacks[id])(reply, data);
}


void AudioLibrary::retrieveAudioAlbums(void *dataModel)
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("AudioLibrary.GetAlbums")));

    QJsonObject paramObj;
    QJsonArray   properties;

    properties.prepend(QJsonValue(QString("title")));
    properties.prepend(QJsonValue(QString("artistid")));
    properties.prepend(QJsonValue(QString("description")));
    properties.prepend(QJsonValue(QString("genre")));
    properties.prepend(QJsonValue(QString("rating")));
    properties.prepend(QJsonValue(QString("thumbnail")));
    properties.prepend(QJsonValue(QString("year")));
    properties.prepend(QJsonValue(QString("mood")));
    paramObj.insert("properties", QJsonValue(properties));

    requestJson.insert("params", QJsonValue(paramObj));
    // "ID IS TRANSMITTED BACK WITH RESPONSE TO IDENTITFY THE QUERY
    requestJson.insert("id", QJsonValue(QString("albums")));

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(RETRIEVE_ALBUMS), dataModel);
}

void AudioLibrary::retrieveAudioArtists(void *dataModel)
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("AudioLibrary.GetArtists")));

    QJsonObject paramObj;
    QJsonArray   properties;

    properties.prepend(QJsonValue(QString("thumbnail")));
    properties.prepend(QJsonValue(QString("born")));
    properties.prepend(QJsonValue(QString("mood")));
    properties.prepend(QJsonValue(QString("genre")));
    paramObj.insert("properties", QJsonValue(properties));
    requestJson.insert("params", QJsonValue(paramObj));
    requestJson.insert("id", QJsonValue(QString("artists")));

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(RETRIEVE_ARTISTS), dataModel);
}

void AudioLibrary::retrieveAudioPlaylist()
{
    //    QJsonObject requestJson;
    //    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    //    requestJson.insert("method", QJsonValue(QString("AudioLibrary.GetArtists")));

    //    QJsonObject paramObj;
    //    QJsonArray   properties;

    //    properties.prepend(QJsonValue(QString("thumbnail")));
    //    properties.prepend(QJsonValue(QString("born")));
    //    properties.prepend(QJsonValue(QString("mood")));
    //    properties.prepend(QJsonValue(QString("genre")));
    //    paramObj.insert("properties", QJsonValue(properties));
    //    requestJson.insert("params", QJsonValue(paramObj));
    //    requestJson.insert("id", QJsonValue(QString("artists")));

    //    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(RETRIEVE_ARTISTS));
}

void AudioLibrary::retrieveAllSongs(void *dataModel)
{
    QJsonObject requestJson = this->getSongsRequestBaseJSON();

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(RETRIEVE_SONGS), dataModel);
}

void AudioLibrary::retrieveSongsForAlbum(int albumId, void *dataModel)
{
    QJsonObject requestJson = this->getSongsRequestBaseJSON();
    QJsonObject params = requestJson.take("params").toObject();

    params.insert("albumid", QJsonValue(albumId));
     requestJson.insert("params", QJsonValue(params));
    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(RETRIEVE_SONGS), dataModel);
}

void AudioLibrary::retrieveSongsForArtist(int artistId, void *dataModel)
{
    QJsonObject requestJson = this->getSongsRequestBaseJSON();
    QJsonObject params = requestJson.take("params").toObject();

    params.insert("artistid", QJsonValue(artistId));
    requestJson.insert("params", QJsonValue(params));
    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(RETRIEVE_SONGS), dataModel);
}

void AudioLibrary::retrieveSongsForGenre(int genreId, void *dataModel)
{
    QJsonObject requestJson = this->getSongsRequestBaseJSON();
    QJsonObject params = requestJson.take("params").toObject();

    params.insert("genreid", QJsonValue(genreId));
    requestJson.insert("params", QJsonValue(params));
    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(RETRIEVE_SONGS), dataModel);
}

Models::ListModel *AudioLibrary::getArtistsLibraryModel() const
{
    return this->artistsLibraryModel;
}

Models::ListModel *AudioLibrary::getAlbumsLibraryModel() const
{
    return this->albumsLibraryModel;
}

Models::ListModel *AudioLibrary::getSongsLibraryModel() const
{
    return this->songsLibraryModel;
}

void AudioLibrary::retrieveAudioAlbumsCallBack(QNetworkReply *reply, void *data)
{
    qDebug() << "Receiving Request Result Albums";
    if (reply != NULL && data != NULL)
    {
        QJsonDocument jsonResponse = Utils::QJsonDocumentFromReply(reply);
        if (!jsonResponse.isNull() && !jsonResponse.isEmpty() && jsonResponse.isObject())
        {
            QJsonObject resultObj = jsonResponse.object().value("result").toObject();
            QJsonArray   albumsArray;

            if (!resultObj.isEmpty())
            {
                albumsArray = resultObj.value("albums").toArray();
                foreach (QJsonValue albumObj, albumsArray)
                {
                    AlbumModel *album = this->parseJsonAlbum(albumObj.toObject());
                    if (album != NULL)
                    {
                        reinterpret_cast<Models::ListModel*>(data)->appendRow(album);
                        this->retrieveSongsForAlbum(album->id(), (void *)album->submodel());
                    }
                }
            }
        }
    }
}

void AudioLibrary::retrieveAudioArtistsCallBack(QNetworkReply *reply, void *data)
{
    qDebug() << "Receiving Request Artists";
    if (reply != NULL && data != NULL)
    {
        QJsonDocument jsonResponse = Utils::QJsonDocumentFromReply(reply);
        if (!jsonResponse.isNull() && !jsonResponse.isEmpty() && jsonResponse.isObject())
        {
            QJsonObject resultObj = jsonResponse.object().value("result").toObject();
            QJsonArray  artistsArray;
            if (!resultObj.isEmpty())
            {
                artistsArray = resultObj.value("artists").toArray();
                foreach (QJsonValue artistObj, artistsArray)
                {
                    ArtistModel* artist = this->parseJsonArtist(artistObj.toObject());
                    if (artist != NULL)
                    {
                        reinterpret_cast<Models::ListModel*>(data)->appendRow(artist);
                        this->retrieveSongsForArtist(artist->id(), (void *)artist->submodel());
                    }
                }
            }
        }
    }
}

void AudioLibrary::retrieveSongsCallBack(QNetworkReply *reply, void *data)
{
    qDebug() << "Receiving Request Songs";
    if (reply != NULL && data != NULL)
    {
        QJsonDocument jsonResponse = Utils::QJsonDocumentFromReply(reply);
        if (!jsonResponse.isNull() && !jsonResponse.isEmpty() && jsonResponse.isObject())
        {
            QJsonObject resultObj = jsonResponse.object().value("result").toObject();
            QJsonArray songsArray;
            if (!resultObj.empty())
            {
                songsArray = resultObj.value("songs").toArray();
                foreach (QJsonValue songObj, songsArray)
                {
                    SongModel*  song = this->parseJsonSong(songObj.toObject());
                    if (song != NULL)
                        reinterpret_cast<Models::ListModel*>(data)->appendRow(song);
                }
            }
        }
    }
}

void AudioLibrary::retrieveAudioPlaylistCallBack(QNetworkReply *reply, void *data)
{
}

QJsonObject AudioLibrary::getSongsRequestBaseJSON( )
{
    QJsonObject requestJson;
    QJsonObject paramObj;
    QJsonArray   properties;

    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("AudioLibrary.GetSongs")));

    properties.prepend(QJsonValue(QString("title")));
    properties.prepend(QJsonValue(QString("artist")));
    properties.prepend(QJsonValue(QString("genre")));
    properties.prepend(QJsonValue(QString("rating")));
    properties.prepend(QJsonValue(QString("track")));
    properties.prepend(QJsonValue(QString("duration")));
    properties.prepend(QJsonValue(QString("thumbnail")));
    properties.prepend(QJsonValue(QString("file")));
    properties.prepend(QJsonValue(QString("artistid")));
    properties.prepend(QJsonValue(QString("albumid")));

    paramObj.insert("properties", QJsonValue(properties));
    requestJson.insert("params", QJsonValue(paramObj));
    requestJson.insert("id", QJsonValue(QString("songs")));

    return requestJson;
}

AlbumModel *AudioLibrary::parseJsonAlbum(const QJsonObject &jsonAlbum)
{
    if (!jsonAlbum.isEmpty())
    {
        AlbumModel *album = new AlbumModel(NULL, jsonAlbum.value("albumid").toDouble());
        album->setArtistId(jsonAlbum.value("artistid").toArray().first().toDouble());
        album->setDescription(jsonAlbum.value("description").toString());
        album->setGenre(jsonAlbum.value("genre").toArray().first().toString());
        album->setMood(jsonAlbum.value("mood").toArray().first().toString());
        album->setAlbumTitle(jsonAlbum.value("title").toString());
        album->setRating(jsonAlbum.value("rating").toDouble());
        album->setAlbumYear((jsonAlbum.value("year").toDouble()));
        album->setThumbnail(jsonAlbum.value("thumbnail").toString());
        return album;
    }
    return NULL;
}

ArtistModel *AudioLibrary::parseJsonArtist(const QJsonObject &jsonArtist)
{
    if (!jsonArtist.isEmpty())
    {
        ArtistModel *artist = new ArtistModel(NULL, jsonArtist.value("artistid").toDouble());
        artist->setArtistName(jsonArtist.value("artist").toString());
        artist->setBirthDate(jsonArtist.value("born").toString());
        artist->setGenre(jsonArtist.value("genre").toArray().first().toString());
        artist->setMood(jsonArtist.value("mood").toArray().first().toString());
        artist->setThumbnail(jsonArtist.value("thumbnail").toString());
        return artist;
    }
    return NULL;
}

SongModel *AudioLibrary::parseJsonSong(const QJsonObject &jsonSong)
{
    if (!jsonSong.isEmpty())
    {
        SongModel *song = new SongModel(NULL, jsonSong.value("songid").toDouble());
        song->setAlbumId(jsonSong.value("albumid").toDouble());
        song->setArtistId(jsonSong.value("artistid").toArray().first().toDouble());
        song->setDuration(jsonSong.value("duration").toDouble());
        song->setFile(jsonSong.value("file").toString());
        song->setGenre(jsonSong.value("genre").toArray().first().toString());
        song->setRating(jsonSong.value("rating").toDouble());
        song->setThumbnail(jsonSong.value("thumbnail").toString());
        song->setTitle(jsonSong.value("title").toString());
        song->setTrack(jsonSong.value("track").toDouble());
        return song;
    }
    return NULL;
}

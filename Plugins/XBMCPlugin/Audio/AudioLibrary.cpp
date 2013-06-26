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

#include "AudioLibrary.h"
#include <QDebug>

AudioLibrary::AudioLibrary(QObject *parent) : QObject(parent)
{
    this->webCallBacks[RETRIEVE_ALBUMS] = &AudioLibrary::retrieveAudioAlbumsCallBack;
    this->webCallBacks[RETRIEVE_ARTISTS] = &AudioLibrary::retrieveAudioArtistsCallBack;
    this->webCallBacks[RETRIEVE_SONGS] = &AudioLibrary::retrieveSongsCallBack;
    this->webCallBacks[REFRESH_AUDIO_LIBRARY] = &AudioLibrary::refreshAudioLibraryCallBack;

    this->artistsLibraryModel = new Models::SubListedListModel(new ArtistModel());
    this->albumsLibraryModel = new Models::SubListedListModel(new AlbumModel());
    this->songsLibraryModel = new Models::ListModel(new PlayableItemModel());

    this->m_asyncRequests = 0;

//    QObject::connect(this, SIGNAL(asyncRequestChanged()), this, SLOT(checkForRemoval()));
}

int AudioLibrary::getMajorIDRequestHandled() const
{
    return MAJOR_ID_REQUEST_AUDIO;
}

void AudioLibrary::receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data)
{
    (this->*this->webCallBacks[id])(reply, data);
}


void AudioLibrary::retrieveAudioAlbums(Models::ListModel *dataModel)
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("AudioLibrary.GetAlbums")));

    QJsonObject paramObj;
    QJsonArray   properties;
    QJsonObject sortObj;

    properties.prepend(QJsonValue(QString("title")));
    properties.prepend(QJsonValue(QString("artistid")));
    properties.prepend(QJsonValue(QString("description")));
    properties.prepend(QJsonValue(QString("genre")));
    properties.prepend(QJsonValue(QString("rating")));
    properties.prepend(QJsonValue(QString("thumbnail")));
    properties.prepend(QJsonValue(QString("year")));
    properties.prepend(QJsonValue(QString("mood")));
    sortObj.insert("order", QJsonValue(QString("ascending")));
    sortObj.insert("method", QJsonValue(QString("album")));
    paramObj.insert("properties", QJsonValue(properties));

    requestJson.insert("params", QJsonValue(paramObj));
    // "ID IS TRANSMITTED BACK WITH RESPONSE TO IDENTITFY THE QUERY
    requestJson.insert("id", QJsonValue(QString("albums")));
    this->increaseAsyncRequest();
    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_AUDIO, RETRIEVE_ALBUMS), dataModel);
}

void AudioLibrary::retrieveAudioArtists(Models::ListModel *dataModel)
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("AudioLibrary.GetArtists")));

    QJsonObject paramObj;
    QJsonArray   properties;
    QJsonObject sortObj;

    properties.prepend(QJsonValue(QString("thumbnail")));
    properties.prepend(QJsonValue(QString("born")));
    properties.prepend(QJsonValue(QString("mood")));
    properties.prepend(QJsonValue(QString("genre")));
    sortObj.insert("order", QJsonValue(QString("ascending")));
    sortObj.insert("method", QJsonValue(QString("artist")));
    paramObj.insert("properties", QJsonValue(properties));
    paramObj.insert("sort", QJsonValue(sortObj));
    requestJson.insert("params", QJsonValue(paramObj));
    requestJson.insert("id", QJsonValue(QString("artists")));
    this->increaseAsyncRequest();
    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_AUDIO, RETRIEVE_ARTISTS), dataModel);
}

void AudioLibrary::retrieveAllSongs(Models::ListModel *dataModel)
{
    QJsonObject requestJson = this->getSongsRequestBaseJSON();
    this->increaseAsyncRequest();
    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_AUDIO, RETRIEVE_SONGS), dataModel);
}

void AudioLibrary::retrieveSongsForAlbum(int albumId, Models::ListModel *dataModel)
{
    QJsonObject requestJson = this->getSongsRequestBaseJSON();
    QJsonObject params = requestJson.take("params").toObject();
    QJsonObject filter;

    filter.insert("albumid", QJsonValue(albumId));
    params.insert("filter", QJsonValue(filter));
    requestJson.insert("params", QJsonValue(params));
    this->increaseAsyncRequest();
    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_AUDIO, RETRIEVE_SONGS), dataModel);
}

void AudioLibrary::retrieveAlbumsForArtist(int artistId, Models::ListModel *dataModel)
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("AudioLibrary.GetAlbums")));

    QJsonObject paramObj;
    QJsonArray   properties;
    QJsonObject filter;

    filter.insert("artistid", QJsonValue(artistId));
    properties.prepend(QJsonValue(QString("title")));
    properties.prepend(QJsonValue(QString("artistid")));
    properties.prepend(QJsonValue(QString("description")));
    properties.prepend(QJsonValue(QString("genre")));
    properties.prepend(QJsonValue(QString("rating")));
    properties.prepend(QJsonValue(QString("thumbnail")));
    properties.prepend(QJsonValue(QString("year")));
    properties.prepend(QJsonValue(QString("mood")));

    paramObj.insert("filter", QJsonValue(filter));
    paramObj.insert("properties", QJsonValue(properties));

    requestJson.insert("params", QJsonValue(paramObj));
    requestJson.insert("id", QJsonValue(QString("albums")));
    this->increaseAsyncRequest();
    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_AUDIO, RETRIEVE_ALBUMS), dataModel);
}

void AudioLibrary::refreshAudioLibrary()
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("AudioLibrary.Scan")));

    // "ID IS TRANSMITTED BACK WITH RESPONSE TO IDENTITFY THE QUERY
    //    requestJson.insert("id", QJsonValue(QString("refresh")));
    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_AUDIO, REFRESH_AUDIO_LIBRARY));
}

void AudioLibrary::reloadDataModels()
{
    // MODELS ARE SAVED IN CASE THEY ARE STILL SYNCHRONOUS REQUESTS GOING ON
//    this->dirtyModelItem.append(this->albumsLibraryModel->takeRows());
//    this->dirtyModelItem.append(this->artistsLibraryModel->takeRows());
//    this->dirtyModelItem.append(this->songsLibraryModel->takeRows());

    this->retrieveAudioAlbums(this->albumsLibraryModel);
    this->retrieveAudioArtists(this->artistsLibraryModel);
    this->retrieveAllSongs(this->songsLibraryModel);
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
                        this->retrieveSongsForAlbum(album->id(), album->submodel());
                    }
                }
            }
        }
        this->decreaseAsyncRequest();
    }
}

void AudioLibrary::retrieveAudioArtistsCallBack(QNetworkReply *reply, void *data)
{
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
                        this->retrieveAlbumsForArtist(artist->id(), artist->submodel());
                    }
                }
            }
        }
        this->decreaseAsyncRequest();
    }
}

void AudioLibrary::retrieveSongsCallBack(QNetworkReply *reply, void *data)
{
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
                    else
                        qDebug() << "Song is NULL";
                }
            }
            else
            {
                qDebug() << "Not expected json song";
                qDebug() << jsonResponse.toJson();
            }
        }
        this->decreaseAsyncRequest();
    }
}

void AudioLibrary::refreshAudioLibraryCallBack(QNetworkReply *reply, void *data)
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
        qDebug() << "Parsing album";
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
        qDebug() << "Parsing artist";
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
        qDebug() << "Parsing song";
        SongModel *song = new SongModel(NULL, jsonSong.value("songid").toDouble());
        song->setAlbumId(jsonSong.value("albumid").toDouble());
        song->setArtistId(jsonSong.value("artistid").toArray().first().toDouble());
        song->setDuration(jsonSong.value("duration").toDouble());
        song->setRuntime(jsonSong.value("duration").toDouble());
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

void AudioLibrary::increaseAsyncRequest()
{
    this->m_asyncRequests++;
    emit asyncRequestChanged();
}

void AudioLibrary::decreaseAsyncRequest()
{
    this->m_asyncRequests--;
    emit asyncRequestChanged();
}

void AudioLibrary::checkForRemoval()
{
    if (this->m_asyncRequests == 0 && !this->dirtyModelItem.empty())
    {
        qDebug() << "Freeing Audio Models >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>..";
        foreach (QList<Models::ListItem *> dirtyList, this->dirtyModelItem)
        {
            qDebug() << "AUDIO ";
            qDebug() << "Items in list " << dirtyList.size();
//            while (!dirtyList.empty())
//                delete dirtyList.takeFirst();
        }
    }
}


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

#ifndef AUDIOLIBRARY_H
#define AUDIOLIBRARY_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QHash>
#include "IWebRequestDispatcher.h"
#include <SubListedListModel.h>
#include "AlbumModel.h"
#include "ArtistModel.h"
#include "SongModel.h"

#define MAJOR_ID_REQUEST_AUDIO 1
#define RETRIEVE_ALBUMS 0
#define RETRIEVE_ARTISTS 1
#define RETRIEVE_SONGS 2
#define REFRESH_AUDIO_LIBRARY 4

class AudioLibrary : public QObject, public IWebRequestDispatcher
{
    Q_OBJECT
public:
    AudioLibrary(QObject *parent = 0);

    int                       getMajorIDRequestHandled() const;
    void                      receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data);

    void                      retrieveAudioAlbums(Models::ListModel *dataModel);
    void                      retrieveAudioArtists(Models::ListModel *dataModel);
    void                      retrieveAllSongs(Models::ListModel *dataModel);
    void                      retrieveSongsForAlbum(int albumId, Models::ListModel *dataModel);
    void                      retrieveAlbumsForArtist(int artistId, Models::ListModel *dataModel);
    void                      refreshAudioLibrary();
    void                      reloadDataModels();

    Models::ListModel *       getArtistsLibraryModel() const;
    Models::ListModel *       getAlbumsLibraryModel() const;
    Models::ListModel *       getSongsLibraryModel() const;

private:

    QHash<int, void (AudioLibrary::*)(QNetworkReply *reply, void *data)> webCallBacks;

    Models::SubListedListModel  *artistsLibraryModel;
    Models::SubListedListModel  *albumsLibraryModel;
    Models::ListModel           *songsLibraryModel;
    Models::ListModel           *songsPlayListModel;

    void                     retrieveAudioAlbumsCallBack(QNetworkReply *reply, void *data);
    void                     retrieveAudioArtistsCallBack(QNetworkReply *reply, void *data);
    void                     retrieveSongsCallBack(QNetworkReply *reply, void *data);
    void                     refreshAudioLibraryCallBack(QNetworkReply *reply, void *data);

    QJsonObject              getSongsRequestBaseJSON();

   AlbumModel*               parseJsonAlbum(const QJsonObject & jsonAlbum);
   ArtistModel*              parseJsonArtist(const QJsonObject & jsonArtist);
   SongModel*                parseJsonSong(const QJsonObject & jsonSong);

   int                       m_asyncRequests;
   QList< QList<Models::ListItem *> > dirtyModelItem;

   void                      increaseAsyncRequest();
   void                      decreaseAsyncRequest();

private slots:
   void                      checkForRemoval();

signals:
    void                     performJsonRPCRequest(const QJsonObject &request, int requestId, void *data = NULL);
    void                     asyncRequestChanged();
};

#endif // AUDIOLIBRARY_H

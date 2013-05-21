#ifndef AUDIOLIBRARY_H
#define AUDIOLIBRARY_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QHash>
#include <IWebRequestDispatcher.h>

#define MAJOR_ID_REQUEST 1
#define RETRIEVE_ALBUMS 0
#define RETRIEVE_ARTISTS 1
#define RETRIEVE_SONGS 2

#define REQUEST_ID_BUILDER(id) ((MAJOR_ID_REQUEST * 10) + id)

class AudioLibrary : public QObject, public IWebRequestDispatcher
{
    Q_OBJECT
public:
    AudioLibrary(QObject *parent = 0);

    int                         getMajorIDRequestHandled() const;
    void                      receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data);

    void                      retrieveAudioAlbums();
    void                      retrieveAudioArtists();
    void                      retrieveSongs();

private:

    QHash<int, void (AudioLibrary::*)(QNetworkReply *reply, void *data)> webCallBacks;

    void                      retrieveAudioAlbumsCallBack(QNetworkReply *reply, void *data);
    void                      retrieveAudioArtistsCallBack(QNetworkReply *reply, void *data);
    void                      retrieveSongsCallBack(QNetworkReply *reply, void *data);

signals:
    void                      performJsonRPCRequest(const QJsonObject &request, int requestId, void *data = NULL);
};

#endif // AUDIOLIBRARY_H

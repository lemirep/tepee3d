#include "AudioLibrary.h"
#include <QDebug>

AudioLibrary::AudioLibrary(QObject *parent) : QObject(parent)
{
    this->webCallBacks[RETRIEVE_ALBUMS] = &AudioLibrary::retrieveAudioAlbumsCallBack;
    this->webCallBacks[RETRIEVE_ARTISTS] = &AudioLibrary::retrieveAudioArtistsCallBack;
    this->webCallBacks[RETRIEVE_SONGS] = &AudioLibrary::retrieveSongsCallBack;
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


void AudioLibrary::retrieveAudioAlbums()
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("AudioLibrary.GetAlbums")));

    QJsonObject paramObj;
    QJsonArray   properties;
    QJsonObject limitObj;
    QJsonObject sortObj;

    limitObj.insert("start", QJsonValue(0));
    limitObj.insert("end", QJsonValue(75));

    properties.prepend(QJsonValue(QString("playcount")));
    properties.prepend(QJsonValue(QString("artist")));
    properties.prepend(QJsonValue(QString("genre")));
    properties.prepend(QJsonValue(QString("rating")));
    properties.prepend(QJsonValue(QString("thumbnail")));
    properties.prepend(QJsonValue(QString("year")));
    properties.prepend(QJsonValue(QString("mood")));
    properties.prepend(QJsonValue(QString("style")));

    sortObj.insert("order", QJsonValue(QString("ascending")));
    paramObj.insert("properties", QJsonValue(properties));
    paramObj.insert("sort", QJsonValue(sortObj));

    requestJson.insert("params", QJsonValue(paramObj));
    requestJson.insert("id", QJsonValue(QString("libalbum")));

    sortObj.insert("method",QJsonValue(QString("album")));
    sortObj.insert("ignorearticle", QJsonValue(true));

    paramObj.insert("limits", QJsonValue(limitObj));

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(RETRIEVE_ALBUMS));
}

void AudioLibrary::retrieveAudioArtists()
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("AudioLibrary.GetArtists")));

    QJsonObject paramObj;
    QJsonArray   properties;
    QJsonObject limitObj;
    QJsonObject sortObj;

    limitObj.insert("start", QJsonValue(0));
    limitObj.insert("end", QJsonValue(75));

    properties.prepend(QJsonValue(QString("thumbnail")));
    properties.prepend(QJsonValue(QString("fanart")));
    properties.prepend(QJsonValue(QString("born")));
    properties.prepend(QJsonValue(QString("formed")));
    properties.prepend(QJsonValue(QString("died")));
    properties.prepend(QJsonValue(QString("disbanded")));
    properties.prepend(QJsonValue(QString("yearsactive")));
    properties.prepend(QJsonValue(QString("mood")));
    properties.prepend(QJsonValue(QString("style")));
    properties.prepend(QJsonValue(QString("genre")));

    sortObj.insert("order", QJsonValue(QString("ascending")));
    paramObj.insert("properties", QJsonValue(properties));
    paramObj.insert("sort", QJsonValue(sortObj));

    requestJson.insert("params", QJsonValue(paramObj));
    requestJson.insert("id", QJsonValue(1));

    sortObj.insert("method",QJsonValue(QString("artist")));
    sortObj.insert("ignorearticle", QJsonValue(true));

    paramObj.insert("limits", QJsonValue(limitObj));

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(RETRIEVE_ARTISTS));
}

void AudioLibrary::retrieveSongs()
{
}

void AudioLibrary::retrieveAudioAlbumsCallBack(QNetworkReply *reply, void *data)
{
    qDebug() << "Receiving Request Result Albums";
    // PARSE JSON RESULT HERE
}

void AudioLibrary::retrieveAudioArtistsCallBack(QNetworkReply *reply, void *data)
{
    qDebug() << "Receiving Request Artists";
}

void AudioLibrary::retrieveSongsCallBack(QNetworkReply *reply, void *data)
{
    // PARSEW JSON RESULT HERE
}

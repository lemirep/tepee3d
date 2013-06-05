#include "PlayerManager.h"
#include <QDebug>

PlayerManager::PlayerManager(QObject *parent) : QObject(parent)
{
    this->webCallBacks[GENERIC_CALLBACK] = &PlayerManager::genericCallBack;
    this->webCallBacks[GET_ACTIVE_PLAYERS] = &PlayerManager::getActivesPlayersCallBack;
    this->webCallBacks[GET_PLAYED_ITEM] = &PlayerManager::getCurrentlyPlayerItemCallBack;
}

void PlayerManager::getActivesPlayers()
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("Player.GetActivePlayers")));
    requestJson.insert("id", QJsonValue(1));

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_PLAYER, GET_ACTIVE_PLAYERS));
}

void PlayerManager::playFile(const QString &file)
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("Player.Open")));

    QJsonObject paramObj;
    QJsonObject fileObj;

    fileObj.insert("file", QJsonValue(file));
    paramObj.insert("item", QJsonValue(fileObj));
    requestJson.insert("params", QJsonValue(paramObj));

    qDebug() << QJsonDocument(requestJson).toJson();

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_PLAYER, GENERIC_CALLBACK));
}

void PlayerManager::addToPlayList(const QString &file)
{

}

void PlayerManager::pause_resumeCurrentPlayer(int playerId)
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("Player.PlayPause")));
    requestJson.insert("id", QJsonValue(1));

    QJsonObject paramObj;
    paramObj.insert("playerid", QJsonValue(playerId));
    requestJson.insert("params", QJsonValue(paramObj));

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_PLAYER, GENERIC_CALLBACK));
}

void PlayerManager::playNext(int playerId)
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("Player.Player.GoNext")));
    requestJson.insert("id", QJsonValue(1));

    QJsonObject paramObj;
    paramObj.insert("playerid", QJsonValue(playerId));
    requestJson.insert("params", QJsonValue(paramObj));

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_PLAYER, GENERIC_CALLBACK));
}

void PlayerManager::playPrevious(int playerId)
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("Player.GoPrevious")));
    requestJson.insert("id", QJsonValue(1));

    QJsonObject paramObj;
    paramObj.insert("playerid", QJsonValue(playerId));
    requestJson.insert("params", QJsonValue(paramObj));

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_PLAYER, GENERIC_CALLBACK));
}

void PlayerManager::stopCurrentPlayer(int playerId)
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("Player.Stop")));
    requestJson.insert("id", QJsonValue(1));

    QJsonObject paramObj;
    paramObj.insert("playerid", QJsonValue(playerId));
    requestJson.insert("params", QJsonValue(paramObj));

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_PLAYER, GENERIC_CALLBACK));
}

void PlayerManager::seekCurrentPlayer(int advance)
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("Player.Seek")));
    requestJson.insert("id", QJsonValue(1));

    QJsonObject paramObj;
    paramObj.insert("playerid", QJsonValue(0));
    paramObj.insert("value", QJsonValue(advance));
    requestJson.insert("params", QJsonValue(paramObj));

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_PLAYER, GENERIC_CALLBACK));

}

void PlayerManager::getCurrentlyPlayerItem()
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("Player.GetItem")));
    requestJson.insert("id", QJsonValue(1));

    QJsonObject paramObj;
    QJsonArray properties;

    properties.prepend(QJsonValue(QString("title")));
    properties.prepend(QJsonValue(QString("artist")));
    properties.prepend(QJsonValue(QString("thumbnail")));
    properties.prepend(QJsonValue(QString("runtime")));
    properties.prepend(QJsonValue(QString("duration")));
    properties.prepend(QJsonValue(QString("endtime")));
    properties.prepend(QJsonValue(QString("year")));
    properties.prepend(QJsonValue(QString("genre")));
    properties.prepend(QJsonValue(QString("file")));
    properties.prepend(QJsonValue(QString("rating")));
    paramObj.insert("playerid", QJsonValue(0));
    paramObj.insert("properties", QJsonValue(properties));
    requestJson.insert("params", QJsonValue(paramObj));

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_PLAYER, GENERIC_CALLBACK));
}

int PlayerManager::getMajorIDRequestHandled() const
{
    return MAJOR_ID_REQUEST_PLAYER;
}

void PlayerManager::receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data)
{
    (this->*this->webCallBacks[id])(reply, data);
}


void PlayerManager::genericCallBack(QNetworkReply *reply, void *data)
{
    if (reply != NULL)
    {
        qDebug() << "Reply -> " << reply->readAll();
    }
}

void PlayerManager::getActivesPlayersCallBack(QNetworkReply *reply, void *data)
{
    if (reply != NULL)
    {
        qDebug() << "Reply -> " << reply->readAll();
    }
}

void PlayerManager::getCurrentlyPlayerItemCallBack(QNetworkReply *reply, void *data)
{

}

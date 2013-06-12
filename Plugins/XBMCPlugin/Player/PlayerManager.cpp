#include "PlayerManager.h"
#include <QDebug>

PlayerManager::PlayerManager(QObject *parent) : QObject(parent)
{
    this->webCallBacks[GENERIC_CALLBACK] = &PlayerManager::genericCallBack;
    this->webCallBacks[GET_ACTIVE_PLAYERS] = &PlayerManager::getActivesPlayersCallBack;
    this->webCallBacks[GET_PLAYED_ITEM] = &PlayerManager::getCurrentlyPlayerItemCallBack;
    this->currentActivePlayer = -1;
//    this->currentlyPlayerItems = new Models::ListModel(new PlayableItemModel());
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
    this->getActivesPlayers();
}

void PlayerManager::addToPlayList(const QString &file)
{

}

void PlayerManager::pause_resumeCurrentPlayer()
{
    if (this->currentActivePlayer == -1)
    {
        this->playerActionQueue.append(&PlayerManager::pause_resumeCurrentPlayer);
        this->getActivesPlayers();
        return ;
    }
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("Player.PlayPause")));

    QJsonObject paramObj;
    paramObj.insert("playerid", QJsonValue(this->currentActivePlayer));
    requestJson.insert("id", QJsonValue(1));
    requestJson.insert("params", QJsonValue(paramObj));

    qDebug() << QJsonDocument(requestJson).toJson();

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_PLAYER, GENERIC_CALLBACK));
}

void PlayerManager::playNext()
{
    if (this->currentActivePlayer == -1)
    {
        this->playerActionQueue.append(&PlayerManager::playNext);
        this->getActivesPlayers();
        return ;
    }
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("Player.GoNext")));

    QJsonObject paramObj;
    paramObj.insert("playerid", QJsonValue(this->currentActivePlayer));
    requestJson.insert("params", QJsonValue(paramObj));
    requestJson.insert("id", QJsonValue(1));

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_PLAYER, GENERIC_CALLBACK));
}

void PlayerManager::playPrevious()
{
    if (this->currentActivePlayer == -1)
    {
        this->playerActionQueue.append(&PlayerManager::playPrevious);
        this->getActivesPlayers();
        return ;
    }
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("Player.GoPrevious")));

    QJsonObject paramObj;
    paramObj.insert("playerid", QJsonValue(this->currentActivePlayer));
    requestJson.insert("params", QJsonValue(paramObj));
    requestJson.insert("id", QJsonValue(1));

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_PLAYER, GENERIC_CALLBACK));
}

void PlayerManager::stopCurrentPlayer()
{
    if (this->currentActivePlayer == -1)
    {
        this->playerActionQueue.append(&PlayerManager::stopCurrentPlayer);
        this->getActivesPlayers();
        return ;
    }
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("Player.Stop")));

    QJsonObject paramObj;
    paramObj.insert("playerid", QJsonValue(this->currentActivePlayer));
    requestJson.insert("params", QJsonValue(paramObj));
    requestJson.insert("id", QJsonValue(1));

    this->getCurrentlyPlayedItem();
    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_PLAYER, GENERIC_CALLBACK));

}

void PlayerManager::seekCurrentPlayer(int advance)
{
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("Player.Seek")));

    QJsonObject paramObj;
    paramObj.insert("playerid", QJsonValue(this->currentActivePlayer));
    paramObj.insert("value", QJsonValue(advance));
    requestJson.insert("params", QJsonValue(paramObj));
    requestJson.insert("id", QJsonValue(1));

    qDebug() << QJsonDocument(requestJson).toJson();

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_PLAYER, GENERIC_CALLBACK));
}

void PlayerManager::getCurrentlyPlayedItem()
{
    if (this->currentActivePlayer == -1)
    {
        this->playerActionQueue.append(&PlayerManager::getCurrentlyPlayedItem);
        this->getActivesPlayers();
        return ;
    }
    QJsonObject requestJson;
    requestJson.insert("jsonrpc", QJsonValue(QString("2.0")));
    requestJson.insert("method", QJsonValue(QString("Player.GetItem")));

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
    paramObj.insert("playerid", QJsonValue(this->currentActivePlayer));
    paramObj.insert("properties", QJsonValue(properties));
    requestJson.insert("params", QJsonValue(paramObj));
    requestJson.insert("id", QJsonValue(1));

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

Models::ListModel* PlayerManager::getCurrentlyPlayedItemModel() const
{
    return this->currentlyPlayerItems;
}

PlayableItemModel *PlayerManager::playableItemModelFromType(QString type)
{
    if (type.compare("movie") == 0)
        return new MovieModel();
    else if (type.compare("music") == 0)
        return new SongModel();
    else if (type.compare("show") == 0)
        return new TVShowEpisodeModel();
    else
        return NULL;
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
    Q_UNUSED(data)
    if (reply != NULL)
    {
        QJsonDocument jsonRep = QJsonDocument::fromJson(reply->readAll());
        if  (!jsonRep.isNull() &&
             !jsonRep.isEmpty() &&
             jsonRep.isObject() &&
             jsonRep.object().value("result").isArray() &&
             jsonRep.object().value("result").toArray().first().isObject())
        {
            this->currentActivePlayer = jsonRep.object().value("result").toArray().first().toObject().value("playerid").toDouble();
            while (!this->playerActionQueue.empty())
                (this->*this->playerActionQueue.takeFirst())();
            this->getCurrentlyPlayedItem();
        }
    }
}

void PlayerManager::getCurrentlyPlayerItemCallBack(QNetworkReply *reply, void *data)
{
    Q_UNUSED(data)
    if (reply != NULL)
    {
        QJsonDocument jsonRep = QJsonDocument::fromJson(reply->readAll());
        if  (!jsonRep.isNull() &&
             !jsonRep.isEmpty() &&
             jsonRep.isObject() &&
             jsonRep.object().value("result").isObject())
        {
            this->currentlyPlayerItems->clear();
            QJsonObject item = jsonRep.object().value("result").toObject().value("item").toObject();
            PlayableItemModel *playableItem = this->playableItemModelFromType(item.value("type").toString());
            if (playableItem != NULL)
            {
                playableItem->setFile(item.value("file").toString());
                playableItem->setTitle(item.value("title").toString());
                playableItem->setRating(item.value("rating").toDouble());
                playableItem->setThumbnail(item.value("thumbnail").toString());
                this->currentlyPlayerItems->appendRow(playableItem);
            }
        }
    }
}

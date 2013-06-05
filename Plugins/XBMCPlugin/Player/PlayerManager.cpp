#include "PlayerManager.h"
#include <QDebug>

PlayerManager::PlayerManager(QObject *parent) : QObject(parent)
{
    this->webCallBacks[PLAY_MEDIA_CALLBACK] = &PlayerManager::playFileCallBack;
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
    requestJson.insert("params", QJsonValue(requestJson));

    emit performJsonRPCRequest(requestJson, REQUEST_ID_BUILDER(MAJOR_ID_REQUEST_PLAYER, PLAY_MEDIA_CALLBACK));
}

void PlayerManager::addToPlayList(const QString &file)
{

}

void PlayerManager::pauseCurrentPlayer()
{

}

void PlayerManager::resumeCurrentPlayer()
{

}

void PlayerManager::playNext()
{

}

void PlayerManager::playPrevious()
{

}

int PlayerManager::getMajorIDRequestHandled() const
{
    return MAJOR_ID_REQUEST_PLAYER;
}

void PlayerManager::receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data)
{
    (this->*this->webCallBacks[id])(reply, data);
}


void PlayerManager::playFileCallBack(QNetworkReply *reply, void *data)
{
    if (reply != NULL)
    {
        qDebug() << "Reply -> " << reply->readAll();
    }
}

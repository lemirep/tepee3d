#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QList>
#include "IWebRequestDispatcher.h"

#define MAJOR_ID_REQUEST_PLAYER 2
#define GENERIC_CALLBACK 0
#define GET_ACTIVE_PLAYERS 1

class PlayerManager : public QObject, public IWebRequestDispatcher
{
    Q_OBJECT
public:
    PlayerManager(QObject *parent = 0);

    void                    getActivesPlayers();
    void                    playFile(const QString &file);
    void                    addToPlayList(const QString &file);

    void                    pause_resumeCurrentPlayer(int playerId = 0);
    void                    playNext(int playerId = 0);
    void                    playPrevious(int playerId = 0);
    void                    stopCurrentPlayer(int playerId = 0);
    void                    seekCurrentPlayer(int advance);

    int                     getMajorIDRequestHandled() const;
    void                    receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data);


    class                   PlayerEntity
    {
    public:
        enum PlayerType
        {
            Audio = 0,
            Video,
            Picture
        };

        int                 playerId;
        PlayerType          playerType;
    };

private:
    QHash<int, void (PlayerManager::*)(QNetworkReply *reply, void *data)>   webCallBacks;
    QList<PlayerEntity>     activePlayers;
private:
    void                    genericCallBack(QNetworkReply *reply, void *data);
    void                    getActivesPlayersCallBack(QNetworkReply *reply, void *data);

signals:
    void                    performJsonRPCRequest(const QJsonObject &request, int requestId, void *data = NULL);
};

#endif // PLAYERMANAGER_H

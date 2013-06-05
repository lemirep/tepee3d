#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include "IWebRequestDispatcher.h"

#define MAJOR_ID_REQUEST_PLAYER 2
#define PLAY_MEDIA_CALLBACK 0

class PlayerManager : public QObject, public IWebRequestDispatcher
{
    Q_OBJECT
public:
    PlayerManager(QObject *parent = 0);

    void                    playFile(const QString &file);
    void                    addToPlayList(const QString &file);

    void                    pauseCurrentPlayer();
    void                    resumeCurrentPlayer();
    void                    playNext();
    void                    playPrevious();


    int                     getMajorIDRequestHandled() const;
    void                    receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data);


private:
    QHash<int, void (PlayerManager::*)(QNetworkReply *reply, void *data)>   webCallBacks;

private:
    void                    playFileCallBack(QNetworkReply *reply, void *data);

signals:
    void                    performJsonRPCRequest(const QJsonObject &request, int requestId, void *data = NULL);
};

#endif // PLAYERMANAGER_H

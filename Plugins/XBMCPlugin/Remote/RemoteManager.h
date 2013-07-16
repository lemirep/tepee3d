#ifndef REMOTEMANAGER_H
#define REMOTEMANAGER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonValue>
#include <IWebRequestDispatcher.h>
#include <QDebug>

#define MAJOR_ID_REQUEST_REMOTE 3
#define KEY_PRESSED 0


class RemoteManager : public QObject, public IWebRequestDispatcher
{
    Q_OBJECT
public:
    // REMOTE CONTROL ACTIONS
    enum NavigationKeys
    {
        Up = 0,
        Down,
        Left,
        Right,
        Back,
        Select,
        Home
    };
public:
    RemoteManager(QObject *parent = 0);
    ~RemoteManager();

    void            receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data);
    int             getMajorIDRequestHandled() const;

    void            moveKey(NavigationKeys key);

    void            rebootSystem();
    void            shutdownSystem();
    void            suspendSystem();
    void            hibernateSystem();



private:
    QHash<NavigationKeys, QString>   webServiceMethods;
    void            moveKeyCallBack(QNetworkReply *reply);
signals:
    void            performJsonRPCRequest(const QJsonObject &request, int requestId, void *data = NULL);
};

#endif // REMOTEMANAGER_H

#ifndef REMOTEMANAGER_H
#define REMOTEMANAGER_H

#include <QObject>
#include <IWebRequestDispatcher.h>

#define MAJOR_ID_REQUEST 3
#define REQUEST_ID_BUILDER(id) ((MAJOR_ID_REQUEST * 10) + id)


class RemoteManager : public QObject, public IWebRequestDispatcher
{
    Q_OBJECT
public:
    RemoteManager(QObject *parent);
    ~RemoteManager();

    void    receiveResultFromHttpRequest(QNetworkReply *reply, int id, void *data);
    int       getMajorIDRequestHandled() const;

    void    moveKey();
};

#endif // REMOTEMANAGER_H

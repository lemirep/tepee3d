#ifndef STREAMMANAGERLIBRARY_H
#define STREAMMANAGERLIBRARY_H

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "ServiceInterface.h"
#include "StreamServiceUserInterface.h"

#define SERVICE_ID 4
#define SERVICE_VERSION "1.0.0"

class StreamManagerLibrary :  public QObject, Services::ServiceInterface
{
    Q_OBJECT
    Q_INTERFACES(Services::ServiceInterface)
    Q_PLUGIN_METADATA(IID "com.tepee3d.Services.streamservice")
public:
    StreamManagerLibrary();

    int                     getServiceId() const;
    void                    initLibraryConnection(QObject *parent);
    bool                    connectServiceToUser(QObject *user);
    bool                    disconnectServiceFromUser(QObject *user);
    QObject*                getLibraryQObject();
    QString                 getServiceVersion() const;
private slots:
    void executeStreamRequest(QNetworkRequest request, int requestType,
                            QDataStream *stream, QObject *sender, int requestId, void *data);
private:
    static  QNetworkAccessManager*  instance;
    QNetworkAccessManager*  getInstance();
signals:
    void initialized();
};

#endif // STREAMMANAGERLIBRARY_H

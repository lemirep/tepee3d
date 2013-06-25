#ifndef FILEDOWNLOADLIBRARY_H
#define FILEDOWNLOADERLIBRARY_H

#include <QDebug>
#include <QList>
#include <QNetworkAccessManager>
#include "FileDownloadJob.h"
#include "ServiceInterface.h"

#define SERVICE_ID 4
#define SERVICE_VERSION "1.0.0"

class FileDownloaderLibrary :  public QObject, Services::ServiceInterface
{
    Q_OBJECT
    Q_INTERFACES(Services::ServiceInterface)
    Q_PLUGIN_METADATA(IID "com.tepee3d.Services.filedownloaderservice")
public:
    FileDownloaderLibrary();
    ~FileDownloaderLibrary();

    int                     getServiceId() const;
    void                    initLibraryConnection(QObject *parent);
    bool                    connectServiceToUser(QObject *user);
    bool                    disconnectServiceFromUser(QObject *user);
    QObject*                getLibraryQObject();
    QString                 getServiceVersion() const;

private :

    void                    executeFileDownload(FileDownloadJob *job,
                                                const QNetworkRequest &request,
                                                Services::FileDownloaderServiceUserInterface::FileDownloadRequestType type,
                                                QHttpMultiPart *multiPart);

private slots:
    void                    executeFileDownloader(const QNetworkRequest&,
                               Services::FileDownloaderServiceUserInterface::FileDownloadRequestType,
                               QHttpMultiPart *multiPart,
                               QFile &,
                               QObject* sender,
                               int requestId,
                               void *data);

private:
    static  QNetworkAccessManager*  instance;
    QNetworkAccessManager*  getInstance();

    bool                     downloadInProgress;


signals:
    void initialized();
};

#endif // FILEDOWNLOADERLIBRARY_H

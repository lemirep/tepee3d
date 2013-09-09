#ifndef FILEDOWNLOADERSERVICEUSERINTERFACE_H
#define FILEDOWNLOADERSERVICEUSERINTERFACE_H

#include <QPointer>
#include <QFile>

namespace Services
{
class   FileDownloaderServiceUserInterface
{
public :
    enum FileDownloadRequestType{Get = 1, Post, Delete, Put};
    virtual void onDownloadFinished(QPointer<QFile>, int requestId, QPointer<QObject> data) = 0;
    virtual void onDownloadProgress(QPointer<QFile>, int progress, int requestId, QPointer<QObject> data) = 0;
    virtual void onDownloadStarted(QPointer<QFile>, int requestId, QPointer<QObject> data) = 0;
    virtual void onDownloadError(QPointer<QFile>, int requestId, QPointer<QObject> data) = 0;
    // SIGNAL
    //void executeFileDownloader(const QNetworkRequest&,
    //                           Services::FileDownloaderServiceUserInterface::FileDownloadRequestType,
    //                           QHttpMultiPart *multiPart,
    //                           QPointer<QFile> ,
    //                           QPointer<QObject> sender,
    //                           int requestId,
    //                           QPointer<QObject> data);
};
}
Q_DECLARE_INTERFACE(Services::FileDownloaderServiceUserInterface, "com.tepee3d.Services.FileDownloaderServiceUserInterface/1.0")



#endif // FILEDOWNLOADERSERVICEUSERINTERFACE_H

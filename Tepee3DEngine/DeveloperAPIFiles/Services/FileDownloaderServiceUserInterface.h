#ifndef FILEDOWNLOADERSERVICEUSERINTERFACE_H
#define FILEDOWNLOADERSERVICEUSERINTERFACE_H

#include <QFile>

namespace Services
{
class   FileDownloaderServiceUserInterface
{
public :
    enum FileDownloadRequestType{Get = 1, Post, Delete, Put};
    virtual void onDownloadFinished(QFile *, int requestId, void *data) = 0;
    virtual void onDownloadProgress(QFile *, int progress, int requestId, void *data) = 0;
    virtual void onDownloadStarted(QFile *, int requestId, void *data) = 0;
    virtual void onDownloadError(QFile *, int requestId, void *data) = 0;
    // SIGNAL
    //void executeFileDownloader(const QNetworkRequest&,
    //                           Services::FileDownloaderServiceUserInterface::FileDownloadRequestType,
    //                           QHttpMultiPart *multiPart,
    //                           QFile *,
    //                           QObject* sender,
    //                           int requestId,
    //                           void *data);
};
}
Q_DECLARE_INTERFACE(Services::FileDownloaderServiceUserInterface, "com.tepee3d.Services.FileDownloaderServiceUserInterface/1.0")



#endif // FILEDOWNLOADERSERVICEUSERINTERFACE_H

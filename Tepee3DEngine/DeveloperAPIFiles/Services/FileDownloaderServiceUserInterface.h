#ifndef FILEDOWNLOADERSERVICEUSERINTERFACE_H
#define FILEDOWNLOADERSERVICEUSERINTERFACE_H

#include <QPointer>
#include <QFile>
#include <QHttpMultiPart>
#include <QNetworkRequest>

namespace Services
{
class   FileDownloaderServiceUserInterface
{
public :
    enum FileDownloadRequestType{Get = 1, Post, Delete, Put};
    virtual void onDownloadFinished(QPointer<QFile> file, int requestId, QPointer<QObject> data) = 0;
    virtual void onDownloadProgress(QPointer<QFile> file, int progress, int requestId, QPointer<QObject> data) = 0;
    virtual void onDownloadStarted(QPointer<QFile> file, int requestId, QPointer<QObject> data) = 0;
    virtual void onDownloadError(QPointer<QFile> file, int requestId, QPointer<QObject> data) = 0;
    // SIGNAL
    //void executeFileDownloader(const QNetworkRequest&,
    //                           Services::FileDownloaderServiceUserInterface::FileDownloadRequestType,
    //                           QHttpMultiPart *,
    //                           QPointer<QFile> ,
    //                           QPointer<QObject>,
    //                           int ,
    //                           QPointer<QObject>);
};
}
Q_DECLARE_INTERFACE(Services::FileDownloaderServiceUserInterface, "com.tepee3d.Services.FileDownloaderServiceUserInterface/1.0")



#endif // FILEDOWNLOADERSERVICEUSERINTERFACE_H

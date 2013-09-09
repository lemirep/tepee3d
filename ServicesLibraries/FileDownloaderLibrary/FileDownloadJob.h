#ifndef FILEDOWNLOADJOB_H
#define FILEDOWNLOADJOB_H

#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include "FileDownloaderServiceUserInterface.h"

class FileDownloadJob : public QObject
{
    Q_OBJECT
public :
    FileDownloadJob(QPointer<QFile> file,
                    int   requestId,
                    QPointer<QObject> data,
                    QPointer<QObject> sender);
    ~FileDownloadJob();

    QNetworkReply *getReply() const;
    void setReply(QNetworkReply *value);

private :
    QPointer<QFile> file;
    int requestId;
    QPointer<QObject> data;
    QPointer<QObject> sender;
    QNetworkReply *reply;

public :

    void    abort();
    void    downloadStarted();

public slots:

    void onProgress(qint64, qint64);
    void onError(QNetworkReply::NetworkError);
    void onFinished();
    void onReadReady();
};
#endif // FILEDOWNLOADJOB_H

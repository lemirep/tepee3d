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
    FileDownloadJob(QFile &file,
                    int   requestId,
                    void  *data,
                    QObject* sender);
    ~FileDownloadJob();

    QNetworkReply *getReply() const;
    void setReply(QNetworkReply *value);

private :
    QFile& file;
    int requestId;
    void *data;
    QObject *sender;
    QNetworkReply *reply;

public :

    void    abort();
    void    downloadStarted();

public slots:

    void onProgress(int received, int total);
    void onError(QNetworkReply::NetworkError);
    void onFinished();
    void onReadReady();
};
#endif // FILEDOWNLOADJOB_H

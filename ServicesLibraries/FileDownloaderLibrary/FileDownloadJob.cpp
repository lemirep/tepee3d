#include "FileDownloadJob.h"

FileDownloadJob::FileDownloadJob(QFile &file,
                                 int requestId,
                                 void *data,
                                 QObject *sender):
    file(file),
    requestId(requestId),
    data(data),
    sender(sender)
{
    this->reply = NULL;
    qDebug() << "File downloadJob instanciated";
}


FileDownloadJob::~FileDownloadJob()
{
    this->abort();
    if (this->reply != NULL)
        delete this->reply;
}

void    FileDownloadJob::abort()
{
    if (this->reply != NULL && this->reply->isRunning())
        this->reply->abort();
}

void    FileDownloadJob::downloadStarted()
{
    qDebug() << "Starting download";
    Services::FileDownloaderServiceUserInterface *fileDowloaderInterface = qobject_cast<Services::FileDownloaderServiceUserInterface *>(this->sender);
    if (fileDowloaderInterface != NULL)
        fileDowloaderInterface->onDownloadStarted(this->file, this->requestId, this->data);
}

void    FileDownloadJob::onProgress(qint64 received, qint64 total)
{
    Services::FileDownloaderServiceUserInterface *fileDowloaderInterface = qobject_cast<Services::FileDownloaderServiceUserInterface *>(this->sender);
    if (fileDowloaderInterface != NULL)
        fileDowloaderInterface->onDownloadProgress(this->file, (double)received / total * 100, this->requestId, this->data);
}

void    FileDownloadJob::onError(QNetworkReply::NetworkError error)
{
    Services::FileDownloaderServiceUserInterface *fileDowloaderInterface = qobject_cast<Services::FileDownloaderServiceUserInterface *>(this->sender);
    qWarning() << "Error number : " << error << " : " << reply->errorString();
    if (fileDowloaderInterface != NULL)
        fileDowloaderInterface->onDownloadError(this->file, this->requestId, this->data);
}

void    FileDownloadJob::onFinished()
{
    Services::FileDownloaderServiceUserInterface *fileDowloaderInterface = qobject_cast<Services::FileDownloaderServiceUserInterface *>(this->sender);
    if (fileDowloaderInterface != NULL)
        fileDowloaderInterface->onDownloadFinished(this->file, this->requestId, this->data);
    // DESTROYS THE OBJECT
    delete this;
}

void    FileDownloadJob::onReadReady()
{

    const int readBuffSize = 256;
    char buff[readBuffSize];
    int read = 0;
    memset(buff, 0,readBuffSize);
    while ((read = this->reply->read(buff, readBuffSize)) > 0)
        this->file.write(buff, read);
}

QNetworkReply *FileDownloadJob::getReply() const
{
    return this->reply;
}

void FileDownloadJob::setReply(QNetworkReply *value)
{
    this->reply = value;
}

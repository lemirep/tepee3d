#include "FileDownloadJob.h"

FileDownloadJob::FileDownloadJob(QPointer<QFile> file,
                                 int requestId,
                                 QPointer<QObject> data,
                                 QPointer<QObject> sender):
    file(file),
    requestId(requestId),
    data(data),
    sender(sender)
{
    this->reply = NULL;
    qDebug() << "File downloadJob instanciated " << file->fileName();
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
    if (this->sender.isNull())
        return ;
    Services::FileDownloaderServiceUserInterface *fileDowloaderInterface = qobject_cast<Services::FileDownloaderServiceUserInterface *>(this->sender.data());
    if (fileDowloaderInterface != NULL)
        fileDowloaderInterface->onDownloadStarted(this->file, this->requestId, this->data);
}

void    FileDownloadJob::onProgress(qint64 received, qint64 total)
{
    if (this->sender.isNull())
        return ;
    Services::FileDownloaderServiceUserInterface *fileDowloaderInterface = qobject_cast<Services::FileDownloaderServiceUserInterface *>(this->sender.data());
    if (fileDowloaderInterface != NULL)
        fileDowloaderInterface->onDownloadProgress(this->file, (double)received / total * 100, this->requestId, this->data);
}

void    FileDownloadJob::onError(QNetworkReply::NetworkError error)
{
    if (this->sender.isNull())
        return ;
    Services::FileDownloaderServiceUserInterface *fileDowloaderInterface = qobject_cast<Services::FileDownloaderServiceUserInterface *>(this->sender.data());
    qWarning() << "Error number : " << error << " : " << reply->errorString();
    if (fileDowloaderInterface != NULL)
        fileDowloaderInterface->onDownloadError(this->file, this->requestId, this->data);
}

void    FileDownloadJob::onFinished()
{
    if (this->sender.isNull())
        return ;
    Services::FileDownloaderServiceUserInterface *fileDowloaderInterface = qobject_cast<Services::FileDownloaderServiceUserInterface *>(this->sender.data());
    if (fileDowloaderInterface != NULL)
        fileDowloaderInterface->onDownloadFinished(this->file, this->requestId, this->data);
    // DESTROYS THE OBJECT
    delete this;
}

void    FileDownloadJob::onReadReady()
{
    if (this->file.isNull())
        return ;
    qDebug() << "READING FILE DOWNLOAD";
    const int readBuffSize = 256;
    char buff[readBuffSize];
    int read = 0;
    memset(buff, 0,readBuffSize);
    while ((read = this->reply->read(buff, readBuffSize)) > 0)
        this->file->write(buff, read);
    this->file->flush();
}

QNetworkReply *FileDownloadJob::getReply() const
{
    return this->reply;
}

void FileDownloadJob::setReply(QNetworkReply *value)
{
    this->reply = value;
}

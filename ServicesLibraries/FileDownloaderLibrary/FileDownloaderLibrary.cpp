#include "FileDownloaderLibrary.h"

FileDownloaderLibrary::FileDownloaderLibrary() : QObject()
{
    this->downloadInProgress = false;
}

FileDownloaderLibrary::~FileDownloaderLibrary()
{
    if (FileDownloaderLibrary::instance != NULL)
    {
        delete FileDownloaderLibrary::instance;
        FileDownloaderLibrary::instance = NULL;
    }
}

QNetworkAccessManager*  FileDownloaderLibrary::getInstance()
{
    if (instance == NULL)
        instance = new QNetworkAccessManager();
    return instance;
}

bool  FileDownloaderLibrary::connectServiceToUser(QObject *user)
{
    qDebug() << "Connecting user to FileDownloaderServices";
    if (qobject_cast<Services::FileDownloaderServiceUserInterface*>(user) != NULL)
        return QObject::connect(user, SIGNAL(executeFileDownloader(const QNetworkRequest&,
                                                                   Services::FileDownloaderServiceUserInterface::FileDownloadRequestType,
                                                                   QHttpMultiPart *,
                                                                   QFile &,
                                                                   QObject*,
                                                                   int,
                                                                   void *)),
                                this, SLOT(executeFileDownloader(const QNetworkRequest&,
                                                                 Services::FileDownloaderServiceUserInterface::FileDownloadRequestType,
                                                                 QHttpMultiPart *,
                                                                 QFile &,
                                                                 QObject* ,
                                                                 int ,
                                                                 void *)));
    qWarning() << "Object does not implement FileDownloaderServiceUserInterface";
    return false;
}

/*!
 * Unsubscribes a \a user from the service.
 */
bool  FileDownloaderLibrary::disconnectServiceFromUser(QObject *user)
{
    if (qobject_cast<Services::FileDownloaderServiceUserInterface*>(user) != NULL)
        return QObject::disconnect(user, SIGNAL(executeFileDownloader(const QNetworkRequest&,
                                                                      Services::FileDownloaderServiceUserInterface::FileDownloadRequestType,
                                                                      QHttpMultiPart *multiPart,
                                                                      QFile &,
                                                                      QObject* sender,
                                                                      int requestId,
                                                                      void *data)),
                                   this, SLOT(executeFileDownloader(const QNetworkRequest&,
                                                                    Services::FileDownloaderServiceUserInterface::FileDownloadRequestType,
                                                                    QHttpMultiPart *multiPart,
                                                                    QFile &,
                                                                    QObject* sender,
                                                                    int requestId,
                                                                    void *data)));
    qWarning() << "Object does not implement FileDownloaderServiceUserInterface";
    return false;
}


int FileDownloaderLibrary::getServiceId() const
{
    return SERVICE_ID;
}

/*!
 * Initializes library signal connection with \a parent.
 */
void            FileDownloaderLibrary::initLibraryConnection(QObject *parent)
{
    QObject::connect(this, SIGNAL(initialized()), parent, SLOT(libraryInitialized()));
    emit (initialized());
}



/*!
 * Return the QObject instance of the library so that it can easily be connected to signals
 * and slots.
 */
QObject*        FileDownloaderLibrary::getLibraryQObject()
{
    return this;
}

QString FileDownloaderLibrary::getServiceVersion() const
{
    return SERVICE_VERSION;
}

void FileDownloaderLibrary::executeFileDownload(FileDownloadJob *currentJob, const QNetworkRequest &request, Services::FileDownloaderServiceUserInterface::FileDownloadRequestType type, QHttpMultiPart *multiPart)
{
    QNetworkReply *reply = NULL;
    switch (type)
    {
    case Services::FileDownloaderServiceUserInterface::Get:
        reply = this->getInstance()->get(request);
    case Services::FileDownloaderServiceUserInterface::Delete:
        reply = this->getInstance()->deleteResource(request);
    case Services::FileDownloaderServiceUserInterface::Post:
        reply = this->getInstance()->post(request, multiPart);
    case Services::FileDownloaderServiceUserInterface::Put:
        reply = this->getInstance()->put(request, multiPart);
    }
    if (reply != NULL)
    {
        qDebug() << "File downloader reply not null";
        currentJob->setReply(reply);
        QObject::connect(reply, SIGNAL(finished()), currentJob, SLOT(onFinished()));
        QObject::connect(reply, SIGNAL(downloadProgress(qint64,qint64)), currentJob, SLOT(onProgress(qint64, qint64)));
        QObject::connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), currentJob, SLOT(onError(QNetworkReply::NetworkError)));
        QObject::connect(reply, SIGNAL(readyRead()), currentJob, SLOT(onReadReady()));
        currentJob->downloadStarted();
    }
}

void FileDownloaderLibrary::executeFileDownloader(const QNetworkRequest &request,
                                                  Services::FileDownloaderServiceUserInterface::FileDownloadRequestType requestType,
                                                  QHttpMultiPart *multiPart,
                                                  QFile &file,
                                                  QObject *sender,
                                                  int requestId,
                                                  void *data)
{
    FileDownloadJob *newJob = new FileDownloadJob(file,
                                                  requestId,
                                                  data,
                                                  sender);
    this->executeFileDownload(newJob, request, requestType, multiPart);
}

QNetworkAccessManager* FileDownloaderLibrary::instance = NULL;


